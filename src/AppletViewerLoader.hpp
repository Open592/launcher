// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <jni.h>
#include <memory>
#include <string>
#include <vector>

class AppletViewerLoader {
public:
    AppletViewerLoader(const std::vector<std::string>&);
    ~AppletViewerLoader();

    JNIEnv* getJNIEnv() const noexcept;

private:
    JavaVM* m_vm;
    JNIEnv* m_env;
};
