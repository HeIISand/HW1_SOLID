#ifndef HW1_SOLID_CHARGINGSTATION_H
#define HW1_SOLID_CHARGINGSTATION_H

#include "../Equipment.h"
#include "../../Interfaces/IEnergyConsumer.h"
#include <string>

class ChargingStation : public Equipment, public virtual IEnergyConsumer {
private:
    double energyConsumption = 5.0;
public:
    ChargingStation() : Equipment("Зарядная станция") {}
    std::string getPrefix() const override { return "CHS"; }
    double getDailyEnergyConsumption() const override { return energyConsumption; }
};

#endif
