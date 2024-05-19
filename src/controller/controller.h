#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
    class Controller {
        private:
            s21::Model model_;
        public:
            Controller() {};
            ~Controller() {};
            bool startCalc(std::string *str, double *result);
    };
}

#endif  // CONTROLLER_H_