#ifndef HW1_SOLID_IENERGYCONSUMER_H
#define HW1_SOLID_IENERGYCONSUMER_H

class IEnergyConsumer {
public:
    virtual ~IEnergyConsumer() = default;
    virtual double getDailyEnergyConsumption() const = 0;
};

#endif
