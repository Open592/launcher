// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <string>

class Launcher {
public:
    static std::unique_ptr<Launcher> init(int argc, char** argv);

    explicit Launcher(std::string);

    void loadParameterFile();

private:
    std::string m_profile;
};
