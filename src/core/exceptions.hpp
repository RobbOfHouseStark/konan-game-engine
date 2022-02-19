#ifndef KGE_CORE_EXCEPTIONS_HPP
#define KGE_CORE_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace konan::core {
    struct KonanError : public std::runtime_error {
        template <typename... Ts>
        explicit KonanError(std::string error_message = "", Ts&& ... error_messages)
            : runtime_error((std::string(error_message) + ... + error_messages)) {
        }
    };

    struct Exit : public KonanError {
        explicit Exit(int code = 0)
            : _code { code } {
        }

        int code() const {
            return _code;
        }

    private:
        int _code;
    };

    struct FileError : public KonanError {
        using KonanError::KonanError;
    };

    struct GlfwError : public KonanError {
        using KonanError::KonanError;
    };

    struct GlslError : public KonanError {
        using KonanError::KonanError;
    };
}

#endif  // KGE_CORE_EXCEPTIONS_HPP
