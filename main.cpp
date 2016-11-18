#include "./util.hpp"

using namespace cc;

#include "./gauss_distribution.hpp"
#include "./gamma_distribution.hpp"

int main(int argc, char *argv[]) {
    try {
        // gamma_distribution::run();
        gauss_distribution::run();
    } catch (const std::exception &e) {
        std::cerr << colorant('y', format_str("error: %s", e.what())) << std::endl;
    }
}

