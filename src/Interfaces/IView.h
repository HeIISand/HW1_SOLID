#ifndef HW1_SOLID_ICONSOLEVIEW_H
#define HW1_SOLID_ICONSOLEVIEW_H

#include <string>

class IView {
public:
    virtual ~IView() = default;
    virtual void print(const std::string& message) const = 0;
    virtual int readInt() const = 0;
};

#endif
