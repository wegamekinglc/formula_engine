//
// Created by wegam on 2018/10/20.
//

#include <fel/utilities/errors.hpp>

namespace FEngine {
    namespace {

#if defined(_MSC_VER) || defined(__BORLANDC__)
        // allow Visual Studio integration
        std::string format(
                const std::string& file,
                long line,
                const std::string& message) {
            std::ostringstream msg;
            msg << "\n  " << file << "(" << line << "): \n";
            msg << message;
            return msg.str();
        }
#else
        // use gcc format (e.g. for integration with Emacs)
    std::string format(const std::string& file,
                       long line,
                       const std::string& message) {
        std::ostringstream msg;
        msg << "\n" << file << ":" << line << ": ";
        msg << message;
        return msg.str();
    }
#endif

    }

    Error::Error(const std::string& file,
            long line,
                 const std::string& message) {
        message_ = std::make_shared<std::string>(
                format(file, line, message));
    }


    const char* Error::what() const noexcept {
        return message_->c_str();
    }
}
