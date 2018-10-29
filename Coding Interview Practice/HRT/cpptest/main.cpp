#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class PatternDetector
{
public:

   PatternDetector(int pattern_length, int number_of_repetitions, int time_window)
   {
      patternLength = pattern_length;
      numOfRepetitions = number_of_repetitions;
      curPrices = std::vector<double>();
      curSize = 1;
      timeWindow = time_window;
   }

   ~PatternDetector()
   {
   }

   
   bool check() {
      assert((int) curPrices.size() == numOfRepetitions * patternLength);
      if (numOfRepetitions == 1) {
        return true;
      }
      bool patternExists = true;
      for (int i = 1; i < numOfRepetitions; i++) {
          int index = i * patternLength;
          for (int j = index; j < index + patternLength; j++) {
              if (curPrices[j] != curPrices[j - index]) {
                  patternExists = false;
                  break;
              }
          }
      }
      if (timeWindow == 0) {
          return patternExists;
      }
      double minTime = 1e9, maxTime = -1;
      for (int i = 0; i < times.size(); i++) {
          minTime = std::min(minTime, times[i]);
          maxTime = std::max(maxTime, times[i]);
      }
      if (maxTime - minTime > timeWindow) {
        patternExists = false; 
      }
      return patternExists;
   }

   double convert(const std::string &time) {
      double total_ms = 0;
      total_ms += std::stod(time.substr(time.find(".") + 1));
      total_ms += std::stod(time.substr(6, 2)) * 1000;
      total_ms += std::stod(time.substr(3, 2)) * 60000;
      total_ms += std::stod(time.substr(0, 2)) * 3600000;
      return total_ms;
   }

   bool detectPattern(const std::string& time, double price)
   {
        bool patternExists = false;
        if (curSize < patternLength * numOfRepetitions) {
            curPrices.push_back(price);
            times.push_back(convert(time));
            curSize += 1;
        } else {
            curPrices.push_back(price);
            times.push_back(convert(time));
            patternExists = check();
            curPrices.erase(curPrices.begin());
            times.erase(times.begin());
        }
        return patternExists;
   }

private:
    int patternLength;
    int numOfRepetitions;
    int curSize;
    int patternSize;
    int timeWindow;
    std::vector<double> curPrices;
    std::vector<double> times;
};

///////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    //Check inputs

    if(argc < 4)
    {
        std::cerr << "Usage: PatternDetector [pattern length] [repetition count] [CSV input file]"
                  << std::endl << std::endl
                  <<" example: PatternDetector 2 3 sample_input.csv"
                  << std::endl;
        return 1;
    }

    const int pattern_length = std::atoi(argv[1]);

    if(pattern_length <= 0)
    {
        std::cerr << "Invalid pattern length (parameter 1)"
                  << std::endl;
        return 1;
    }

    const int number_of_repetitions = std::atoi(argv[2]);

    if(number_of_repetitions <= 0)
    {
        std::cerr << "Invalid repetition count (parameter 2)"
                  << std::endl;
        return 1;
    }


    const std::string input_file(argv[3]);

    if(input_file.empty())
    {
        std::cerr << "Invalid input file (parameter 3)"
                  << std::endl;
        return 1;
    }


    std::ifstream input_stream(input_file);
    if(!input_stream.is_open())
    {
        std::cerr << "Could not open input file " << input_file << std::endl;
        return 1;
    }

    int time_window = 0;
    if (argc == 5) {
      time_window = std::atoi(argv[4]);
    }
    // Create an instance of pattern detector.

    PatternDetector detector(pattern_length, number_of_repetitions, time_window);

    // Process input file.
    std::string line;
    std::string token;
    while(getline(input_stream, line))
    {
        std::string time;
        double price;

        std::istringstream string_stream(line);
        getline(string_stream, token, ',');
        time = token;

        getline(string_stream, token, ',');
        price = atof(token.c_str());

        // run price value through pattern detector

        const bool pattern_detected = detector.detectPattern(time, price);

        // *** Do not modify this output ***

        std::cout << time << ','
                  << price << ','
                  << (pattern_detected ? "True" : "False")
                  << std::endl;
    }

    return 0;
}
