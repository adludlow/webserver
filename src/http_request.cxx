// http_request.cxx

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "util.h"
#include "http_request.h"

namespace web {
    http_request::http_request(int sockfd, char *request) {
        this->sockfd = sockfd;
        request_buffer = request;

        try {
            parse_request(request_buffer);
            valid = true;
        }
        catch(std::invalid_argument& e) {
            valid = false;
            invalid_reason = e.what();
        }
    }

    void http_request::parse_request(char *request) {
        std::stringstream req_stream(request);
        std::string request_line = "";
        std::getline(req_stream, request_line);

        std::vector<std::string> request_line_items = string_util::split(request_line, ' ');
        if(request_line_items.size() != 3) {
            throw std::invalid_argument("Invalid Request Line: " + request_line);
        }
        
        method = request_line_items[0];
        if(valid_methods.find(method) == valid_methods.end()) {
            throw std::invalid_argument("Invalid method: " + method);
        }

        uri = request_line_items[1];
        http_version = request_line_items[2];
    }
}
