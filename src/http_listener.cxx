// http_listener.cxx

#include <stdexcept>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

#include "http_listener.h"
#include "util.h"

namespace web {
    http_listener::http_listener(int portno) {
        init(portno);
    }

    void http_listener::init(int portno) {
        request_buffer_len = DEFAULT_REQUEST_BUFFER_LEN;
        backlog_queue_length = DEFAULT_BACKLOG_QUEUE_LEN;

        sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0) {
            // socket creation failed
            throw std::runtime_error(web_util::create_error_text("Socket creation failed."));
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        this->portno = portno;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

        if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            throw std::runtime_error(web_util::create_error_text("Could not bind to port " + std::to_string(portno)));
        }

        // listen() takes a socket file descriptor and the backlog queue size s args.
        ::listen(sockfd, backlog_queue_length);
    }

    http_request http_listener::listen() {
        int newsockfd;
        socklen_t clilen;
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if(newsockfd < 0) {
            throw std::runtime_error(web_util::create_error_text("Error accepting connection request"));
        }

        int n;
        std::vector<char> buffer(request_buffer_len);
        n = read(newsockfd, &buffer[0], buffer.size());
        if(n < 0) {
            throw std::runtime_error(web_util::create_error_text("ERROR re    ading from socket."));
        }
        
        return http_request(newsockfd, buffer.data());
    }
}
