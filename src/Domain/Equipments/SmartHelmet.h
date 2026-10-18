#ifndef HW1_SOLID_SMARTHELMET_H
#define HW1_SOLID_SMARTHELMET_H

#include "Helmet.h"
#include "../../Interfaces/IEnergyConsumer.h"
#include <string>

class SmartHelmet : public Helmet, public virtual IEnergyConsumer {
private:
    double energyConsumption = 0.1;
public:
    SmartHelmet() : Helmet("Умный шлем", 5) {}
    std::string getPrefix() const override { return "SH"; }
    double getDailyEnergyConsumption() const override { return energyConsumption; }
};

#endif
