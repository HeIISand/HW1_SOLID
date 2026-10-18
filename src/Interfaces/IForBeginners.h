#ifndef HW1_SOLID_IFORBEGINNERS_H
#define HW1_SOLID_IFORBEGINNERS_H

class IForBeginners {
public:
    virtual ~IForBeginners() = default;
    virtual int getSimplicityLevel() const = 0;
};

#endif
