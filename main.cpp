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
            // variable used to track the position of the closing parenthesis
            int ending = 0;
            for (int j = i + 1; j < exp.size(); j++) {
                // if we find closing parenthesis note location
                // we do not break as we want to find the last closing parenthesis
                if (exp[j] == ')') {
                    ending = j;
                }
            }
            // if no closing parenthesis was found return an error
            if (ending == 0) {
                //std::cerr << "Error: Mismatched parentheses in expression: " << expression << "\n";
                return std::nullopt;
            }
            // replace the entire parenthetical expression with the result of the evaluation
            //std::cout << "Found sub-expression: " << exp.substr(i + 1, ending - i - 1) << "\n";
            // recursively call evaluate on the sub expression
            std::optional<int> subexp = evaluate(exp.substr(i + 1, ending - i - 1));
            // if sub expression is invalid we return an error , this allows us to propagate the errors recursively
            if (!subexp) {
                //std::cerr << "Error: Invalid sub-expression: " << exp.substr(i + 1, ending - i - 1) << "\n";
                return std::nullopt;
            }
            // replace the entire parenthetical expression with the result of the evaluation
            exp.replace(i, ending - i + 1, std::to_string(*subexp));
        }
    }

    // evaluate the rest of the string from left to right ignoring operator precedence
    // set the initial result to the first integer in expression
    int result = 0;
    // keep track of the current operator
    char current_op = '+';
    // loop through the string looking for digits and operators
    for (int i = 0; i < exp.size(); i++) {
        //if a digit is found we check consecutively for more digits
        if (isdigit(exp[i])){
            int start = i;
            while (i < exp.size() && isdigit(exp[i])) {
                i++;
                
            }
            // we then convert the substring to an integer
            int num = std::stoi(exp.substr(start, i - start));
            // check if the number is negative
            if (i > 0 && exp[start-1] == '-') {
                num = -num;
            }
            //std::cout << "Applying operator: " << current_op << " to " << result << " and " << num << "\n";
            // apply the current operator to the result and the new number
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
            //std::cout << "Changed operator to: " << exp[i] << "\n";
            current_op = exp[i];
        }
    }

    //std::cout << "Evaluated expression: " << expression << " = " << result << "\n";

    return result;
}

//test function using all the examples given in the prompt
//I have left all my debug prints in to show my thought process
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