// main.cxx

#include <memory>
#include <iostream>

#include "webserver.h"

int main(int argc, const char *argv[]) {
    try {
        std::unique_ptr<web::webserver> webserver = std::make_unique<web::webserver>();
        webserver->start(8080);
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
