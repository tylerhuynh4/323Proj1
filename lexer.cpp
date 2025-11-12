#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_set>

std::string removeComments(const std::string& code) {
    std::string cleaned = std::regex_replace(code, std::regex(R"(//.*)"), "");
    cleaned = std::regex_replace(cleaned, std::regex(R"(/\*[\s\S]*?\*/)"), "");
    return cleaned;
}

std::vector<std::pair<std::string, std::string>> tokenize(const std::string& code) {
    std::unordered_set<std::string> keywords = {"let", "function", "return"};
    std::unordered_set<std::string> operators = {"+", "-", "=", "==", "==="};
    std::unordered_set<char> separators = {'(', ')', '{', '}', ';', ','};

    std::vector<std::pair<std::string, std::string>> tokens;
    std::regex tokenRegex(R"([A-Za-z_]\w*|\d+|==|===|!=|!==|>=|<=|&&|\|\||[{}()\[\];,+\-*/=<>!])");
    for (auto it = std::sregex_iterator(code.begin(), code.end(), tokenRegex); it != std::sregex_iterator(); ++it) {
        std::string lexeme = it->str();
        std::string type;
        if (keywords.count(lexeme)) { 
            type = "keyword";
        } else if (operators.count(lexeme)) {
            type = "operator";
        } else if (lexeme.size() == 1 && separators.count(lexeme[0])) {
            type = "separator";
        } else if (std::regex_match(lexeme, std::regex(R"(\d+)"))) {
            type = "literal";
        } else {
            type = "identifier";
        }
        tokens.push_back({lexeme, type});
    }
    return tokens;
}