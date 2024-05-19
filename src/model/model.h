#ifndef MODEL_H_
#define MODEL_H_

#include <iostream>
#include <stack>
#include <string>
#include <list>

#define SPACE ' '

typedef enum {
    NULL_ELEMENT = -2,
    ERROR = -1,
    PLUS = 0,
    UN_PLUS = 1,
    MINUS = 2,
    UN_MINUS = 3,
    MUL = 4,
    DIV = 5,
    MOD = 6,
    POWER = 7,
    SIN = 8,
    COS = 9,
    TAN = 10,
    ASIN = 11,
    ACOS = 12,
    ATAN = 13,
    SQRT = 14,
    LN = 15,
    LOG = 16,
    OPEN_BRACKET = 17,
    CLOSE_BRACKET = 18,
    NUMBER = 19
} calcFunctionsEnum;

namespace s21 {
    typedef struct Calc {
        double value_;
        calcFunctionsEnum operation_;
        int priority_;
    } calc_t;

    class Model {
        private:
            std::stack<calc_t> operationsAndNumbers_;
        public:
            Model() {};
            ~Model() {};

            bool startCalc(std::string *str, double *result);

            calc_t parseOperation(std::string& str, int *element);
            calc_t parsePlusMinus(std::string& str, int *element);
            calc_t parseSinSqrt(std::string& str, int *element);
            calc_t parseArchFunctions(std::string& str, int* element);
            calc_t parseLogarithm(std::string& str, int* element);
            calc_t parseOperand(std::string& str, int* element);
            bool parse(std::string &str);

            bool checkCorrectStr(std::string &str);
            bool checkCorrectOperator(char element);
            bool checkBrackets(std::string &str);
            bool checkNumbers(std::string &str);

            void reverse();
            void calculate(double* result);
            calc_t calcTwo(std::stack<calc_t> *output, std::stack<calc_t> *operations);
            calc_t calcOne(std::stack<calc_t> *output, std::stack<calc_t> *operations);
            void pushToNotationStack(calc_t result, std::stack<calc_t> *output, std::stack<calc_t> *operations);
            
            void clean();
    };
}

#endif  // MODEL_H_