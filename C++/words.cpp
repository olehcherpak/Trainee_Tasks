#include <fstream>
#include <string>
#include <map>
#include <algorithm>

inline bool is_not_alnum(char c)
{
    return !isalnum(c);
}

int main() {
    std::ifstream infile("task.in", std::ifstream::in);
    std::ofstream outfile("task.out", std::ofstream::out);
    std::map<std::string, unsigned> wordMap;
    
    for (std::string input; infile >> input;) {
        input.erase(std::remove_if(input.begin(), input.end(), is_not_alnum), input.end());
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        wordMap[input] += 1;
        
    }
    
    for (auto pairIter = wordMap.begin(); pairIter != wordMap.end(); pairIter++) {
        outfile << pairIter->first << " - " << pairIter->second << std::endl;
    }
    
    infile.close();
    outfile.close();
    
    return 0;
}
