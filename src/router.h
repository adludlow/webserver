// router.h
#ifndef ROUTER_H
#define ROUTER_H

#include <string>

#include "http_request.h"
#include "http_response.h"

namespace web {
    class router {

        public:
            router();
        
            void get(const std::string& path, http_request& req, http_response& res);
            void post(const std::string& path, http_request& req, http_response& res);
            void put(const std::string& path, http_request& req, http_response& res);
            void del(const std::string& path, http_request& req, http_response& res);
            void options(const std::string& path, http_request& req, http_response& res);
    };
}

#endif
