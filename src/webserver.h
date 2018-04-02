// webserver.h
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "router.h"
#include "middleware.h"
#include "http_request.h"
#include "http_response.h"


namespace web {
    class webserver {
        private:
            int portno;
            bool is_running;

            std::vector<middleware*> middleware_pipeline;
            std::map<std::string, router> routers;

            void process_request(http_request& req, http_response& res);
            router default_router;

        public:
            webserver();

            void start(const int portno);
            void shutdown();
            void add_route(const std::string& path, router& route);
            void add_middleware(middleware* mw);
    };
}
#endif
