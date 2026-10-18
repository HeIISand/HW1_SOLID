#ifndef HW1_SOLID_CONSOLEVIEW_H
#define HW1_SOLID_CONSOLEVIEW_H

#pragma once
#include "../Interfaces/IView.h"
#include <iostream>
#include <string>

class StandardConsoleView : public IView {
public:

    void print(const std::string& message) const override {
        std::cout << message << std::endl;
    }

    int readInt() const override {
        std::string input;
        while (true) {
            std::cin >> input;
            try {
                return std::stoi(input);
            }
            catch (...) {
                std::cout << "Ошибка. Попробуйте еще раз:\n";
            }
        }
    }
};

#endif
