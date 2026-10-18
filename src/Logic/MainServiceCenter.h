#ifndef HW1_SOLID_MAINSERVICECENTER_H
#define HW1_SOLID_MAINSERVICECENTER_H

#include "../Interfaces/IServiceCenter.h"
#include <memory>
#include <random>

class MainServiceCenter : public IServiceCenter {
public:
    bool check(const std::shared_ptr<Transport>& transport) const override {
        int random =  std::rand() % 10;

        if (random <= 6) return true;
        return false;
    }
};

#endif
