#ifndef HW1_SOLID_EBIKE_H
#define HW1_SOLID_EBIKE_H

#include "../Transport.h"
#include "../../Interfaces/IEnergyConsumer.h"
#include <string>

class EBike : public Transport, public virtual IEnergyConsumer {
private:
    double energyConsumption = 1.0;
public:
    EBike() : Transport("Электровелосипед", 7) {}
    std::string getPrefix() const override { return "EB"; }
    double getDailyEnergyConsumption() const override { return energyConsumption; }
};

#endif
