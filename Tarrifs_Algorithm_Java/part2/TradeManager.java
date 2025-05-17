// ---------------------------------------------------------
// Assignment 3
// Written by: Adam El-Zein 40298143
// For COMP 249 Section U – Winter 2025
// Manages tariffs and evaluates trade requests.
// ---------------------------------------------------------
package part2;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class TradeManager {

    // Nested class representing a trade request
    private static class TradeRequest {
        private String requestId;
        private String originCountry;
        private String destinationCountry;
        private String productCategory;
        private double tradeValue;
        private double proposedTariff;

        public TradeRequest(String requestId, String originCountry, String destinationCountry,
                            String productCategory, double tradeValue, double proposedTariff) {
            this.requestId = requestId;
            this.originCountry = originCountry;
            this.destinationCountry = destinationCountry;
            this.productCategory = productCategory;
            this.tradeValue = tradeValue;
            this.proposedTariff = proposedTariff;
        }

        public String getRequestId() { return requestId; }
        public String getOriginCountry() { return originCountry; }
        public String getDestinationCountry() { return destinationCountry; }
        public String getProductCategory() { return productCategory; }
        public double getTradeValue() { return tradeValue; }
        public double getProposedTariff() { return proposedTariff; }
    }

    // Reads tariff data from file and loads it into the TariffList
    private static void readTariffData(String filename, TariffList tariffList) {
        try (Scanner scanner = new Scanner(new File(filename))) {
            while (scanner.hasNextLine()) {
                String[] parts = scanner.nextLine().split("\\s+");
                if (parts.length == 4) {
                    String dest = parts[0], origin = parts[1], category = parts[2];
                    double minTariff = Double.parseDouble(parts[3]);
                    if (!tariffList.contains(origin, dest, category)) {
                        tariffList.addToStart(new Tariff(dest, origin, category, minTariff));
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + filename);
            System.exit(1);
        } catch (Exception e) {
            System.out.println("Error reading file: " + e.getMessage());
            System.exit(1);
        }
    }

    // Reads trade requests from file and returns them as an ArrayList
    private static ArrayList<TradeRequest> readTradeRequests(String filename) {
        ArrayList<TradeRequest> requests = new ArrayList<>();
        try (Scanner scanner = new Scanner(new File(filename))) {
            while (scanner.hasNextLine()) {
                String[] parts = scanner.nextLine().split("\\s+");
                if (parts.length == 6) {
                    String id = parts[0], origin = parts[1], dest = parts[2], cat = parts[3];
                    double value = Double.parseDouble(parts[4]);
                    double tariff = Double.parseDouble(parts[5]);
                    requests.add(new TradeRequest(id, origin, dest, cat, value, tariff));
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + filename);
            System.exit(1);
        } catch (Exception e) {
            System.out.println("Error reading file: " + e.getMessage());
            System.exit(1);
        }
        return requests;
    }

    // Evaluates each trade request using the tariffs and prints the results
    private static void processTradeRequests(ArrayList<TradeRequest> requests, TariffList tariffList) {
        for (TradeRequest r : requests) {
            Tariff tariff = tariffList.getTariff(r.getOriginCountry(), r.getDestinationCountry(), r.getProductCategory());
            if (tariff != null) {
                String result = tariffList.evaluateTrade(r.getProposedTariff(), tariff.getMinimumTariff());
                displayTradeResult(r, result, tariff.getMinimumTariff());
            } else {
                System.out.println(r.getRequestId() + " - No tariff information found.");
            }
        }
    }

    // Displays the result of a trade request evaluation
    private static void displayTradeResult(TradeRequest r, String result, double minTariff) {
        System.out.println(r.getRequestId() + " - " + result + ".");
        if (result.equals("Accepted")) {
            System.out.println("Proposed tariff meets or exceeds the minimum.");
        } else if (result.equals("Conditionally Accepted")) {
            double surcharge = r.getTradeValue() * ((minTariff - r.getProposedTariff()) / 100);
            System.out.println("Proposed tariff " + r.getProposedTariff() + "% is close to the required " + minTariff + "%.");
            System.out.println("Surcharge of $" + (int)surcharge + " applied.");
        } else {
            System.out.println("Proposed tariff " + r.getProposedTariff() + "% is too low. Minimum is " + minTariff + "%.");
        }
        System.out.println();
    }

    // Allows user to search for tariffs through command line input
    private static void searchTariffs(TariffList tariffList, Scanner inputScanner) {
        System.out.println("\n=== Tariff Search ===");
        System.out.println("Enter details to search (type 'exit' to quit):");

        while (true) {
            System.out.print("Origin Country: ");
            String origin = inputScanner.nextLine().trim();
            if (origin.equalsIgnoreCase("exit")) break;

            System.out.print("Destination Country: ");
            String dest = inputScanner.nextLine().trim();

            System.out.print("Product Category: ");
            String cat = inputScanner.nextLine().trim();

            Tariff t = tariffList.getTariff(origin, dest, cat);
            if (t != null) {
                System.out.println("Found. Minimum tariff: " + t.getMinimumTariff() + "%");
            } else {
                System.out.println("No matching tariff found.");
            }
            System.out.println();
        }
    }

    // Demonstrates TariffList methods and functionality
    private static void testTariffListFunctionality() {
        System.out.println("\n=== Testing TariffList ===");
        TariffList list = new TariffList();

        Tariff t1 = new Tariff("USA", "China", "Electronics", 25.0);
        Tariff t2 = new Tariff("Japan", "USA", "Cars", 15.0);
        Tariff t3 = new Tariff("Germany", "France", "Goods", 10.0);

        list.addToStart(t1);
        list.addToStart(t2);
        list.insertAtIndex(t3, 1);

        System.out.println("List size: " + list.getSize());
        System.out.println("Contains USA->China Electronics? " + list.contains("USA", "China", "Electronics"));
        System.out.println("Contains France->Germany Food? " + list.contains("France", "Germany", "Food"));

        TariffList copy = new TariffList(list);
        System.out.println("Lists equal? " + list.equals(copy));

        list.deleteFromIndex(1);
        list.deleteFromStart();
        System.out.println("List size after deletions: " + list.getSize());
        System.out.println("Lists still equal? " + list.equals(copy));

        System.out.println("Evaluation tests:");
        System.out.println("25% vs 20%: " + list.evaluateTrade(25, 20));
        System.out.println("18% vs 20%: " + list.evaluateTrade(18, 20));
        System.out.println("15% vs 20%: " + list.evaluateTrade(15, 20));
    }

    // Main method to run the program
    public static void main(String[] args) {
        System.out.println("Welcome to the Tariff Management System - Part 2");

        String tariffFile = "input_files/Tariffs.txt";
        String requestFile = "input_files/TradeRequests.txt";

        TariffList tariffList = new TariffList();

        System.out.println("\nReading tariff data...");
        readTariffData(tariffFile, tariffList);
        System.out.println("Loaded " + tariffList.getSize() + " tariffs.");

        System.out.println("\nReading trade requests...");
        ArrayList<TradeRequest> requests = readTradeRequests(requestFile);
        System.out.println("Loaded " + requests.size() + " trade requests.");

        System.out.println("\n=== Processing Requests ===");
        processTradeRequests(requests, tariffList);

        Scanner inputScanner = new Scanner(System.in);
        searchTariffs(tariffList, inputScanner);
        inputScanner.close(); // Closing scanner to avoid resource leak

        testTariffListFunctionality();

        System.out.println("\nProgram finished.");
    }
}
