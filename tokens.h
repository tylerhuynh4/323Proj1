#pragma once
#include <string>
#include <unordered_set>
#include <regex>

inline std::string classifyToken(const std::string &token) {        // inline allows compile in header file w/o multiple definition errors

    static const std::unordered_set<std::string> keywords = {
        "let", "const", "function", "return", "if", "else", "for", "while", "var", "true", "false"
    };

    static const std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "=", "==", "===", "!=", "!==", ">", "<", ">=", "<=", "&&", "||", "!"
    };

    static const std::unordered_set<std::string> separators = {
        "(", ")", "{", "}", ";", ",", "[", "]"
    };
    
    // checks if token is known or matches from set
    if (keywords.count(token)) {    
        return "keyword";
    }
    if (operators.count(token)) {
        return "operator";
    } 
    if (separators.count(token)) {
        return "separator";
    }
    if (std::regex_match(token, std::regex(R"(\d+)"))) {    // purely digits
        return "literal";
    }
    if (std::regex_match(token, std::regex(R"(["'][^"']*["'])"))) {
        return "string literal";
    }
    return "identifier";
}