// http_request.cxx

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "util.h"
#include "http_request.h"

namespace web {
    const std::string http_request::HEADER_BODY_DELIM = "\r\n\r\n";

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

        // Request line parsing
        std::string request_line = "";
        // Request line is the first line of the request.
        std::getline(req_stream, request_line);

        std::vector<std::string> request_line_items = string_util::split(request_line, ' ');
        if(request_line_items.size() != 3) {
            throw std::invalid_argument("Invalid Request Line: " + request_line);
        }
        
        method = request_line_items[0];
        if(valid_methods.find(method) == valid_methods.end()) {
            throw std::invalid_argument("Invalid method: " + method);
        }

        // TODO validate the uri
        uri = request_line_items[1];
        // Should be 1.1
        http_version = request_line_items[2];

        // Headers are all lines up to CRLFCRLF
        int header_end_index = req_stream.str().find(HEADER_BODY_DELIM);
        std::string hdrs = req_stream.str().substr(request_line.size()+1, header_end_index - request_line.size());
        std::vector<std::string> hdr_vec = string_util::split(hdrs, '\n');
        for(std::string h: hdr_vec) {
            int hdr_delim_idx = h.find_first_of(":");
            std::string hdr_key = string_util::trim_copy(h.substr(0, hdr_delim_idx));
            std::string hdr_value = string_util::trim_copy(h.substr(hdr_delim_idx+1));
            headers[hdr_key] = hdr_value;
        }

        body = req_stream.str().substr(header_end_index + HEADER_BODY_DELIM.size());
    }

    std::string http_request::to_string() {
        std::stringstream req_str;
        req_str << "Method: " << method << std::endl
                << "URI: " << uri << std::endl
                << "HTTP Version: " << http_version << std::endl
                << "Path: " << path << std::endl;
        
        req_str << "Headers:" << std::endl;
        for(std::map<std::string, std::string>::iterator i = headers.begin(); i != headers.end(); ++i) {
            req_str << i->first << " - " << i->second << std::endl;
        }
        req_str << "Body:" << std::endl << body;

        return req_str.str();
    }
}
