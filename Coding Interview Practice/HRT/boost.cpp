#include <boost/algorithm/string.hpp>
 
std::string text = "Let me split this into words";
std::vector<std::string> results;
 
boost::split(results, text, [](char c){return c == ' ';});

for (int i = 0; i < result.size(); i++) {
  cout << result[i] << ' ';
}
cout << endl;
