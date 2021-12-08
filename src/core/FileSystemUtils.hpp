// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

/**
 * Platform dependent filesystem utilities
 */
namespace Core::Utils {

fs::path findConfigurationDirectory();
fs::path getProjectConfigurationDirectory();

} // namespace Core::Utils
