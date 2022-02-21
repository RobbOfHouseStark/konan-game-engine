#include "files.hpp"

namespace {
    void prepare_content(std::string& content, char delimiter) {
        while (content.at(0) == delimiter)
            content.erase(0, 1);
    }

    template<class T>
    T parse_vec(std::string& content, char delimiter) {
        T data;

        for (std::int32_t i {}; i < T::length(); ++i) {
            prepare_content(content, delimiter);
            std::size_t pos {content.find(delimiter)};
            std::string item {content.substr(0, pos)};
            auto value = static_cast<typename T::value_type>(std::atof(item.c_str()));
            data[i] = value;
            content.erase(0, pos);
        }

        return data;
    }

    template<class T>
    T parse_mat(std::string& content, char delimiter) {
        T data;

        for (std::int32_t i {}; i < T::length(); ++i) {
            prepare_content(content, delimiter);
            std::size_t pos {content.find(delimiter)};
            std::string item {content.substr(0, pos)};
            data[i] = parse_vec<glm::vec<T::length(), typename T::value_type>>(item, '/');
            content.erase(0, pos);
        }

        return data;
    }

    union PixelInfo {
        std::uint32_t color;

        struct {
            std::uint8_t r, g, b, a;
        };
    };
}

namespace konan::core {
    auto load_obj(std::string_view file_path)
                    -> std::pair<std::vector<std::array<float, 8>>, std::vector<std::uint32_t>> {
        std::ifstream file { file_path.data() };
        if (!file.is_open())
            throw FileError("Couldn't open shader: ", file_path.data());

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<glm::mat<3, 3, std::int32_t>> faces;

        std::string line;
        while (getline(file, line)) {
            if (line.size() < 10)
                continue;

            std::string header { line.substr(0, 2) };
            std::string content { line.substr(2) };
            if (header == "v ")
                positions.push_back(parse_vec<glm::vec3>(content, ' '));
            else if (header == "vt")
                uvs.push_back(parse_vec<glm::vec2>(content, ' '));
            else if (header == "vn")
                normals.push_back(parse_vec<glm::vec3>(content, ' '));
            else if (header == "f ")
                faces.push_back(parse_mat<glm::mat<3, 3, std::int32_t>> (content, ' '));
        }

        std::uint32_t current_index {};
        std::unordered_map<glm::vec3, std::uint32_t> processed;
        std::vector<std::uint32_t> indices;
        std::vector<std::array<float, 8>> vertices;

        for (auto const& vertex_components: faces) {
            for (std::int32_t i {}; i < vertex_components.length(); ++i) {
                if (processed.find(vertex_components[i]) != processed.end()) {
                    indices.push_back(processed[vertex_components[i]]);
                    continue;
                }

                indices.push_back(current_index);
                processed[vertex_components[i]] = current_index++;

                vertices.push_back({ positions[vertex_components[i][0] - 1].x,
                                     positions[vertex_components[i][0] - 1].y,
                                     positions[vertex_components[i][0] - 1].z,
                                     uvs[vertex_components[i][1] - 1].x,
                                     uvs[vertex_components[i][1] - 1].y,
                                     normals[vertex_components[i][2] - 1].x,
                                     normals[vertex_components[i][2] - 1].y,
                                     normals[vertex_components[i][2] - 1].z });
            }
        }

        return { vertices, indices };
    }

    Tga load_tga(std::string_view file_path) {
        std::fstream file {file_path.data(), std::ios::in | std::ios::binary};
        if (!file.is_open())
            throw FileError("Couldn't open texture: ", file_path.data());

        Tga tga {};

        std::uint8_t header[18];
        std::vector<std::uint8_t> image_data;
        std::uint8_t de_compressed[12] {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        std::uint8_t is_compressed[12] {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (!std::memcmp(de_compressed, &header, sizeof(de_compressed))) {
            tga.bits_per_pixel = header[16];
            tga.width = header[13] * 256 + header[12];
            tga.height = header[15] * 256 + header[14];
            tga.size = ((tga.width * tga.bits_per_pixel + 31) / 32) * 4 * tga.height;

            if (tga.bits_per_pixel != 24 && tga.bits_per_pixel != 32)
                throw FileError("Couldn't open texture(required 24 or 32 bit image): ", file_path.data());

            image_data.resize(tga.size);
            file.read(reinterpret_cast<char*>(image_data.data()), tga.size);
        } else if (!std::memcmp(is_compressed, &header, sizeof(is_compressed))) {
            tga.bits_per_pixel = header[16];
            tga.width = header[13] * 256 + header[12];
            tga.height = header[15] * 256 + header[14];
            tga.size = ((tga.width * tga.bits_per_pixel + 31) / 32) * 4 * tga.height;

            if (tga.bits_per_pixel != 24 && tga.bits_per_pixel != 32)
                throw core::FileError("Couldn't open texture(required 24 or 32 bit image): " + std::string(file_path) + '.');

            PixelInfo pixel {};
            int current_byte {};
            std::size_t current_pixel {};
            std::uint8_t chunk_header {};
            auto bytes_per_pixel { static_cast<int>(tga.bits_per_pixel / 8) };
            image_data.resize(tga.width * tga.height * sizeof(PixelInfo));

            do {
                file.read(reinterpret_cast<char*>(&chunk_header), sizeof(chunk_header));
                if (chunk_header < 128) {
                    ++chunk_header;
                    for (int i {}; i < chunk_header; ++i, ++current_pixel) {
                        file.read(reinterpret_cast<char*>(&pixel), bytes_per_pixel);
                        image_data[current_byte++] = pixel.b;
                        image_data[current_byte++] = pixel.g;
                        image_data[current_byte++] = pixel.r;
                        if (tga.bits_per_pixel > 24)
                            image_data[current_byte++] = pixel.a;
                    }
                } else {
                    chunk_header -= 127;
                    file.read(reinterpret_cast<char*>(&pixel), bytes_per_pixel);
                    for (int i {}; i < chunk_header; ++i, ++current_pixel) {
                        image_data[current_byte++] = pixel.b;
                        image_data[current_byte++] = pixel.g;
                        image_data[current_byte++] = pixel.r;
                        if (tga.bits_per_pixel > 24)
                            image_data[current_byte++] = pixel.a;
                    }
                }
            } while (current_pixel < (tga.width * tga.height));
        } else {
            throw FileError("Couldn't open texture(required 24 or 32 bit image): ", file_path.data());
        }

        tga.pixels = image_data;
        return tga;
    }

    GlslData load_glsl(std::string_view file_path, std::vector<std::string> const& shader_types) {
        std::ifstream file { file_path.data() };
        if (!file.is_open())
            throw FileError("Couldn't open shader: ", file_path.data());

        int mode { -1 };
        std::stringstream ss[2];
        std::unordered_map<std::string, std::string> uniforms;

        std::regex shader_type { "(#shader[ ]+)" };
        std::regex shader_name { '(' + core::join(shader_types, '|') + ')' };
        std::regex uniform { "(uniform[ ]+)" };
        std::regex uniform_type { "(\\ [A-Za-z0-9]+\\ )" };
        std::regex uniform_name { "(\\ [A-Za-z0-9_]+\\;)" };

        std::string line;
        while (getline(file, line)) {
            std::smatch matches;
            if (std::regex_search(line, shader_type)) {
                std::regex_search(line, matches, shader_name);
                mode = -1;
                for (int i {}; i < shader_types.size(); ++i) {
                    if (shader_types[i] == matches.str(1)) {
                        mode = i;
                        break;
                    }
                }
                continue;
            } else if (std::regex_search(line, uniform)) {
                std::regex_search(line, matches, uniform_type);
                auto type { matches.str(1).substr(1, matches.str(1).size() - 2) };
                std::regex_search(line, matches, uniform_name);
                uniforms.emplace(matches.str(1).substr(1, matches.str(1).size() - 2), type);
            }

            ss[mode] << line << '\n';
        }

        return { { ss[0].str(), ss[1].str() }, uniforms };
    }
}
