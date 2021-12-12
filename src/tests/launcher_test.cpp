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
 * - Successfully able to load a parameter file when given a direct path
 * - Successfully able to parse JVM parameters
 * - Successfully able to initialize the JVM with the provided parameters
 * - Successfully able to call the main method of the provided class
 *
 * The test is run as follows:
 *
 * - We verify that the parameter file exists within the `TEST_CONFIG_DIR`
 * - Given the `TEST_CONIG_DIR` we create an exchange file which includes a
 * known text.
 * - We initialize the launcher with the path to the above parameter file
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
    fs::path testDataDirectory = fs::path(TEST_DATA_DIR);

    EXPECT_TRUE(fs::exists(testDataDirectory));

    std::ofstream exchangeFile(testDataDirectory / EXCHANGE_FILE_NAME);

    EXPECT_TRUE(exchangeFile.is_open());

    exchangeFile << SENDER_KNOWN_TEXT << std::endl;

    exchangeFile.close();

    fs::path parameterFilePath = testDataDirectory / PARAMETER_FILE_NAME;

    EXPECT_TRUE(fs::exists(parameterFilePath));

    Core::Launcher launcher(parameterFilePath);

    EXPECT_FALSE(launcher.getClassName().empty());
    EXPECT_FALSE(launcher.getParameters().empty());

    EXPECT_NO_THROW(launcher.loadAppletViewer());

    std::ifstream updatedExchangeFile(testDataDirectory / EXCHANGE_FILE_NAME);

    std::string receiverKnownText;
    std::getline(updatedExchangeFile, receiverKnownText);

    EXPECT_EQ(receiverKnownText, EXPECTED_RECEIVER_KNOWN_TEXT);

    updatedExchangeFile.close();

    EXPECT_NO_THROW(fs::remove(testDataDirectory / EXCHANGE_FILE_NAME));
}
