#include <iostream>
#include <string>
#include <optional>
#include <cassert>

//goal is to write a recursive function that looks for parentheses in a string expression. If it finds none it then solves the expression
std::optional<int> evaluate(std::string const &expression) {
    // create a copy of the string to modify
    std::string exp = expression;
    // loop through the string looking for sub expressions in parentheses
    for (int i = 0; i < exp.size(); i++) {
        // if one is located find the closing parenthesis position
        if (exp[i] == '('){
            bool ending = false;
            for (int j = i + 1; j < exp.size(); j++) {
                if (exp[j] == ')') {
                    ending = true;
                    // recursively call evaluate on the sub expression
                    // replace the entire parenthetical expression with the result of the evaluation
                    std::cout << "Found sub-expression: " << exp.substr(i + 1, j - i - 1) << "\n";
                    exp.replace(i, j - i + 1, std::to_string(*evaluate(exp.substr(i + 1, j - i - 1))));
                }
            }
        }
    }

    // evaluate the rest of the string from left to right ignoring operator precedence
    // set the initial result to the first integer in expression
    int result = 0;
    std::cout << "Initial result set to: " << result << "\n";
    // keep track of the current operator
    char current_op = '+';
    // loop through the string looking for digits and operators
    for (int i = 0; i < exp.size(); i++) {
        //if a digit is found apply the current operator to the result and the digit
        if (isdigit(exp[i])){
            int num = exp[i] - '0';
            if (i > 0 && exp[i-1] == '-') {
                num = -num;
            }
            std::cout << "Applying operator: " << current_op << " to " << result << " and " << num << "\n";
            switch(current_op) {
                case '+':
                    result += num;
                    break;
                case '-':
                    result -= num;
                    break;
                case '*':
                    result *= num;
                    break;
                case '/':
                    result /= num;
                    break;
            }
        // if an operator is found set the current operator to it ensuring to ignore whitespace
        } else if (!isdigit(exp[i+1]) && exp[i] != ' ') {
            std::cout << "Changed operator to: " << exp[i] << "\n";
            current_op = exp[i];
        }
    }


    std::cout << "Evaluated expression: " << expression << " = " << result << "\n";

    return result;
}

//test function
void test_evaluate() {
    assert(evaluate("1 + 3") == 4);
    assert(evaluate("-2 + 3") == 1);
    assert(evaluate("(1 + 3) * 2") == 8);
    assert(evaluate("(1 + -3) * 2") == -4);
    assert(evaluate("(4 / 2) + 6") == 8);
    assert(evaluate("4 + (12 / (1 * 2))") == 10);
    assert(evaluate("(1 + (12 * 2)") == std::nullopt); 
}

int main() {
    test_evaluate();
}