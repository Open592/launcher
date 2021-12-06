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
        throw std::invalid_argument(fmt::format("Expected exactly 1 argument, received: {}", argc - 1));
    }

    std::string profile = argv[1];

    if (profile.empty()) {
        throw std::invalid_argument("Received invalid profile argument");
    }

    return std::make_unique<Launcher>(profile);
}

Launcher::Launcher(std::string profile)
    : m_profile(profile)
{
}

/**
 * Load the JVM parameters from `.prm` file located in the configuration dir
 *
 * These parameters will be used to initalize the JVM and launch the Applet
 * Viewer. They will be stored for now in an internal vector. The location of
 * the parameter file is platform dependent.
 */
void Launcher::loadParametersFromFile()
{
    fs::path configDirectory = Utilities::getProjectConfigurationDirectory();

    if (configDirectory.empty()) {
        throw std::runtime_error(fmt::format("Failed to find configuration directory: {}", configDirectory.native()));
    }

    std::string parameterFileName = this->m_profile + ".prm";
    fs::path parameterFilePath = configDirectory / parameterFileName;

    if (!std::filesystem::exists(parameterFilePath)) {
        throw std::runtime_error(fmt::format("Failed to find parameter file: {}", parameterFilePath.native()));
    }

    if (!std::filesystem::is_regular_file(parameterFilePath)) {
        throw std::runtime_error(fmt::format("{} is not a valid parameter file", parameterFilePath.native()));
    }

    this->readParameterFile(parameterFilePath);
}

/**
 * Read the parameters from the parameter file.
 *
 * @param path
 */
void Launcher::readParameterFile(const fs::path& path)
{
    std::ifstream parameterFile = std::ifstream(path, std::ifstream::in);

    if (!parameterFile.is_open()) {
        throw std::runtime_error("Failed to open parameter file");
    }

    std::string line;

    while (std::getline(parameterFile, line)) {
        this->m_parameters.push_back(line);
    }

    parameterFile.close();
}
