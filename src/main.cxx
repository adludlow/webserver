// main.cxx

#include <memory>
#include <iostream>

#include "webserver.h"

int main(int argc, const char *argv[]) {
    if(argc < 2) {
        std::cout << "Specify a port on the commandline." << std::endl;
        exit(1);
    }

    try {
        std::unique_ptr<web::webserver> webserver = std::make_unique<web::webserver>();
        webserver->start(std::stoi(argv[1]));
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
