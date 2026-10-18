#ifndef HW1_SOLID_COMMONHELMET_H
#define HW1_SOLID_COMMONHELMET_H

#include "Helmet.h"
#include <string>

class CommonHelmet : public Helmet {
public:
    CommonHelmet() : Helmet("Обычный шлем", 9) {}
    std::string getPrefix() const override { return "CH"; }
};

#endif
