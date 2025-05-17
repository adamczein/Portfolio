// ---------------------------------------------------------
// Assignment 3
// Written by: Adam El-Zein 40298143
// For COMP 249 Section U – Winter 2025
// Interface for trade evaluation based on tariffs.
// ---------------------------------------------------------

package part2;

public interface TariffPolicy {

    // Checks if a trade is acceptable based on tariffs
    String evaluateTrade(double proposedTariff, double minimumTariff);
}
