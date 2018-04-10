#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <set>
#include <string>
#include <map>

namespace web {
    class http_request {
        public:
            http_request(int sockfd, char *request);

            static const std::string HEADER_BODY_DELIM;

            int sockfd;
            char *request_buffer;
            std::string method;
            std::string uri;
            std::string http_version;
            std::string path;
            bool valid;
            std::string invalid_reason = "";
            std::string body;

            std::map<std::string, std::string> query;
            std::map<std::string, std::string> param;
            std::map<std::string, std::string> headers;

            std::string to_string();
            
        private:
            const std::set<std::string> valid_methods = {
                "OPTIONS",
                "GET",
                "HEAD",
                "POST",
                "PUT",
                "DELETE",
                "TRACE",
                "CONNECT"
            };

            void parse_request(char *request);
    };
}

#endif
