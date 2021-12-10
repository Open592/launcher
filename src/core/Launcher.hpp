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

    Launcher(std::string_view);
    Launcher(std::vector<std::string>) noexcept;

    const std::vector<std::string>& getParameters() const noexcept { return m_parameters; };
    const std::string& getClassName() const noexcept { return m_className; };

    void loadAppletViewer();

private:
    static std::vector<std::string> readParameterFile(const fs::path&);
    static fs::path findParameterFilePath(std::string_view);

    void loadParameterData(std::string_view);

    std::unique_ptr<AppletViewerLoader> m_appletViewerLoader;
    std::string m_className;
    std::vector<std::string> m_parameters;
};

}
