#ifndef HW1_SOLID_SCOOTER_H
#define HW1_SOLID_SCOOTER_H

#include "../Transport.h"
#include "../../Interfaces/IEnergyConsumer.h"
#include <string>

class Scooter : public Transport, public virtual IEnergyConsumer {
private:
    double energyConsumption = 0.6;
public:
    Scooter() : Transport("Электросамокат", 5) {}
    std::string getPrefix() const override { return "SC"; }
    double getDailyEnergyConsumption() const override { return energyConsumption; }
};

#endif
