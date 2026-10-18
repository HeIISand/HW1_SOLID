#ifndef HW1_SOLID_TRANSPORT_H
#define HW1_SOLID_TRANSPORT_H

#include <string>
#include <utility>
#include "../Interfaces/IInventory.h"
#include "../Interfaces/IForBeginners.h"

class Transport : public virtual IInventory, public virtual IForBeginners {
protected:
    std::string inventoryNumber = "Не задан";
    std::string name;
    int simplicityLevel;

public:
    Transport(std::string name, int simplicity)
        : name(std::move(name)), simplicityLevel(simplicity) {}

    std::string getInventoryNumber() const override { return inventoryNumber; }
    void setInventoryNumber(const std::string& number) override { inventoryNumber = number; }
    std::string getName() const override { return name; }
    int getSimplicityLevel() const override { return simplicityLevel; }
};

#endif
