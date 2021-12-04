// SPDX-License-Identifier: BSD-2-Clause

#include <iostream>
#include <memory>

#include "Launcher.hpp"

int main(int argc, char** argv)
{
    try {
        std::unique_ptr<Launcher> launcher = Launcher::init(argc, argv);
    } catch (const std::invalid_argument& err) {
        std::cout << err.what() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
