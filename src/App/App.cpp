#include "App.h"

#include "../Domain/Equipments/CommonHelmet.h"
#include "../Domain/Equipments/SmartHelmet.h"
#include "../Domain/Equipments/ChargingStation.h"

#include "../Domain/Transports/Bike.h"
#include "../Domain/Transports/EBike.h"
#include "../Domain/Transports/Scooter.h"

#include <string>
#include <utility>

App::App(std::shared_ptr<IInventoryCenter> ic, std::shared_ptr<IView> cv)
    : inventoryCenter(std::move(ic)), view(std::move(cv)) {}

void App::addTransport() {
    view->print("\n--- Добавление транспорта ---");
    view->print("1. Электросамокат");
    view->print("2. Велосипед");
    view->print("3. Электровелосипед");
    view->print("0. Назад в главное меню");

    int choice = view->readInt();
    std::shared_ptr<Transport> transport;

    switch (choice) {
        case 1: transport = std::make_shared<Scooter>(); break;
        case 2: transport = std::make_shared<Bike>(); break;
        case 3: transport = std::make_shared<EBike>(); break;
        case 0: return;
        default:
            view->print("Неизвестный тип транспорта.");
            return;
    }

    if (inventoryCenter->addTransport(transport)) {
        view->print("Транспорт успешно добавлен! Инвентарный номер: " + transport->getInventoryNumber());
    } else {
        view->print("Транспорт отклонен сервисным центром.");
    }
}

void App::addThing() {
    view->print("\n--- Добавление инвентаря ---");
    view->print("1. Обычный шлем");
    view->print("2. Умный шлем");
    view->print("3. Зарядная станция");
    view->print("0. Назад в главное меню");

    int choice = view->readInt();
    std::shared_ptr<Equipment> thing;

    switch (choice) {
        case 1: thing = std::make_shared<CommonHelmet>(); break;
        case 2: thing = std::make_shared<SmartHelmet>(); break;
        case 3: thing = std::make_shared<ChargingStation>(); break;
        case 0: return;
        default:
            view->print("Неизвестный тип инвентаря.");
            return;
    }
    inventoryCenter->addEquipment(thing);
    view->print("Инвентарь успешно добавлен! Инвентарный номер: " + thing->getInventoryNumber());
}

void App::showInventory() {
    auto items = inventoryCenter->getAllInventory();
    if (items.empty()) {
        view->print("Парк пуст.");
        return;
    }
    view->print("--- Инвентарь парка ВышКат ---");
    for (const auto& item : items) {
        view->print(item->getName() + " [" + item->getInventoryNumber() + "]");
    }
}

void App::showTotalEnergy() {
    double total = inventoryCenter->getTotalEnergy();
    view->print("Суммарное суточное потребление парка: " + std::to_string(total) + " кВт*ч");
}

void App::showCount() {
    view->print("\n--- Число единиц ---");
    view->print("1. Число техники");
    view->print("2. Число инвентаря");
    view->print("0. Назад в главное меню");

    int choice = view->readInt();
    int count;

    switch (choice) {
        case 1: view->print("Всего " + std::to_string(inventoryCenter->getTransportCount()) + " единиц транспорта."); break;
        case 2: view->print("Всего " + std::to_string(inventoryCenter->getEquipmentCount()) + " единиц инвентаря."); break;
        case 0: return;
        default:
            view->print("Неизвестный объект.");
            return;
    }
}

void App::showForBegginers() {
    auto items = inventoryCenter->getForBeginners();
    if (items.empty()) {
        view->print("Техника не найдена.");
        return;
    }
    view->print("--- Техника для новичков ---");
    for (const auto& item : items) {
        view->print(item->getName() + " [" + item->getInventoryNumber() + "]");
    }
}

void App::run() {
    bool isRunning = true;
    while (isRunning) {
        view->print("\nМеню ВышКат:");
        view->print("1. Добавить транспорт");
        view->print("2. Добавить инвентарь");
        view->print("3. Показать весь инвентарь");
        view->print("4. Суммарное энергопотребление");
        view->print("5. Проверить количество");
        view->print("6. Показать всю технику, подходящую для новичков");
        view->print("0. Выход");

        int choice = view->readInt();

            switch (choice) {
                case 1: addTransport(); break;
                case 2: addThing(); break;
                case 3: showInventory(); break;
                case 4: showTotalEnergy(); break;
                case 5: showCount(); break;
                case 6: showForBegginers(); break;
                case 0: isRunning = false; break;
                default: view->print("Неизвестная команда.");
            }
        }
    }