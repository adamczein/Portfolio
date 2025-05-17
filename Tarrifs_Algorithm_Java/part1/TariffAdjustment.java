// ---------------------------------------------------------   
// Assignment 3
// Written by: Adam El-Zein 40298143
// For COMP 249 Section U – Winter 2025
// This program reads product data, applies tariffs, sorts it, and writes the result to a file.
// ---------------------------------------------------------
package part1;

import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class TariffAdjustment {

    // Reads product data from a file
    private static ArrayList<Product> readDataFromFile(String filename) {
        ArrayList<Product> products = new ArrayList<>();

        try (Scanner scanner = new Scanner(new File(filename))) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] parts = line.split(",");

                if (parts.length == 4) {
                    String productName = parts[0];
                    String country = parts[1];
                    String category = parts[2];
                    double initialPrice = Double.parseDouble(parts[3]);

                    Product product = new Product(productName, country, category, initialPrice);
                    products.add(product);
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error: File not found - " + filename);
            System.exit(1);
        } catch (Exception e) {
            System.out.println("Error reading file: " + e.getMessage());
            System.exit(1);
        }

        return products;
    }

    // Applies tariff rates based on country and category
    private static void applyTariffs(ArrayList<Product> products) {
        for (Product product : products) {
            double tariffRate = 0.0;
            String country = product.getCountry();
            String category = product.getCategory();

            if (country.equals("China")) {
                tariffRate = 0.25;
            } else if (country.equals("USA") && category.equals("Electronics")) {
                tariffRate = 0.10;
            } else if (country.equals("Japan") && category.equals("Automobiles")) {
                tariffRate = 0.15;
            } else if (country.equals("India") && category.equals("Agriculture")) {
                tariffRate = 0.05;
            } else if (country.equals("South Korea") && category.equals("Electronics")) {
                tariffRate = 0.08;
            } else if (country.equals("Saudi Arabia") && category.equals("Energy")) {
                tariffRate = 0.12;
            } else if (country.equals("Germany") && category.equals("Manufacturing")) {
                tariffRate = 0.06;
            } else if (country.equals("Bangladesh") && category.equals("Textile")) {
                tariffRate = 0.04;
            } else if (country.equals("Brazil") && category.equals("Agriculture")) {
                tariffRate = 0.09;
            }

            double finalPrice = product.getInitialPrice() * (1 + tariffRate);
            product.setFinalPrice(finalPrice);
        }
    }

    // Sorts products by name
    private static void sortProductsByName(ArrayList<Product> products) {
        Collections.sort(products, new Comparator<Product>() {
            @Override
            public int compare(Product p1, Product p2) {
                return p1.getProductName().compareTo(p2.getProductName());
            }
        });
    }

    // Writes updated product data to a file
    private static void writeDataToFile(ArrayList<Product> products, String filename) {
        try (PrintWriter writer = new PrintWriter(new File(filename))) {
            for (Product product : products) {
                writer.println(product.toString());
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error: Could not create file - " + filename);
            System.exit(1);
        } catch (Exception e) {
            System.out.println("Error writing to file: " + e.getMessage());
            System.exit(1);
        }
    }

    // Main program flow
    public static void main(String[] args) {
        System.out.println("Welcome to the Tariff Management System - Part 1");

        String inputFile = "input_files/TradeData.txt";
        String outputFile = "input_files/UpdatedTradeData.txt";

        ArrayList<Product> products = readDataFromFile(inputFile);
        System.out.println("Read " + products.size() + " products from " + inputFile);

        applyTariffs(products);
        System.out.println("Applied tariff adjustments");

        sortProductsByName(products);
        System.out.println("Sorted products by name");

        writeDataToFile(products, outputFile);
        System.out.println("Wrote updated data to " + outputFile);

        System.out.println("\nProgram done!");
    }
}
