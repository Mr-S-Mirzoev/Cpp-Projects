#include <iostream>
#include <string>

std::pair <int, int> get_val_coef_part (std::string s) {
    auto len = s.length();
    
    if (s[len - 1] == 'x') {
        if (len > 2)
            return {0, std::stoi(s.substr(0, len - 1))};
        else
            return {0, (s[0] == '+') ? 1 : -1};
    } else {
        if (len > 1)
            return {std::stoi(s.substr(0, len)), 0};
        else
            return {(s[0] == '+') ? 1 : -1, 0};
    }
}

std::pair <int, int> get_val_coef (std::string s) {
    if (s[0] != '-' && s[0] != '+') 
        s = "+" + s;

    std::size_t prev_position = 0;
    std::size_t position = 0;
    std::size_t pos_, neg_;

    int val = 0, coef = 0;
    std::pair<int, int> part;

    while (position != std::string::npos) {
        pos_ = s.find('+', position + 1);
        neg_ = s.find('-', position + 1);

        position = pos_;
        if (pos_ == std::string::npos || (neg_ != std::string::npos && pos_ > neg_))
            position = neg_;

        part = get_val_coef_part(s.substr(prev_position, position - prev_position));
        val += part.first;
        coef += part.second;

        prev_position = position;
    }

    return {val, coef};
}

std::string solveEquation(std::string equation) {
    auto eq = equation.find('=');
    auto l_coef = get_val_coef(equation.substr(0, eq));
    auto r_coef = get_val_coef(equation.substr(eq + 1));

    auto val = l_coef.first - r_coef.first;
    auto coef = r_coef.second - l_coef.second;

    if (coef == 0)
        if (val == 0)
            return "Infinite solutions";
        else 
            return "No solution";

    return "x=" + std::to_string(val / coef);
}

int main(int argc, char const *argv[])
{
    std::cout << solveEquation(argv[1]) << std::endl;
    return 0;
}
