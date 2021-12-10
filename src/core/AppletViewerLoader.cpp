// SPDX-License-Identifier: BSD-2-Clause

#include <fmt/core.h>
#include <iostream>
#include <stdexcept>

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
        std::string_view errorDetail;

        switch (ret) {
        case JNI_EINVAL:
            errorDetail = "Invalid arguments supplied";
        case JNI_EVERSION:
            errorDetail = "Invalid JNI version";
        case JNI_ENOMEM:
            errorDetail = "Not enough memory";
        case JNI_EEXIST:
            errorDetail = "JVM already exists";
        default:
            errorDetail = "Unkown error";
        }

        throw std::runtime_error(fmt::format("Failed to start JVM {}", errorDetail));
    }
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

void AppletViewerLoader::init(std::string_view className)
{
    jclass appletViewerClass = this->m_env->FindClass(className.data());

    if (appletViewerClass == nullptr) {
        throw std::runtime_error(fmt::format("Failed to find java class: {}", className));
    }

    jmethodID mainMethodID = this->m_env->GetStaticMethodID(appletViewerClass, "main", "(Ljava/lang/String;)V");
    jclass stringClass = this->m_env->FindClass("java/lang/class");
    jobjectArray mainArgs = this->m_env->NewObjectArray(0, stringClass, nullptr);

    this->m_env->CallStaticVoidMethod(appletViewerClass, mainMethodID, mainArgs);
}

} // namespace Core
