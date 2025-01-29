#include <iostream>
#include <string>
#include <map>
#include <iomanip> // For setting the precision of output
#include <limits>  // For numeric_limits

using namespace std;

// Base class for currency
class Currency {
public:
    string name;
    double exchangeRate;

    // Constructor
    Currency(const string& n, double rate) : name(n), exchangeRate(rate) {}
};

// Derived class for currency converter
class CurrencyConverter : public Currency { // Inheritance: CurrencyConverter derives from Currency
private:
    map<string, Currency> currencies; // Encapsulation

public:
    // Constructor initializes exchange rates
    CurrencyConverter() : Currency("", 0.0) { 
        currencies = {
            {"USD", Currency("US Dollar", 1.0)},
            {"EUR", Currency("Euro", 0.92)},
            {"GBP", Currency("British Pound", 0.79)},
            {"JPY", Currency("Japanese Yen", 156.13)},
            {"AUD", Currency("Australian Dollar", 1.50)},
            {"CAD", Currency("Canadian Dollar", 1.36)},
            {"CHF", Currency("Swiss Franc", 0.91)},
            {"CNY", Currency("Chinese Yuan", 7.23)},
            {"INR", Currency("Indian Rupee", 83.31)},
            {"RUB", Currency("Russian Ruble", 90.89)},
            {"PKR", Currency("Pakistani Rupee", 278.48)} 
        };
    }

    double convertCurrency(double amount, const string& from, const string& to) const {
        auto fromCurrency = currencies.find(from);
        auto toCurrency = currencies.find(to);

        if (fromCurrency != currencies.end() && toCurrency != currencies.end()) {
            // Polymorphism
            double convertedAmount = amount * (fromCurrency->second.exchangeRate / toCurrency->second.exchangeRate);
            return convertedAmount;
        } else {
            cout << "Currency not supported." << endl;
            return 0.0;
        }
    }

    void displayCurrencies() const {
        cout << "Available Currencies: ";
        for (const auto& pair : currencies) {
            cout << pair.first << " ";
        }
        cout << endl;
    }
};

int main() {
    CurrencyConverter converter;

    // Display available currencies
    converter.displayCurrencies();

    double amount;
    string fromCurrency, toCurrency;
    char choice;

    do {
        // Input validation for amount
        cout << "Enter the amount: ";
        while (!(cin >> amount)) {
            cout << "Invalid input. Please enter a valid number for the amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
        }

        // Input for 'from' currency
        cout << "Enter the currency to convert from: ";
        cin >> fromCurrency;

        // Input for 'to' currency
        cout << "Enter the currency to convert to: ";
        cin >> toCurrency;

        // Perform currency conversion
        double convertedAmount = converter.convertCurrency(amount, fromCurrency, toCurrency);

        // If conversion is successful, display the result
        if (convertedAmount != 0.0) {
            cout << fixed << setprecision(2);  // Set precision to 2 decimal places
            cout << amount << " " << fromCurrency << " is equivalent to " << convertedAmount << " " << toCurrency << endl;
        }

        // Ask if user wants to make another conversion
        cout << "Do you want to perform another conversion? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    return 0;
}

    