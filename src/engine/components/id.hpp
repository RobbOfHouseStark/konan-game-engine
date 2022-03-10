#ifndef KGE_ENGINE_ID_HPP
#define KGE_ENGINE_ID_HPP

#include <string>

#include "interpreters/create_interpreter.hpp"
#include "interpreters/imgui_interpreter.hpp"

namespace konan::engine {
    struct Id;

    Id create_id();
    void show_id(Id& id);

    struct Id : public CreateInterpreter<Id, create_id>,
                public ImGuiInterpreter<Id, show_id> {
        Id(std::string tag, std::string name);

    public:
        std::string tag;
        std::string name;
    };
}

#endif  // KGE_ENGINE_ID_HPP
