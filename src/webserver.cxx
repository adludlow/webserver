// webserver.cxx

#include <memory>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <algorithm>

#include "webserver.h"
#include "http_listener.h"

namespace web {

    webserver::webserver() {
        default_router = router();
    }

    void webserver::start(const int portno) {
        std::cout << "starting webserver on port " << portno << std::endl;

        is_running = true;

        std::unique_ptr<http_listener> listener = std::make_unique<http_listener>(portno);

        while(is_running) {
            http_request req = listener->listen();
            std::unique_ptr<http_response> res = std::make_unique<http_response>(req.sockfd);
            process_request(req, *res);
        }
    }

    void webserver::process_request(http_request& req, http_response& res) {
        // Iterate through middleware
        for(middleware* mw: middleware_pipeline) {
            mw->process(req, res);
        }

        // Find router.
        // call appropriate router method.
        router r;
        try {
            r = routers.at(req.path);
        }
        catch(std::out_of_range& e) {
            r = default_router;
        }
        
        std::string method;
        std::transform(req.method.begin(), req.method.end(), method.begin(), ::tolower);
        if(method == "get") {
            r.get(req.path, req, res);
        }
        else if(method == "post") {
            r.post(req.path, req, res);
        }
        else if(method == "put") {
            r.put(req.path, req, res);
        }
        else if(method == "delete") {
            r.del(req.path, req, res);
        }
        else if(method == "options") {
            r.options(req.path, req, res);
        }
        else {
            res.send("400");
        }
    }

    void webserver::shutdown() {
        is_running = false;

        // What else?
    }

    void webserver::add_middleware(middleware* mw) {
        middleware_pipeline.push_back(mw);
    }

    void webserver::add_route(const std::string& path, router& route) {
        routers[path] = route;
    }
}
