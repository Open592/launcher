#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

#include <core/Launcher.hpp>

namespace fs = std::filesystem;

const std::string EXCHANGE_FILE_NAME = "exchange.txt";
const std::string SENDER_KNOWN_TEXT = "hello-from-cpp";
const std::string EXPECTED_RECEIVER_KNOWN_TEXT = "hello-from-java";

/**
 * The goal of this test is verify the successful execution of every part of
 * the launcher:
 *
 * - Successfully able to resolve parameter file path
 * - Successfully able to parse JVM parameters
 * - Successfully able to initialize the JVM with the provided parameters
 * - Successfully able to call the main method of the provided class
 *
 * The test is run as follows:
 *
 * - Given the `MOCK_PROJECT_CONFIG_DIRECTORY` we create an exchange file which
 * includes a known text.
 * - We initialize the launcher
 * - The mock appletviewer jar will read the exchange file and verify that
 * it contains the known text.
 * - The mock appletviewer jar will then replace the known text with it's own
 * known text.
 * - Once the launcher successfully executes we will read the exchange file and
 * verify that the known text has been changed and is correct.
 * - We will delete the exchange file.
 */
TEST(LauncherFunctionalTest, VerifyJarSuccessfullyLoaded)
{
    fs::path testDataDirectory = fs::path(MOCK_PROJECT_CONFIG_DIRECTORY);

    EXPECT_TRUE(fs::exists(testDataDirectory)) << "Expected mock project config directory to exist";

    std::ofstream exchangeFile(testDataDirectory / EXCHANGE_FILE_NAME);

    EXPECT_TRUE(exchangeFile.is_open()) << "Failed to open exchange file";

    exchangeFile << SENDER_KNOWN_TEXT << std::endl;

    exchangeFile.close();

    // The name of the parameters file is "happypath.prm". Because of this we
    // will pass "happypath" as the profile name.
    Core::Launcher launcher("happypath");

    EXPECT_FALSE(launcher.getClassName().empty()) << "Expected Launcher to correctly parse Java class name";
    EXPECT_FALSE(launcher.getParameters().empty()) << "Expected Launcher to correctly parse JVM parameters";

    EXPECT_NO_THROW(launcher.loadAppletViewer());

    std::ifstream updatedExchangeFile(testDataDirectory / EXCHANGE_FILE_NAME);

    std::string receiverKnownText;
    std::getline(updatedExchangeFile, receiverKnownText);

    EXPECT_EQ(receiverKnownText, EXPECTED_RECEIVER_KNOWN_TEXT);

    updatedExchangeFile.close();

    EXPECT_NO_THROW(fs::remove(testDataDirectory / EXCHANGE_FILE_NAME));
}

/**
 * The goal of this test is validate the handling of the launcher when it
 * encounters a sitation where it cannot load the Java class specified in the
 * `.prm` file.
 *
 * - We will initialize the launcher with a `.prm` file which is purposefully
 * flawed in that it's classname points to nothing. It will have a valid
 * classpath which points to a valid jar. But that won't help with anything.
 *
 * We should receive an exception from the launcher `loadAppletViewer` method
 * since it will fail to load.
 */
TEST(LauncherFunctionalTest, VerifyHandlingOfClassNotFound)
{
    // The name of the parameters file is "classnotfound.prm". Because of this we
    // will pass "classnotfound" as the profile name.
    Core::Launcher launcher("classnotfound");

    EXPECT_FALSE(launcher.getClassName().empty()) << "Expected Launcher to correctly parse Java class name";
    EXPECT_FALSE(launcher.getParameters().empty()) << "Expected Launcher to correctly parse JVM parameters";

    EXPECT_THROW(launcher.loadAppletViewer(), std::runtime_error);
}

/**
 * The goal of this test is to validate the handling of Java exceptions thrown
 * within the Java code loaded by the launcher.
 *
 * - We will initialize the launcher with a `.prm` file which is purposefully
 * pointing to a jar which will always throw an exception.
 *
 * This tests validates that the launcher correctly sees that an exception was
 * thrown and that the launcher did not exit cleanly.
 */
TEST(LauncherFunctionalTest, VerifyJavaException)
{
    // The name of the parameters file is "javaerror.prm". Because of this we
    // will pass "javaerror" as the profile name.
    Core::Launcher launcher("javaerror");

    EXPECT_FALSE(launcher.getClassName().empty()) << "Expected Launcher to correctly parse Java class name";
    EXPECT_FALSE(launcher.getParameters().empty()) << "Expected Launcher to correctly parse JVM parameters";

    EXPECT_THROW(launcher.loadAppletViewer(), std::runtime_error);
}
