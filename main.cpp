#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "tokens.h"
#include <cctype>

int main()
{

    std::ifstream inputfile; // variable for the file
    inputfile.open("input.txt");

    if (!inputfile.is_open())
    {
        std::cerr << "File not opened" << std::endl;
        return 1;
    }

    std::vector<std::string> tokens; // vector of tokens
    std::string line;                // holds each line to read
    std::string token;               // holds one token at a time

    while (std::getline(inputfile, line))
    { // while there's still a line to read from the file

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        char c; // c will hold each character at a time

        // This part will handle finding any comments and discarding whatever is after that
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos)
        {
            line = line.substr(0, commentPos); // make sure that line only holds the content from 0 to
                                               // but not including the first character of the comment ('/')
            ss.clear();
            ss.str(line);
        }

        while (ss.get(c)) // while there's still chars to read in ss
        {
            if (std::isspace(static_cast<unsigned char>(c))) // Checks if the char is a whitespace
            {
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
            }
            else if (std::ispunct(static_cast<unsigned char>(c))) // Checks if the char is a punctuation marking
            {
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
                std::string punct(1, c);
                tokens.push_back(punct);
            }
            else
            {
                token += c; // add the char to the current token
            }
        }
        if (!token.empty())
        {
            tokens.push_back(token); // add the token to the vector
            token.clear();           // free up the string to allow for the next token
        }
    }

    for (const auto &current : tokens)
    {
        std::cout << t << std::endl; // maybe soon something like  < lexicalAnalyzer(t); >
    }

    return 0;
}
