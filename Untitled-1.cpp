#include <iostream>
#include <string>

std::optional<int> evaluate(std::string const &expression) {
    std::cout << "Hello world";

    return std::nullopt;
}

int main() {
    auto result = evaluate("1 + 1");
    if (result) {
        std::cout << "Result: " << *result << "\n";
    } else {
        std::cout << "Could not evaluate expression.\n";
    }
}