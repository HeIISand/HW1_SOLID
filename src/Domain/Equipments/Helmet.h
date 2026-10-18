#ifndef HW1_SOLID_HELMET_H
#define HW1_SOLID_HELMET_H

#include "../Equipment.h"
#include "../../Interfaces/IForBeginners.h"
#include <string>
#include <utility>

class Helmet : public Equipment, public virtual IForBeginners {
protected:
    int simplicityLevel;
public:
    Helmet(std::string name, int simplicity)
        : Equipment(std::move(name)), simplicityLevel(simplicity) {}

    int getSimplicityLevel() const override { return simplicityLevel; }
};

#endif
