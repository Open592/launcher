// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <jni.h>
#include <memory>
#include <string>
#include <vector>

namespace Core {

class AppletViewerLoader {
public:
    AppletViewerLoader(const std::vector<std::string>&);
    ~AppletViewerLoader();

    void init(std::string_view);

private:
    JavaVM* m_vm;
    JNIEnv* m_env;
};

}
