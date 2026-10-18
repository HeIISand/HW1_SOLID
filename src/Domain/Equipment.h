#ifndef HW1_SOLID_EQUIPMENT_H
#define HW1_SOLID_EQUIPMENT_H

#include <string>
#include <utility>
#include "../Interfaces/IInventory.h"

class Equipment : public virtual IInventory {
protected:
    std::string inventoryNumber = "Не задан";
    std::string name;

public:
    Equipment(std::string name) : name(std::move(name)) {}

    std::string getInventoryNumber() const override { return inventoryNumber; }
    void setInventoryNumber(const std::string& number) override { inventoryNumber = number; }
    std::string getName() const override { return name; }
};

#endif
