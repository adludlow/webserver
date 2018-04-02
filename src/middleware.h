#ifndef MIDDLEAWARE_H
#define MIDDLEWARE

#include "http_request.h"
#include "http_response.h"

namespace web {
    class middleware {
        public:
            middleware();

            virtual void process(http_request& req, http_response& res) = 0;
    };
}

#endif // MIDDLEWARE_H
