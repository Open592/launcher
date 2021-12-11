// SPDX-License-Identifier: BSD-2-Clause

public class MockOpen592AppletViewer {
    public static String result;
    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            throw new Exception("Invalid argument count");
        }

        MockOpen592AppletViewer.result = args[0];

        System.out.println("Successfully ran MockOpen592AppletViewer with argument: " + MockOpen592AppletViewer.result);
    }
}
