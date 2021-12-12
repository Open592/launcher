// SPDX-License-Identifier: BSD-2-Clause

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.InvalidParameterException;
import java.util.Scanner;

public class MockOpen592AppletViewer {
    // The filename for the exchange file created in the cpp test
    private static String EXCHANGE_FILE_NAME = "exchange.txt";

    // The known text set by the cpp test
    private static String EXPECTED_SENDER_KNOWN_TEXT = "hello-from-cpp";

    // The known text we will set and the cpp test will subsequently read
    private static String RECEIVER_KNOWN_TEXT = "hello-from-java";

    public static void validateExchangeFile(File exchangeFile) throws IOException {
        Scanner scanner = new Scanner(exchangeFile);
        String senderKnownText = scanner.nextLine().strip();

        scanner.close();

        if (!senderKnownText.equals(EXPECTED_SENDER_KNOWN_TEXT)) {
            String error = String.format(
                "Expected sender known text to be: \"%s\" but received: \"%s\"",
                senderKnownText,
                EXPECTED_SENDER_KNOWN_TEXT
            );

            throw new IOException(error);
        }
    }

    public static void updateExchangeFile(File exchangeFile) throws IOException {
        FileWriter writer = new FileWriter(exchangeFile, false);

        writer.write(RECEIVER_KNOWN_TEXT);
        writer.close();
    }

    public static void main(String[] args) throws IOException, IllegalArgumentException {
        if (args.length != 0) {
            throw new IllegalArgumentException("Expected to receive no arguments but received: " + args.length);
        }

        // This will be the directory where the exchange file will be present
        String testDataDir = System.getProperty("open592.test.data.dir");

        if (testDataDir.isEmpty()) {
            throw new IOException("Could not retrieve test data directory");
        }

        String exchangeFilePath = testDataDir + File.separator + MockOpen592AppletViewer.EXCHANGE_FILE_NAME;
        File exchangeFile = new File(exchangeFilePath);

        if (!exchangeFile.canRead()) {
            throw new IOException("Cannot open the exchange file for reading");
        }

        // Make sure we received the correct known text
        MockOpen592AppletViewer.validateExchangeFile(exchangeFile);

        // Overwrite the exchange file
        MockOpen592AppletViewer.updateExchangeFile(exchangeFile);
    }
}
