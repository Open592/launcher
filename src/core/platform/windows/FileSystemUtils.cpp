// SPDX-License-Identifier: BSD-2-Clause

#include <filesystem>
#include <optional>
#include <shlobj.h>
#include <windows.h>

#include "../../FileSystemUtils.hpp"

static std::optional<std::wstring> getOverrideConfigurationDirectory()
{
    // https://docs.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getenvironmentvariablea
    DWORD bufferSize = 65535;
    std::wstring buffer;

    buffer.resize(bufferSize);

    bufferSize = GetEnvironmentVariableW(L"OPEN592_OVERRIDE_OS_CONFIG_DIR", buffer.data(), bufferSize);

    if (bufferSize == 0 || buffer.empty()) {
        return std::nullopt;
    }

    if (GetLastError() == ERROR_ENVVAR_NOT_FOUND) {
        return std::nullopt;
    }

    buffer.resize(bufferSize);

    return buffer;
}

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
        auto localAppDataPath = fs::path(std::move(localAppDataDirectory));

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
    // First check if an override directory is set
    std::optional<std::wstring> overrideConfigurationDirectory = getOverrideConfigurationDirectory();

    if (overrideConfigurationDirectory.has_value()) {
        return fs::path(std::move(overrideConfigurationDirectory.value())) / "open592";
    }

    // Otherwise, we will use the standard OS application directory
    fs::path configurationDirectory = findConfigurationDirectory();

    if (configurationDirectory.empty()) {
        return configurationDirectory;
    }

    return configurationDirectory / "config" / "open592";
}

}
