// ---------------------------------------------------------   
// Assignment 3
// Written by: Adam El-Zein 40298143
// For COMP 249 Section U – Winter 2025
// Represents a product with its basic info and pricing.
// ---------------------------------------------------------
package part1;

public class Product {
    private String productName;
    private String country;
    private String category;
    private double initialPrice;
    private double finalPrice;

    // Constructor
    public Product(String productName, String country, String category, double initialPrice) {
        this.productName = productName;
        this.country = country;
        this.category = category;
        this.initialPrice = initialPrice;
        this.finalPrice = initialPrice; // Start with same value
    }

    // Getters
    public String getProductName() {
        return productName;
    }

    public String getCountry() {
        return country;
    }

    public String getCategory() {
        return category;
    }

    public double getInitialPrice() {
        return initialPrice;
    }

    public double getFinalPrice() {
        return finalPrice;
    }

    // Setter for final price after tariff
    public void setFinalPrice(double finalPrice) {
        this.finalPrice = finalPrice;
    }

    // Output format for writing to file
    @Override
    public String toString() {
        return productName + "," + country + "," + category + "," + String.format("%.2f", finalPrice);
    }
}
