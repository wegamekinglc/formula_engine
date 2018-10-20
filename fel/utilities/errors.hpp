#pragma once

#include <exception>
#include <string>
#include <memory>
#include <sstream>

namespace FEngine {
    class Error : public std::exception {
      public:
        /*! The explicit use of this constructor is not advised.
            Use the QL_FAIL macro instead.
        */
        Error(const std::string& file,
              long line,
              const std::string& message = "");
        /*! the automatically generated destructor would
            not have the throw specifier.
        */
        ~Error() noexcept = default;
        //! returns the error message.
        const char* what() const noexcept;
      private:
        std::shared_ptr<std::string> message_;
    };
}

#define FEL_REQUIRE(condition,message) \
if (!(condition)) { \
    std::ostringstream _ql_msg_stream; \
    _ql_msg_stream << message; \
    throw FEngine::Error(__FILE__,__LINE__,_ql_msg_stream.str()); \
 } else 