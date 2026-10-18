#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>
#include "../../include/di.h"

#include "../Interfaces/IInventory.h"
#include "../Interfaces/IEnergyConsumer.h"
#include "../Interfaces/IForBeginners.h"
#include "../Interfaces/IServiceCenter.h"
#include "../Interfaces/IInventoryCenter.h"
#include "../Interfaces/IView.h"

#include "../Domain/Transport.h"
#include "../Domain/Equipment.h"
#include "../Domain/Transports/Scooter.h"
#include "../Domain/Transports/Bike.h"
#include "../Domain/Transports/EBike.h"
#include "../Domain/Equipments/Helmet.h"
#include "../Domain/Equipments/CommonHelmet.h"
#include "../Domain/Equipments/SmartHelmet.h"
#include "../Domain/Equipments/ChargingStation.h"

#include "../Logic/MainServiceCenter.h"
#include "../Logic/MainInventoryCenter.h"
#include "../App/App.h"

namespace di = boost::ext::di;

class FakeServiceCenter : public IServiceCenter {
public:
    bool shouldPass = true;
    mutable int checkCallCount = 0;

    bool check(const std::shared_ptr<Transport>& transport) const override {
        checkCallCount++;
        return shouldPass;
    }
};

class FakeView : public IView {
public:
    mutable std::vector<int> inputs;
    mutable size_t inputIndex = 0;
    mutable std::vector<std::string> outputs;

    void print(const std::string& message) const override {
        outputs.push_back(message);
    }

    int readInt() const override {
        if (inputIndex < inputs.size()) {
            return inputs[inputIndex++];
        }
        return 0;
    }
};

class AppTest : public ::testing::Test {
protected:
    std::shared_ptr<FakeServiceCenter> fakeService;
    std::shared_ptr<IInventoryCenter> inventory;

    void SetUp() override {
        fakeService = std::make_shared<FakeServiceCenter>();

        const auto injector = di::make_injector(
            di::bind<IServiceCenter>.to(fakeService),
            di::bind<IInventoryCenter>.to<MainInventoryCenter>().in(di::unique)
        );

        inventory = injector.create<std::shared_ptr<IInventoryCenter>>();
    }

    void addAllEntities() {
        inventory->addTransport(std::make_shared<Scooter>());
        inventory->addTransport(std::make_shared<Bike>());
        inventory->addTransport(std::make_shared<EBike>());

        inventory->addEquipment(std::make_shared<CommonHelmet>());
        inventory->addEquipment(std::make_shared<SmartHelmet>());
        inventory->addEquipment(std::make_shared<ChargingStation>());
    }
};

TEST_F(AppTest, EmptyParkInitialState) {
    EXPECT_EQ(inventory->getAllInventory().size(), 0);
    EXPECT_EQ(inventory->getTransportCount(), 0);
    EXPECT_EQ(inventory->getEquipmentCount(), 0);
    EXPECT_DOUBLE_EQ(inventory->getTotalEnergy(), 0.0);
    EXPECT_TRUE(inventory->getForBeginners().empty());
}

TEST_F(AppTest, ServicePasses) {
    fakeService->shouldPass = true;
    addAllEntities();

    EXPECT_EQ(fakeService->checkCallCount, 3);
    EXPECT_EQ(inventory->getTransportCount(), 3);
    EXPECT_EQ(inventory->getEquipmentCount(), 3);
    EXPECT_EQ(inventory->getAllInventory().size(), 6);

    for (const auto& item : inventory->getAllInventory()) {
        EXPECT_FALSE(item->getInventoryNumber().empty());
        EXPECT_NE(item->getInventoryNumber(), "Не задан");
    }
}

TEST_F(AppTest, ServiceFails) {
    fakeService->shouldPass = false;

    auto scooter = std::make_shared<Scooter>();
    auto bike = std::make_shared<Bike>();
    auto ebike = std::make_shared<EBike>();
    auto commonHelmet = std::make_shared<CommonHelmet>();
    auto smartHelmet = std::make_shared<SmartHelmet>();
    auto station = std::make_shared<ChargingStation>();

    std::string defaultNum = scooter->getInventoryNumber();

    inventory->addTransport(scooter);
    inventory->addTransport(bike);
    inventory->addTransport(ebike);
    inventory->addEquipment(commonHelmet);
    inventory->addEquipment(smartHelmet);
    inventory->addEquipment(station);

    EXPECT_EQ(fakeService->checkCallCount, 3);
    EXPECT_EQ(inventory->getTransportCount(), 0);
    EXPECT_EQ(inventory->getEquipmentCount(), 3);
    EXPECT_EQ(inventory->getAllInventory().size(), 3);

    EXPECT_EQ(scooter->getInventoryNumber(), defaultNum);
    EXPECT_EQ(bike->getInventoryNumber(), defaultNum);
    EXPECT_EQ(ebike->getInventoryNumber(), defaultNum);

    EXPECT_NE(commonHelmet->getInventoryNumber(), defaultNum);
    EXPECT_NE(smartHelmet->getInventoryNumber(), defaultNum);
    EXPECT_NE(station->getInventoryNumber(), defaultNum);
}

TEST_F(AppTest, InventoryNumberFormatting) {
    fakeService->shouldPass = true;

    auto scooter = std::make_shared<Scooter>();
    auto station = std::make_shared<ChargingStation>();

    inventory->addTransport(scooter);
    inventory->addEquipment(station);

    EXPECT_EQ(scooter->getInventoryNumber(), scooter->getPrefix() + "00000001");
    EXPECT_EQ(station->getInventoryNumber(), station->getPrefix() + "00000002");
}

TEST_F(AppTest, BeginnersCheck) {
    fakeService->shouldPass = true;
    addAllEntities();

    auto beginnersItems = inventory->getForBeginners();
    EXPECT_FALSE(beginnersItems.empty());

    int expectedCount = 0;
    for (const auto& item : inventory->getAllInventory()) {
        if (auto fb = std::dynamic_pointer_cast<IForBeginners>(item)) {
            if (fb->getSimplicityLevel() >= 6) {
                expectedCount++;
            }
        }
    }

    EXPECT_EQ(beginnersItems.size(), expectedCount);

    for (const auto& item : beginnersItems) {
        auto beginnerItem = std::dynamic_pointer_cast<IForBeginners>(item);
        ASSERT_NE(beginnerItem, nullptr);
        EXPECT_GE(beginnerItem->getSimplicityLevel(), 6);
    }
}

TEST_F(AppTest, TotalEnergyCalculation) {
    fakeService->shouldPass = true;

    auto scooter = std::make_shared<Scooter>();
    auto bike = std::make_shared<Bike>();
    auto ebike = std::make_shared<EBike>();
    auto commonHelmet = std::make_shared<CommonHelmet>();
    auto smartHelmet = std::make_shared<SmartHelmet>();
    auto station = std::make_shared<ChargingStation>();

    inventory->addTransport(scooter);
    inventory->addTransport(bike);
    inventory->addTransport(ebike);
    inventory->addEquipment(commonHelmet);
    inventory->addEquipment(smartHelmet);
    inventory->addEquipment(station);

    double expectedEnergy = scooter->getDailyEnergyConsumption() +
                            ebike->getDailyEnergyConsumption() +
                            smartHelmet->getDailyEnergyConsumption() +
                            station->getDailyEnergyConsumption();

    EXPECT_DOUBLE_EQ(inventory->getTotalEnergy(), expectedEnergy);
    EXPECT_GT(inventory->getTotalEnergy(), 0.0);
}

TEST_F(AppTest, DomainEntitiesPropertiesCheck) {
    auto scooter = std::make_shared<Scooter>();
    auto bike = std::make_shared<Bike>();
    auto ebike = std::make_shared<EBike>();
    auto commonHelmet = std::make_shared<CommonHelmet>();
    auto smartHelmet = std::make_shared<SmartHelmet>();
    auto station = std::make_shared<ChargingStation>();

    EXPECT_FALSE(scooter->getName().empty());
    EXPECT_FALSE(bike->getName().empty());
    EXPECT_FALSE(ebike->getName().empty());
    EXPECT_FALSE(commonHelmet->getName().empty());
    EXPECT_FALSE(smartHelmet->getName().empty());
    EXPECT_FALSE(station->getName().empty());

    EXPECT_FALSE(scooter->getPrefix().empty());
    EXPECT_FALSE(bike->getPrefix().empty());
    EXPECT_FALSE(ebike->getPrefix().empty());
    EXPECT_FALSE(commonHelmet->getPrefix().empty());
    EXPECT_FALSE(smartHelmet->getPrefix().empty());
    EXPECT_FALSE(station->getPrefix().empty());
}

TEST_F(AppTest, InputAndOutput) {
    auto fakeService = std::make_shared<FakeServiceCenter>();
    fakeService->shouldPass = true;
    auto fakeView = std::make_shared<FakeView>();

    fakeView->inputs = {1, 1, 2, 1, 3, 4, 5, 1, 6, 0};

    const auto injector = di::make_injector(
        di::bind<IServiceCenter>.to(fakeService),
        di::bind<IInventoryCenter>.to<MainInventoryCenter>().in(di::unique),
        di::bind<IView>.to(fakeView)
    );

    auto app = injector.create<App>();
    app.run();

    EXPECT_FALSE(fakeView->outputs.empty());
    EXPECT_GE(fakeService->checkCallCount, 1);
}