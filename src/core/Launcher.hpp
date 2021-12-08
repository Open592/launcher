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

    explicit Launcher(std::string);

    const std::vector<std::string>& getParameters() const noexcept { return m_parameters; };
    std::string getProfile() const noexcept { return m_profile; }

    void loadAppletViewer();
    void loadParametersFromFile();

private:
    void readParameterFile(const fs::path&);

    std::unique_ptr<AppletViewerLoader> m_appletViewerLoader;
    std::vector<std::string> m_parameters;
    std::string m_profile;
};

}
