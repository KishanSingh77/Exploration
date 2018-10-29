#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

struct VWAPCalculator {
    double sharesTraded; 
    double totalPrice;
    VWAPCalculator() :  sharesTraded(0), totalPrice(0) {}

    void processTrade(std::string line) {
        int pos = line.find(",");
        double curSharesTraded = std::stod(line.substr(0, pos));
        double curPricePerShare = std::stod(line.substr(pos + 1));
        totalPrice += curSharesTraded * curPricePerShare;
        sharesTraded += curSharesTraded;
    }

    double getValue() {
        if (sharesTraded == 0) {
            return 0;
        }
        return totalPrice / sharesTraded;
    }
};

// Main function for parsing input and displaying output
// You should not have to change this in your final solution
int main(int argc, char** argv) {
    //Check inputs
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " [CSV Input File]" << std::endl;
        return 1;
    }

    const std::string input_file(argv[1]);
    if(input_file.empty()) {
        std::cerr << "Invalid input file (parameter 1)" << std::endl;
        return 1;
    }

    std::ifstream input_stream(input_file);
    if(!input_stream.is_open()) {
        std::cerr << "Could not open input file " << input_file << std::endl;
        return 1;
    }

    // Create an instance of calculator.
    VWAPCalculator calculator;

    // Iterate through the input file.
    std::string line;
    while (std::getline(input_stream, line)) {
        calculator.processTrade(line);
    }

    // Print output.
    std::cout << std::setprecision(3) << std::showpoint << std::fixed;
    std::cout << "VWAP: " << calculator.getValue() << std::endl;

    return 0;
}