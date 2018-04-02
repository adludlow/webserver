#ifndef HTTP_LISTENER_H
#define HTTP_LISTENER_H

#include <netinet/in.h>

#include "http_request.h"

#define DEFAULT_REQUEST_BUFFER_LEN 1024 * 1024 * 10
#define DEFAULT_BACKLOG_QUEUE_LEN 5

namespace web {
    
    class http_listener {
        private: 
            int sockfd;
            struct sockaddr_in serv_addr, cli_addr;
            int request_buffer_len;
            int backlog_queue_length;
            int portno;

            void init(int portno);
        public:
            http_listener(int portno);

            http_request listen();

    };
}

#endif // HTTP_LISTENER_H
