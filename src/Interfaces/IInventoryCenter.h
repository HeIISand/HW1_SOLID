#ifndef HW1_SOLID_IINVENTORYCENTER_H
#define HW1_SOLID_IINVENTORYCENTER_H

#include <vector>
#include <memory>

class IInventory;
class Transport;
class Equipment;

class IInventoryCenter {
public:
    virtual ~IInventoryCenter() = default;
    virtual bool addTransport(const std::shared_ptr<Transport>& transport) = 0;
    virtual void addEquipment(const std::shared_ptr<Equipment>& equipment) = 0;
    virtual double getTotalEnergy() const = 0;
    virtual int getEquipmentCount() const = 0;
    virtual int getTransportCount() const = 0;
    virtual std::vector<std::shared_ptr<IInventory>> getForBeginners() const = 0;
    virtual std::vector<std::shared_ptr<IInventory>> getAllInventory() const = 0;
};

#endif
