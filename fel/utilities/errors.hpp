#pragma once

#include <exception>
#include <string>
#include <memory>
#include <sstream>

namespace FEngine {
    class Error : public std::exception {
      public:
        /*! The explicit use of this constructor is not advised.
            Use the FEL_FAIL macro instead.
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
    std::ostringstream _fel_msg_stream; \
    _fel_msg_stream << message; \
    throw FEngine::Error(__FILE__,__LINE__,_fel_msg_stream.str()); \
 } else 


#define MULTILINE_MACRO_BEGIN do {
#if defined(BOOST_MSVC) && BOOST_MSVC >= 1500
    /* __pragma is available from VC++9 */
    #define MULTILINE_MACRO_END \
        __pragma(warning(push)) \
        __pragma(warning(disable:4127)) \
        } while(false) \
        __pragma(warning(pop))
#else
    #define MULTILINE_MACRO_END } while(false)
#endif


#define FEL_FAIL(message) \
MULTILINE_MACRO_BEGIN \
    std::ostringstream _fel_msg_stream; \
    _fel_msg_stream << message; \
    throw FEngine::Error(__FILE__,__LINE__, _fel_msg_stream.str()); \
MULTILINE_MACRO_END