#ifndef HW1_SOLID_MAININVENTORYCENTER_H
#define HW1_SOLID_MAININVENTORYCENTER_H

#include "../Interfaces/IInventoryCenter.h"
#include "../Interfaces/IServiceCenter.h"
#include "../Interfaces/IInventory.h"
#include "../Domain/Transport.h"
#include "../Domain/Equipment.h"
#include <vector>
#include <memory>
#include <string>

class MainInventoryCenter : public IInventoryCenter {
private:
    std::shared_ptr<IServiceCenter> serviceCenter;
    std::vector<std::shared_ptr<IInventory>> items;
    int nextInventoryId = 1;

    std::string generateInventoryNumber(const std::shared_ptr<IInventory>& item);

public:
    explicit MainInventoryCenter(std::shared_ptr<IServiceCenter> sc);

    bool addTransport(const std::shared_ptr<Transport>& transport) override;
    void addEquipment(const std::shared_ptr<Equipment>& equipment) override;

    int getEquipmentCount() const override;
    int getTransportCount() const override;

    double getTotalEnergy() const override;
    std::vector<std::shared_ptr<IInventory>> getForBeginners() const override;
    std::vector<std::shared_ptr<IInventory>> getAllInventory() const override;
};

#endif
