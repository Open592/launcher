// SPDX-License-Identifier: BSD-2-Clause

#include <cassert>
#include <fmt/core.h>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "FileSystemUtils.hpp"
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

    fs::path configDirectory = Utilities::getProjectConfigurationDirectory();

    if (configDirectory.empty()) {
        throw std::runtime_error("Failed to find configuration directory");
    }

    std::string parameterFileName = this->m_profile + ".prm";
    fs::path parameterFilePath = configDirectory / parameterFileName;

    if (!std::filesystem::exists(parameterFilePath)) {
        throw std::runtime_error("Failed to open parameter file");
    }

    if (!std::filesystem::is_regular_file(parameterFilePath)) {
        throw std::runtime_error("Found invalid parameter file");
    }

    this->readParameterFile(parameterFilePath);
}

void Launcher::readParameterFile(const fs::path& path)
{
    std::cout << path << '\n';
}
