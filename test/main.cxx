#define CATCH_CONFIG_MAIN
#include <exception>
#include <iostream>

#include "catch.hpp"
#include "../src/webserver.h"

TEST_CASE("webserver test") {
    try {
        web::webserver* ws = new web::webserver();
        ws->start(8090);
        ws->shutdown();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
