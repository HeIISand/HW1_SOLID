#ifndef HW1_SOLID_BIKE_H
#define HW1_SOLID_BIKE_H

#include "../Transport.h"
#include <string>

class Bike : public Transport {
public:
    Bike() : Transport("Велосипед", 8) {}
    std::string getPrefix() const override { return "B"; }
};

#endif
