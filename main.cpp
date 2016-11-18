#include "./util.hpp"

using namespace cc;

#include "./case1.hpp"
#include "./case2.hpp"

int main(int argc, char *argv[]) {
    try {
        // case1::run();
        case2::run();
    } catch (const std::exception &e) {
        std::cerr << colorant('y', format_str("error: %s", e.what())) << std::endl;
    }
}

