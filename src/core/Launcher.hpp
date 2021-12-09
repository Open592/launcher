// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "AppletViewerLoader.hpp"

namespace fs = std::filesystem;

namespace Core {

class Launcher {
public:
    static std::unique_ptr<Launcher> init(int argc, char** argv);

    Launcher(std::string);
    Launcher(std::vector<std::string>) noexcept;

    const std::vector<std::string>& getParameters() const noexcept { return m_parameters; };

    void loadAppletViewer();

private:
    fs::path findParameterFilePath(std::string) const;
    std::vector<std::string> readParameterFile(const fs::path&) const;

    std::unique_ptr<AppletViewerLoader> m_appletViewerLoader;
    std::vector<std::string> m_parameters;
};

}
