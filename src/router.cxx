// router.cxx

#include "router.h"

namespace web {

    router::router() {

    }

    void router::get(const std::string& path, http_request& req, http_response& res) {
        res.send("405");
    }

    void router::post(const std::string& path, http_request& req, http_response& res) {
        res.send("405");
    }

    void router::put(const std::string& path, http_request& req, http_response& res) {
        res.send("405");
    }

    void router::del(const std::string& path, http_request& req, http_response& res) {
        res.send("405");
    }

    void router::options(const std::string& path, http_request& req, http_response& res) {
        res.send("405");
    }
}
