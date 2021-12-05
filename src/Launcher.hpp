// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Launcher {
public:
    static std::unique_ptr<Launcher> init(int argc, char** argv);

    explicit Launcher(std::string);

    std::string getProfile() const noexcept { return m_profile; }

    void loadParameterFile();

private:
    void readParameterFile(const fs::path&);

    std::string m_profile;
    std::vector<std::string> m_parameters;
};
