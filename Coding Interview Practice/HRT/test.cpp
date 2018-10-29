#include <iostream>
#include <string> 

double convert(std::string &time) {
      double total_ms = 0;
      total_ms += std::stod(time.substr(time.find(".") + 1));
      total_ms += std::stod(time.substr(6, 2)) * 1000;
      total_ms += std::stod(time.substr(3, 2)) * 60000;
      total_ms += std::stod(time.substr(0, 2)) * 3600000;
      return total_ms;
}

int main(){
  std::string s = "24:59:59.999";
  std::cout << convert(s) << std::endl;
}
