// SPDX-License-Identifier: BSD-2-Clause

#include <iostream>

#include "AppletViewerLoader.hpp"

namespace Core {

/**
 * AppletViewerLoader handles initializing the JVM and loading the Applet Viewer
 *
 * All parameters located in the `.prm` file loaded by the launcher are passed
 * when starting up the JVM.
 *
 * @param parameters
 */
AppletViewerLoader::AppletViewerLoader(const std::vector<std::string>& parameters)
{
    JavaVMInitArgs vmArgs;
    std::vector<JavaVMOption> options;

    for (const std::string& parameter : parameters) {
        JavaVMOption option;

        option.optionString = const_cast<char*>(parameter.c_str());

        options.push_back(option);
    }

    vmArgs.version = JNI_VERSION_1_6;
    vmArgs.nOptions = static_cast<jint>(options.size());
    vmArgs.options = options.data();
    vmArgs.ignoreUnrecognized = false;

    jint ret = JNI_CreateJavaVM(&this->m_vm, reinterpret_cast<void**>(&this->m_env), &vmArgs);

    if (ret != JNI_OK) {
        throw std::runtime_error("Failed to start JVM");
    }

    std::cout << "Started JVM" << '\n';
}

AppletViewerLoader::~AppletViewerLoader()
{
    if (!this->m_vm) {
        return;
    }

    if (this->m_vm->DetachCurrentThread() != JNI_OK) {
        std::cerr << "Failed to detach current JVM thread" << '\n';
    }

    if (this->m_vm->DestroyJavaVM() != JNI_OK) {
        std::cerr << "Failed to destroy JVM";
    }
}

} // namespace Core
