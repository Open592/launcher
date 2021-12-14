#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

#include <core/Launcher.hpp>

namespace fs = std::filesystem;

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
const std::string PARAMETER_FILE_NAME = "parameters.prm";
const std::string EXCHANGE_FILE_NAME = "exchange.txt";
const std::string SENDER_KNOWN_TEXT = "hello-from-cpp";
const std::string EXPECTED_RECEIVER_KNOWN_TEXT = "hello-from-java";

TEST(LauncherTest, VerifyJarSuccessfullyLoaded)
{
    fs::path testDataDirectory = fs::path(MOCK_PROJECT_CONFIG_DIRECTORY);

    EXPECT_TRUE(fs::exists(testDataDirectory)) << "Expected mock project config directory to exist";

    std::ofstream exchangeFile(testDataDirectory / EXCHANGE_FILE_NAME);

    EXPECT_TRUE(exchangeFile.is_open()) << "Failed to open exchange file";

    exchangeFile << SENDER_KNOWN_TEXT << std::endl;

    exchangeFile.close();

    // The name of the parameters file is "parameters.prm". Because of this we
    // will pass "parameters" as the profile name.
    Core::Launcher launcher(static_cast<std::string>("parameters"));

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
