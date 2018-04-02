// http_response.cxx

#include <stdexcept>
#include <iostream>
#include <unistd.h>

#include "http_response.h"
#include "util.h"

namespace web {

    http_response::http_response(const int sockfd) {
        this->sockfd = sockfd;
    }

    void http_response::send(const std::string& status){
        std::string response_str = "HTTP/1.1 " + status + " OK\n"
        "Date: Sun, 11 Mar 2018 14:54:30 GMT\n"
        "Server: Webtoy\n"
        "content-type: text/html;\n"
        "content-length: 47\n"
        "\n"
        "<html><head>\n<title>TEST</title>\n</head></html>";

        write_response(sockfd, response_str);
    }

    void http_response::send(const std::string& status, const std::string& body){
        std::string response_str = "HTTP/1.1 " + status + " OK\n"
        "Date: Sun, 11 Mar 2018 14:54:30 GMT\n"
        "Server: Webtoy\n"
        "content-type: text/html;\n"
        "content-length: 47\n"
        "\n" + body;

        write_response(sockfd, response_str);
      }

    void http_response::write_response(const int sockfd, const std::string& response) {
        int n = write(sockfd, response.c_str(), response.size());
        if(n < 0) {
            throw std::runtime_error(web_util::create_error_text("ERROR writing to socket."));
        }
        close(sockfd);
    }
}
