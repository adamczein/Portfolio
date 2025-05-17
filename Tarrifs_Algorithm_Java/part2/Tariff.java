// ---------------------------------------------------------   
// Assignment 3
// Written by: Adam El-Zein 40298143
// For COMP 249 Section U – Winter 2025
// Represents a tariff between two countries for a product category
// ---------------------------------------------------------

package part2;

public class Tariff {
    private String destinationCountry;
    private String originCountry;
    private String productCategory;
    private double minimumTariff;

    // Constructor
    public Tariff(String destinationCountry, String originCountry, String productCategory, double minimumTariff) {
        this.destinationCountry = destinationCountry;
        this.originCountry = originCountry;
        this.productCategory = productCategory;
        this.minimumTariff = minimumTariff;
    }

    // Copy constructor
    public Tariff(Tariff other) {
        this.destinationCountry = other.destinationCountry;
        this.originCountry = other.originCountry;
        this.productCategory = other.productCategory;
        this.minimumTariff = other.minimumTariff;
    }

    // Clone method
    public Tariff clone() {
        return new Tariff(this);
    }

    // Getters and setters
    public String getDestinationCountry() {
        return destinationCountry;
    }

    public void setDestinationCountry(String destinationCountry) {
        this.destinationCountry = destinationCountry;
    }

    public String getOriginCountry() {
        return originCountry;
    }

    public void setOriginCountry(String originCountry) {
        this.originCountry = originCountry;
    }

    public String getProductCategory() {
        return productCategory;
    }

    public void setProductCategory(String productCategory) {
        this.productCategory = productCategory;
    }

    public double getMinimumTariff() {
        return minimumTariff;
    }

    public void setMinimumTariff(double minimumTariff) {
        this.minimumTariff = minimumTariff;
    }

    // Converts object to string
    @Override
    public String toString() {
        return "Tariff [destinationCountry=" + destinationCountry + ", originCountry=" + originCountry
                + ", productCategory=" + productCategory + ", minimumTariff=" + minimumTariff + "]";
    }

    // Checks if two Tariff objects are equal
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Tariff other = (Tariff) obj;
        return Double.compare(other.minimumTariff, minimumTariff) == 0
                && destinationCountry.equals(other.destinationCountry)
                && originCountry.equals(other.originCountry)
                && productCategory.equals(other.productCategory);
    }
}
