#include "model.h"

namespace s21 {
    bool Model::startCalc(std::string *str, double *result) {
        bool checkedResult = parse(*str);
        if (checkedResult) {
            calculate(result);
        }
        else {
            clean();
        }
        return checkedResult;
    }

    void Model::clean() {
        while(!operationsAndNumbers_.empty()) {
            operationsAndNumbers_.pop();
        }
    }

    void Model::reverse() {
        std::stack<calc_t> tempStack;
        while (!operationsAndNumbers_.empty()) { 
            calc_t item = operationsAndNumbers_.top();
            operationsAndNumbers_.pop();
            tempStack.push(item);
        }
        operationsAndNumbers_ = tempStack;
    }

    calc_t Model::calcTwo(std::stack<calc_t> *output, std::stack<calc_t> *operations) {
        calc_t result;
        calc_t operationsIterator = operations->top();
        calc_t outputIterator = output->top();
        output->pop();
        if (operationsIterator.operation_ == PLUS) {
            result.value_ = output->top().value_ + outputIterator.value_;
        } else if (operationsIterator.operation_ == MINUS) {
            result.value_ = output->top().value_ - outputIterator.value_;
        } else if (operationsIterator.operation_ == DIV) {
            result.value_ = output->top().value_ / outputIterator.value_;
        } else if (operationsIterator.operation_ == MUL) {
            result.value_ = output->top().value_ * outputIterator.value_;
        } else if (operationsIterator.operation_ == POWER) {
            result.value_ = pow(output->top().value_, outputIterator.value_);
        }
        return result;
    }

    calc_t Model::calcOne(std::stack<calc_t> *output, std::stack<calc_t> *operations) {
        calc_t result;
        calc_t operationsIterator = operations->top();
        calc_t outputIterator = output->top();
        if (operationsIterator.operation_ == SIN) {
            result.value_ = sin(outputIterator.value_);
        } else if (operationsIterator.operation_ == COS) {
            result.value_ = cos(outputIterator.value_);
        } else if (operationsIterator.operation_ == TAN) {
            result.value_ = tan(outputIterator.value_);
        } else if (operationsIterator.operation_ == ASIN) {
            result.value_ = asin(outputIterator.value_);
        } else if (operationsIterator.operation_ == ACOS) {
            result.value_ = acos(outputIterator.value_);
        } else if (operationsIterator.operation_ == ATAN) {
            result.value_ = atan(outputIterator.value_);
        } else if (operationsIterator.operation_ == SQRT) {
            result.value_ = sqrt(outputIterator.value_);
        } else if (operationsIterator.operation_ == LN) {
            result.value_ = log(outputIterator.value_);
        } else if (operationsIterator.operation_ == LOG) {
            result.value_ = log10(outputIterator.value_);
        } else if (operationsIterator.operation_ == OPEN_BRACKET) {
            result.value_ = outputIterator.value_;
        } else if (operationsIterator.operation_ == MOD) {
            output->pop();
            result.value_ = fmod(output->top().value_, outputIterator.value_);
        }
        return result;
    }

    void Model::pushToNotationStack(calc_t result, std::stack<calc_t> *output, std::stack<calc_t> *operations) {
        output->pop();
        operations->pop();
        output->push(result);
    }

    void Model::calculate(double* result) {
        reverse();
        std::stack<calc_t> output;
        std::stack<calc_t> operations;
        calc_t structResult;
        output.push({0, NULL_ELEMENT, -1});
        operations.push({0, NULL_ELEMENT, -1});
        while (!operationsAndNumbers_.empty()) {
            if (operationsAndNumbers_.top().priority_ == 0) {
                output.push(operationsAndNumbers_.top());
                operationsAndNumbers_.pop();
            } else if (operationsAndNumbers_.top().priority_ > 0 && operationsAndNumbers_.top().priority_ < 4) {
                if (operationsAndNumbers_.top().priority_ > operations.top().priority_ || operations.top().priority_ == 4) {
                    operations.push(operationsAndNumbers_.top());
                    operationsAndNumbers_.pop();
                } else {
                    structResult = calcTwo(&output, &operations);
                    pushToNotationStack(structResult, &output, &operations);
                }
            } else if (operationsAndNumbers_.top().priority_ == 4) {
                if (operationsAndNumbers_.top().operation_ == CLOSE_BRACKET) {
                    while (operations.top().priority_ != 4) {
                        structResult = calcTwo(&output, &operations);
                        pushToNotationStack(structResult, &output, &operations);
                    }
                    structResult = calcOne(&output, &operations);
                    pushToNotationStack(structResult, &output, &operations);
                    operationsAndNumbers_.pop();
                } else {
                    operations.push(operationsAndNumbers_.top());
                    operationsAndNumbers_.pop();
                }
            }
        }
        while (operations.top().operation_ != NULL_ELEMENT) {
            if (operations.top().priority_ != 4) {
                structResult = calcTwo(&output, &operations);
                pushToNotationStack(structResult, &output, &operations);
            } else {
                structResult = calcOne(&output, &operations);
                pushToNotationStack(structResult, &output, &operations);
            }
        }
        *result = output.top().value_;
    }

   calc_t Model::parseOperand(std::string& str, int* element) {
        char number[256];
        int j = 0;
        while (isdigit(str[*element]) || str[*element] == '.') {
            number[j] = str[*element];
            j++;
            number[j] = '\0';
            *element += 1;
        }
        *element -= 1;
        return {strtod(number, NULL), NUMBER, 0};
    }

    calc_t Model::parsePlusMinus(std::string& str, int *element) {
        calc_t toReturn;
        if (*element > 0) {
            if (str[*element - 1] == '(') {
                str[*element] == '+' ? toReturn = {0, UN_PLUS, 0} : toReturn = {0, UN_MINUS, 4};
            } else {
                str[*element] == '+' ? toReturn = {0, PLUS, 1} : toReturn = {0, MINUS, 1};
            }
        } else if (*element == 0) {
            str[*element] == '+' ? toReturn = {0, UN_PLUS, 0} : toReturn = {0, UN_MINUS, 4};
        }
        return toReturn;
    }

    calc_t Model::parseSinSqrt(std::string& str, int* element) {
        calc_t toReturn;
        if (str[*element + 1] == 'i' && str[*element + 2] == 'n' && str[*element + 3] == '(') {
            toReturn = {0, SIN, 4};
            *element += 3;
        } else if (str[*element + 1] == 'q' && str[*element + 2] == 'r' && str[*element + 3] == 't' && str[*element + 4] == '(') {
            toReturn = {0, SQRT, 4};
            *element += 4;
        } else {
            throw std::length_error("wrong function!");
        }
        return toReturn;
    }

    calc_t Model::parseArchFunctions(std::string& str, int* element) {
        calc_t toReturn;
        if (str[*element + 1] == 'c' && str[*element + 2] == 'o' && str[*element + 3] == 's' && str[*element + 4] == '(') {
            *element += 4;
            toReturn = {0, ACOS, 4};
        } else if (str[*element + 1] == 's' && str[*element + 2] == 'i' && str[*element + 3] == 'n' && str[*element + 4] == '(') {
            *element += 4;
            toReturn = {0, ASIN, 4};
        } else if (str[*element + 1] == 't' && str[*element + 2] == 'a' && str[*element + 3] == 'n' && str[*element + 4] == '(') {
            *element += 4;
            toReturn = {9, ATAN, 4};
        } else {
            throw std::length_error("wrong function!");
        }
        return toReturn;
    }

    calc_t Model::parseLogarithm(std::string& str, int* element) {
        calc_t toReturn;
        if (str[*element + 1] == 'n' && str[*element + 2] == '(') {
            *element += 2;
            toReturn = {0, LN, 4};
        } else if (str[*element + 1] == 'o' && str[*element + 2] == 'g' && str[*element + 3] == '(') {
            *element += 3;
            toReturn = {0, LOG, 4};
        } else {
            throw std::length_error("wrong function!");
        }
        return toReturn;
    }

    calc_t Model::parseOperation(std::string &str, int *element) {
        std::stack<calc_t> result;
        if (str[*element] == '+' || str[*element] == '-') {
            result.push(parsePlusMinus(str, element));
        } else if (str[*element] == '*') {
            result.push({0, MUL, 2});
        } else if (str[*element] == '/') {
            result.push({0, DIV, 2});
        } else if (str[*element] == '^') {
            result.push({0, POWER, 3});
        } else if (str[*element] == 's') {
            result.push(parseSinSqrt(str, element));
        } else if (str[*element] == 'c') {
            if (str[*element + 1] == 'o' && str[*element + 2] == 's' && str[*element + 3] == '(') {
                *element += 3;
                result.push({0, COS, 4});
            }
        } else if (str[*element] == 't') {
            if (str[*element + 1] == 'a' && str[*element + 2] == 'n' && str[*element + 3] == '(') {
                *element += 3;
                result.push({0, TAN, 4});
            }
        } else if (str[*element] == 'a') {
            result.push(parseArchFunctions(str, element));
        } else if (str[*element] == 'l') {
            result.push(parseLogarithm(str, element));
        } else if (str[*element] == 'm') {
            if (str[*element + 1] == 'o' && str[*element + 2] == 'd') {
                *element += 2;
                result.push({0, MOD, 4});
            }
        } else if (str[*element] == '(') {
            result.push({0, OPEN_BRACKET, 4});
        } else if (str[*element] == ')') {
            result.push({0, CLOSE_BRACKET, 4});
        } else {
            result.push({0, ERROR, 100});
        }
        return result.top();
    }

    bool Model::checkCorrectStr(std::string &str) {
        bool checkedResult = true;
        const char *strSpecialFunc = "sincotaqrlg()";
        if (!checkBrackets(str) || !checkNumbers(str)) {
            checkedResult = false;
        }
        for (int iterator = 0; iterator != int(str.size()) && checkedResult != false; iterator++) {
            if (str[iterator] == SPACE || str[iterator] == '.') {
                continue;
            } else if (!checkCorrectOperator(str[iterator]) && !isdigit(str[iterator]) && !strchr(strSpecialFunc, str[iterator])) {
                checkedResult = false;
                if (str[iterator] == 'm' && str[iterator + 1] == 'o' && str[iterator + 2] == 'd') {
                    checkedResult = true;
                    iterator += 2;
                }
            } else if (checkCorrectOperator(str[iterator]) && str[iterator + 1] == '\0' && !strchr(strSpecialFunc, str[iterator])) {
                checkedResult = false;
            } else if (isdigit(str[iterator]) && str[iterator + 1] == '(' && !strchr(strSpecialFunc, str[iterator])) {
                checkedResult = false;
            }
        }
        return checkedResult;
    }

    bool Model::checkNumbers(std::string &str) {
        bool checkedResult = true;
        for (int iterator = 0; iterator != (int)str.size(); iterator++) {
            if (str[iterator] == '.') {
                if (!isdigit(str[iterator - 1]) || !isdigit(str[iterator + 1])) {
                    checkedResult = false;
                }
            }
        }
        return checkedResult;
    }

    bool Model::checkCorrectOperator(char element) {
        return (element == '+' ||element == '-' || element == '*' || element == '/' || element == '^');
    }

    bool Model::checkBrackets(std::string &str) {
        bool checkedResult = true;
        int countOpenBrackets = -1;
        int countCloseBrackets = -1;
        for (int iterator = 0; iterator != int(str.size()); iterator++) {
            if (str[iterator] == '(' && str[iterator + 1] != ')') {
                countOpenBrackets++;
            } else if (str[iterator] == ')' && str[iterator] != '(') {
                countCloseBrackets++;
            }
        }
        if (abs(countOpenBrackets) != countCloseBrackets && countOpenBrackets != countCloseBrackets) {
            checkedResult = false;
        }
        return checkedResult;
    }

        bool Model::parse(std::string &str) {
        calc_t object;
        bool checkedResult = checkCorrectStr(str);
        for (int iterator = 0; iterator != (int)str.size(); iterator++) {
            if (str[iterator] != SPACE && !isdigit(str[iterator])) {
                object = parseOperation(str, &iterator);
                if (object.operation_ != ERROR && object.operation_ != UN_PLUS && object.operation_ != UN_MINUS) {
                    operationsAndNumbers_.push(object);
                } else if (object.operation_ == UN_PLUS) {
                    continue;
                } else if (object.operation_ == UN_MINUS) {
                    operationsAndNumbers_.push({0, MINUS, 1});
                    operationsAndNumbers_.push({0, NUMBER, 0});
                } else {
                    checkedResult = false;
                }
            } else if (str[iterator] != SPACE) {
                object = parseOperand(str, &iterator);
                operationsAndNumbers_.push(object);
            }
        }
        return checkedResult;
    }
}