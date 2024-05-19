#include "controller.h"

namespace s21 {
    bool Controller::startCalc(std::string *str, double *result) {
        return model_.startCalc(str, result);
    }
}