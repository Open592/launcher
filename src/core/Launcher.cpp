// SPDX-License-Identifier: BSD-2-Clause

#include <cassert>
#include <fmt/core.h>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "FileSystemUtils.hpp"
#include "Launcher.hpp"

namespace Core {

/**
 * Initialize the Launcher from command line arguments
 *
 * We expect a single argument to be passed which represents the
 * "profile". We use this profile to initialize the `.prm` file which includes
 * information to be passed to the JVM
 *
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

/**
 * Initialize the Launcher with a profile with which it can retrieve a `.prm`
 * file from the configuration directory. From this file the parameters which
 * are passed to the JVM when initialized.
 */
Launcher::Launcher(std::string_view profile)
{
    this->loadParameterData(profile);
}

/**
 * Initialize the launcher with a list of parameters which will be passed to the
 * JVM when it's initialized.
 */
Launcher::Launcher(std::vector<std::string> parameters) noexcept
    : m_parameters(std::move(parameters))
{
}

/**
 * Handle initialzing the JVM and loading the Applet Viewer
 */
void Launcher::loadAppletViewer()
{
    m_appletViewerLoader = std::make_unique<AppletViewerLoader>(m_parameters);
}

/**
 * Load the JVM parameters from `.prm` file located in the configuration dir
 *
 * These parameters will be used to initalize the JVM and launch the Applet
 * Viewer. They will be stored for now in an internal vector. The location of
 * the parameter file is platform dependent.
 */
fs::path Launcher::findParameterFilePath(std::string_view profile)
{
    fs::path configDirectory = Utils::getProjectConfigurationDirectory();

    if (configDirectory.empty()) {
        throw std::runtime_error(fmt::format("Failed to find configuration directory: {}", configDirectory.native()));
    }

    std::string parameterFileName = fmt::format("{}.prm", profile);
    fs::path parameterFilePath = configDirectory / parameterFileName;

    if (!std::filesystem::exists(parameterFilePath)) {
        throw std::runtime_error(fmt::format("Failed to find parameter file: {}", parameterFilePath.native()));
    }

    if (!std::filesystem::is_regular_file(parameterFilePath)) {
        throw std::runtime_error(fmt::format("{} is not a valid parameter file", parameterFilePath.native()));
    }

    return parameterFilePath;
}

/**
 * Read the parameters from the parameter file.
 *
 * @param path
 */
std::vector<std::string> Launcher::readParameterFile(const fs::path& path)
{
    std::vector<std::string> parameters;
    std::ifstream parameterFile = std::ifstream(path, std::ifstream::in);

    if (!parameterFile.is_open()) {
        throw std::runtime_error(fmt::format("Failed to open parameter file: {}", path.native()));
    }

    std::string currentParameter;

    while (std::getline(parameterFile, currentParameter)) {
        parameters.push_back(currentParameter);
    }

    parameterFile.close();

    return parameters;
}

/**
 * Load parameter data
 *
 * The `.prm` file contains two sets of data. Parameters for the JVM and the
 * class which needs to be loaded. Within this function we will pull both
 * pieces of data from the file and store them.
 */
void Launcher::loadParameterData(std::string_view profile)
{
    fs::path parameterFilePath = Launcher::findParameterFilePath(profile);
    std::vector<std::string> parameterFileData = Launcher::readParameterFile(parameterFilePath);

    if (parameterFileData.empty()) {
        throw std::runtime_error(fmt::format("Found empty parameter file: {}", parameterFilePath.native()));
    }

    // In the case that the parameter file only has a single entry, we will
    // treat it as the class name, and attempt to load the JVM without any
    // parameters.
    this->m_className = std::move(parameterFileData.back());
    parameterFileData.pop_back();

    this->m_parameters = std::move(parameterFileData);
}

}
