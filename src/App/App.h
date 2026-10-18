#ifndef HW1_SOLID_CONSOLEAPP_H
#define HW1_SOLID_CONSOLEAPP_H

#include "../Interfaces/IInventoryCenter.h"
#include "../Interfaces/IView.h"
#include <memory>

class App {
private:
    std::shared_ptr<IInventoryCenter> inventoryCenter;
    std::shared_ptr<IView> view;

    void addTransport();
    void addThing();
    void showInventory();
    void showTotalEnergy();

    void showCount();

    void showForBegginers();

public:
    App(std::shared_ptr<IInventoryCenter> ic, std::shared_ptr<IView> cv);
    void run();
};

#endif
