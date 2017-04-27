#include <iostream>
#include <fstream>
#include <set>
#include <ctype.h>

int main() {
    std::set<char> charSet;
    std::ifstream infile("task.in", std::ifstream::in);
    std::ofstream outfile("task.out", std::ofstream::out);
    
    for (char input; infile.good();) {
        infile >> input;
        
        if (isalpha(input) && charSet.find(input) == charSet.end()) {
            charSet.insert(tolower(input));
        }
    }
    
    for (auto letter = charSet.begin(); letter != charSet.end(); letter++) {
        outfile << *letter;
    }
    outfile << '\n';
    
    infile.close();
    outfile.close();
    
    return 0;
}