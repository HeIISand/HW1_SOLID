#ifndef HW1_SOLID_ISERVICECENTER_H
#define HW1_SOLID_ISERVICECENTER_H

#include <memory>

class Transport;

class IServiceCenter {
public:
    virtual ~IServiceCenter() = default;
    virtual bool check(const std::shared_ptr<Transport>& transport) const = 0;
};

#endif
