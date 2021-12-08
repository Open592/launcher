// SPDX-License-Identifier: BSD-2-Clause

#include <pwd.h>
#include <stdexcept>
#include <unistd.h>

#include "../../FileSystemUtils.hpp"

namespace Core::Utils {

/**
 * Find the root configuration directory on Linux systems
 *
 * We will attempt to honor the users preference if they have set
 * `XDG_CONFIG_HOME` - if that doesn't work, or is unset we will then fallback
 * to using `$HOME/.config`
 *
 * @return std::filesystem::path
 */
fs::path findConfigurationDirectory()
{
    const char* userConfig = std::getenv("XDG_CONFIG_HOME");

    if (userConfig != nullptr) {
        return fs::path(userConfig);
    }

    const char* home = std::getenv("HOME");

    if (home != nullptr) {
        return fs::path(home) / ".config";
    }

    // Fallback to using passwd

    struct passwd* pwuid = getpwuid(getuid());

    if (pwuid == nullptr) {
        return "";
    }

    return fs::path(pwuid->pw_dir) / ".config";
}

/**
 * Find the configuration directory for the project
 *
 * @return std::filesystem::path
 */
fs::path getProjectConfigurationDirectory()
{
    fs::path configurationDirectory = findConfigurationDirectory();

    if (configurationDirectory.empty()) {
        return "";
    }

    return configurationDirectory / "open592";
}

} // namespace Core::Utils
