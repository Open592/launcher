// SPDX-License-Identifier: BSD-2-Clause

#include <cassert>
#include <fmt/core.h>
#include <memory>
#include <stdexcept>

#include "Launcher.hpp"

/**
 * Initialize the Launcher from command line arguments
 *
 * We expect a single argument to be passed which represents the
 * "profile". We use this profile to initialize the `.prm` file which includes
 * information to be passed to the JVM
 *
 * @param argc
 * @param argv
 * @return An instance of Launcher instantiated with the provided profile
 */
std::unique_ptr<Launcher> Launcher::init(int argc, char** argv)
{
    if (argc != 2) {
        throw std::invalid_argument(fmt::format("Expected exactly 1 argument, received: {}", argc));
    }

    std::string profile = argv[1];

    if (profile.empty()) {
        throw std::invalid_argument("Received empty profile argument");
    }

    return std::make_unique<Launcher>(profile);
}

Launcher::Launcher(std::string profile)
    : m_profile(profile)
{
}

void Launcher::loadParameterFile()
{
    assert(!m_profile.empty());
}
