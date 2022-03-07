#include "files.hpp"

namespace {
    // --------------------- Wavefront. -----------

    using namespace konan;

    template <typename Value, int Length>
    glm::vec<Length, Value> parse_vec(std::string_view const line, char delimiter,
                                      glm::vec<Length, Value> data = {}, int index = 0) {
        if (line.empty()) return data;
        std::size_t delimiter_position { line.find(delimiter) };
        data[index] = static_cast<Value>(std::atof(line.substr(0, delimiter_position).data()));
        if (delimiter_position == std::string::npos) return data;
        return parse_vec(line.substr(delimiter_position + 1), delimiter, data, index + 1);
    }

    template <typename Value, int Length>
    glm::mat<Length, Length, Value> parse_mat(std::string_view const line, char mat_delimiter, char vec_delimiter,
                                              glm::mat<Length, Length, Value> data = {}, int index = 0) {
        if (line.empty()) return data;
        auto delimiter_position { line.find(mat_delimiter) };
        data[index] = parse_vec<Value, Length>(line.substr(0, delimiter_position), vec_delimiter);
        if (delimiter_position == std::string::npos) return data;
        return parse_mat(line.substr(delimiter_position + 1), mat_delimiter, vec_delimiter, data, index + 1);
    }

    core::Wavefront combine_vertex_data(std::span<glm::vec3> positions, std::span<glm::vec2> uvs,
                                        std::span<glm::vec3> normals, std::span<glm::imat3x3> faces,
                                        std::unordered_map<glm::vec3, core::VertexIndex> processed = {},
                                        std::vector<core::Vertex> vertices = {},
                                        std::vector<core::VertexIndex> indices = {},
                                        int index = 0) {
        if (faces.empty()) return { vertices, indices };

        auto const& vertex_data_indices { faces[0][index] };
        if (!processed.contains(vertex_data_indices)) {
            processed.emplace(vertex_data_indices, static_cast<core::VertexIndex>(processed.size()));
            // We subtract 1 because indices in wavefront start from 1.
            vertices.push_back({ positions[vertex_data_indices[0] - 1],
                                 uvs[vertex_data_indices[1] - 1],
                                 normals[vertex_data_indices[2] - 1] });
        }
        indices.push_back(processed[vertex_data_indices]);

        if (index < 2) {
            ++index;
        } else {
            index = 0;
            faces = faces.subspan(1);
        }

        return combine_vertex_data(positions, uvs, normals, faces,
                                   std::move(processed), std::move(vertices), std::move(indices),
                                   index);
    }

    // --------------------- Glsl. ----------------

    std::optional<std::string> regex_search_result(std::string const& line, std::regex const& shader_name) {
        std::smatch matches;
        if (std::regex_search(line, matches, shader_name))
            return matches.str(1);

        return {};
    }

    std::pair<std::string, std::string> get_uniform_data(std::string const& line,
                                                         std::regex const& uniform_type,
                                                         std::regex const& uniform_name) {
        auto result_type { regex_search_result(line, uniform_type) };
        auto result_name { regex_search_result(line, uniform_name) };
        return { result_name.value().substr(1, result_name.value().size() - 2),
                 result_type.value().substr(1, result_type.value().size() - 2) };
    }

    int get_glsl_read_mode(std::string const& line, std::regex const& shader_name,
                           std::vector<std::string> const& shader_types) {
        auto result { regex_search_result(line, shader_name) };
        for (int i {}; i < shader_types.size(); ++i) {
            if (shader_types[i] == result.value())
                return i;
        }

        throw core::FileError("Wrong shader type name: ", line);
    }

    // --------------------- General. -------------

    std::ifstream open_file(std::string_view file_path, int flags = std::ios::in) {
        std::ifstream file { file_path.data(), flags };
        if (!file.is_open())
            throw core::FileError("Couldn't open file: ", file_path.data());

        return file;
    }

    template <typename Lambda>
    void process_file(std::ifstream& file, Lambda const& parser) {
        if (std::string line; std::getline(file, line)) {
            parser(line);
            process_file(file, parser);
        }
    }

    template <typename Lambda>
    void process_file(std::string_view const file_path, Lambda const& parser) {
        std::ifstream file { open_file(file_path) };
        process_file(file, parser);
    }
}

namespace konan::core {
    Wavefront load_wavefront(std::string_view file_path) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<glm::imat3x3> vertices;

        process_file(file_path,
                     [&positions, &uvs, &normals, &vertices](std::string_view line) {
                         if (line.starts_with("v ")) {
                             positions.push_back(parse_vec<float, 3>(line.substr(2), ' '));
                         } else if (line.starts_with("vt")) {
                             uvs.push_back(parse_vec<float, 2>(line.substr(3), ' '));
                         } else if (line.starts_with("vn")) {
                             normals.push_back(parse_vec<float, 3>(line.substr(3), ' '));
                         } else if (line.starts_with("f ")) {
                             vertices.push_back(parse_mat<int, 3>(line.substr(2), ' ', '/'));
                         }
                     });

        return combine_vertex_data(positions, uvs, normals, vertices);
    }

    Tga load_tga(std::string_view file_path) {
        std::ifstream file { open_file(file_path, std::ios::in | std::ios::binary) };
        std::uint8_t header[18];
        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (header[16] != 24 || header[2] != 0x2)
            throw FileError("Couldn't open texture(requires 24 bit image): ", file_path.data());

        Tga tga { header[13] * 256 + header[12],
                  header[15] * 256 + header[14],
                  header[16] };
        file.read(reinterpret_cast<char*>(tga.pixels.data()), tga.size);

        return tga;
    }

    Glsl load_glsl(std::string_view file_path, std::vector<std::string> const& shader_types) {
        int mode { -1 };
        std::stringstream ss[2];
        std::unordered_map<std::string, std::string> uniforms;

        std::regex shader_type { "#shader +" };
        std::regex shader_name { '(' + core::join(shader_types, '|') + ')' };
        std::regex uniform { "uniform +" };
        std::regex uniform_type { "(\\ [A-Za-z0-9]+\\ )" };
        std::regex uniform_name { "(\\ [A-Za-z0-9_]+\\;)" };

        process_file(file_path,
                     [&](std::string const& line) {
                         if (std::regex_search(line, shader_type)) {
                             mode = get_glsl_read_mode(line, shader_name, shader_types);
                             return;
                         }

                         if (std::regex_search(line, uniform)) {
                             uniforms.emplace(get_uniform_data(line, uniform_type, uniform_name));
                         }

                         ss[mode] << line << '\n';
                     });

        return {{ ss[0].str(), ss[1].str() }, uniforms };
    }
}
