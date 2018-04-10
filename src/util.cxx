// util.h

#include <string>
#include <string.h>
#include "util.h"

namespace web_util {

    std::string create_error_text(const std::string& error) {
        return error + ": " + strerror(errno);        
    }

}

namespace string_util {
    template<typename Out>
    void split(const std::string& s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while(std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

}
