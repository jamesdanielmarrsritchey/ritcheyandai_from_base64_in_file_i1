#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/*
To compile and install the program on Debian, you can follow these steps:

1. Install the g++ compiler if it's not already installed. You can do this by running the following command in your terminal:
   sudo apt-get install g++

2. Navigate to the directory containing the source code file (let's call it base64.cpp) using the cd command.

3. Compile the source code file using the g++ compiler. You can do this by running the following command in your terminal:
   g++ -o base64 base64.cpp

4. Now, you can run the program using the following command:
   ./base64 --source_file "path_to_your_file"

Please replace "path_to_your_file" with the path to the file you want to decode from Base64.
*/

const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

int pos_of_char(const char c) {
    return base64_chars.find(c);
}

std::string base64_decode(const std::string &input) {
    std::string ret;
    int val = 0;
    int valb = -8;
    for (auto c : input) {
        if (c == '=') break;
        val = (val<<6) + pos_of_char(c);
        valb += 6;
        if (valb >= 0) {
            ret.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return ret;
}

int main(int argc, char* argv[]) {
    std::string input;
    std::string source_file;
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "--source_file" && i + 1 < argc) {
            source_file = argv[++i];
        }
    }
    std::ifstream file(source_file, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open source file.\n";
        return 1;
    }
    std::getline(file, input, '\0');
    std::cout << base64_decode(input);

    return 0;
}