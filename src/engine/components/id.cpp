#include "id.hpp"

namespace konan::engine {
    Id::Id(std::string tag, std::string name)
        : tag { std::move(tag) }, name { std::move(name) } {}

    Id create_id() {
        return { "Default", "Unnamed" };
    }

    void show_id(Id& id) {
        ImGui::InputText("Tag.", (char*)id.tag.c_str(), 50);
        ImGui::InputText("Name.", (char*)id.name.c_str(), 50);
    }
}
