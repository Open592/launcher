// SPDX-License-Identifier: BSD-2-Clause

#include <windows.h>
#include <shlobj.h>
#include <filesystem>

#include "../../FileSystemUtils.hpp"

namespace Core::Utils {

/**
 * Find the root configuration directory on Linux systems
 *
 * The goal of this function is just to return a fs::path pointing to %LOCALAPPDATA%
 */
fs::path findConfigurationDirectory()
{
    PWSTR localAppDataDirectory;

    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &localAppDataDirectory))) {
        auto localAppDataPath = fs::path(localAppDataDirectory);

        CoTaskMemFree(localAppDataDirectory);

        return localAppDataPath;
    }

    return "";
}

/**
 * Find the configuration directory for the project
 *
 * Example returned directory: %LOCALAPPDATA%\open592\config
 */
fs::path getProjectConfigurationDirectory()
{
    fs::path configurationDirectory = findConfigurationDirectory();

    if (configurationDirectory.empty()) {
        return configurationDirectory;
    }

    return configurationDirectory / "config" / "open592";
}

}
