#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>

namespace web {

    class http_response {
        public:
            http_response(const int sockfd);

            void send(const std::string& status);
            void send(const std::string& status, const std::string& body);

        private:
            int sockfd;

            void write_response(const int sockfd, const std::string& response);
    };
}

#endif // HTTP_RESPONSE_H
