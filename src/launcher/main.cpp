// SPDX-License-Identifier: BSD-2-Clause

#include <iostream>
#include <memory>

#include <core/Launcher.hpp>

using Core::Launcher;

int main(int argc, char** argv)
{
    try {
        std::unique_ptr<Launcher> launcher = Launcher::init(argc, argv);

        launcher->loadParametersFromFile();
        launcher->loadAppletViewer();
    } catch (const std::exception& err) {
        std::cout << err.what() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
