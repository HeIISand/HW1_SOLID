#ifndef HW1_SOLID_IINVENTORY_H
#define HW1_SOLID_IINVENTORY_H

#include <string>

class IInventory {
public:
    virtual ~IInventory() = default;
    virtual std::string getInventoryNumber() const = 0;
    virtual void setInventoryNumber(const std::string& number) = 0;
    virtual std::string getPrefix() const = 0;
    virtual std::string getName() const = 0;
};

#endif
