#include "MainInventoryCenter.h"
#include "../Interfaces/IEnergyConsumer.h"
#include "../Interfaces/IForBeginners.h"
#include "../Domain/Transport.h"
#include "../Domain/Equipment.h"
#include <sstream>
#include <iomanip>
#include <utility>

MainInventoryCenter::MainInventoryCenter(std::shared_ptr<IServiceCenter> sc)
    : serviceCenter(std::move(sc)) {}

std::string MainInventoryCenter::generateInventoryNumber(const std::shared_ptr<IInventory>& item) {
    std::stringstream ss;
    ss << item->getPrefix() << std::setw(8) << std::setfill('0') << nextInventoryId++;
    return ss.str();
}

bool MainInventoryCenter::addTransport(const std::shared_ptr<Transport>& transport) {
    int good = serviceCenter->check(transport);
    if (good) {
        transport->setInventoryNumber(generateInventoryNumber(transport));
        items.push_back(transport);
    }
    return good;
}

void MainInventoryCenter::addEquipment(const std::shared_ptr<Equipment>& equipment) {
    equipment->setInventoryNumber(generateInventoryNumber(equipment));
    items.push_back(equipment);
}

int MainInventoryCenter::getEquipmentCount() const {
    int total = 0;
    for (const auto& item : items) {
        if (auto equipment = std::dynamic_pointer_cast<Equipment>(item)) {
            ++total;
        }
    }
    return total;
}

int MainInventoryCenter::getTransportCount() const {
    int total = 0;
    for (const auto& item : items) {
        if (auto equipment = std::dynamic_pointer_cast<Transport>(item)) {
            ++total;
        }
    }
    return total;
}


double MainInventoryCenter::getTotalEnergy() const {
    double total = 0.0;
    for (const auto& item : items) {
        if (auto consumer = std::dynamic_pointer_cast<IEnergyConsumer>(item)) {
            total += consumer->getDailyEnergyConsumption();
        }
    }
    return total;
}

std::vector<std::shared_ptr<IInventory>> MainInventoryCenter::getForBeginners() const {
    std::vector<std::shared_ptr<IInventory>> result;
    for (const auto& item : items) {
        if (auto beginnerItem = std::dynamic_pointer_cast<IForBeginners>(item)) {
            if (beginnerItem->getSimplicityLevel() >= 6) {
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<std::shared_ptr<IInventory>> MainInventoryCenter::getAllInventory() const {
    return items;
}
