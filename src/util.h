#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace web_util {

    std::string create_error_text(const std::string& error);

}

namespace string_util {
    template<typename Out>
    void split(const std::string& s, char delim, Out result);

    std::vector<std::string> split(const std::string& s, char delim);

}

#endif // UTIL_H
