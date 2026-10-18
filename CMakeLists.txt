cmake_minimum_required(VERSION 4.1)
project(HW1_SOLID)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(HW1_SOLID src/App/main.cpp
        src/Interfaces/IInventory.h
        src/Interfaces/IEnergyConsumer.h
        src/Interfaces/IForBeginners.h
        src/Interfaces/IServiceCenter.h
        src/Interfaces/IInventoryCenter.h
        src/Interfaces/IView.h
        src/Domain/Transport.h
        src/Domain/Equipment.h
        src/Logic/MainServiceCenter.h
        src/Logic/MainInventoryCenter.cpp
        src/Logic/MainInventoryCenter.h
        src/App/ConsoleView.h
        src/App/App.cpp
        src/App/App.h
        src/Domain/Equipments/ChargingStation.h
        src/Domain/Transports/Bike.h
        src/Domain/Transports/EBike.h
        src/Domain/Transports/scooter.h
        src/Domain/Equipments/Helmet.h
        src/Domain/Equipments/CommonHelmet.h
        src/Domain/Equipments/SmartHelmet.h
        include/di.h)

add_executable(HW1_SOLID_Tests
        src/Logic/MainInventoryCenter.cpp
        src/Tests/tests.cpp
        src/App/App.cpp
)

target_link_libraries(HW1_SOLID_Tests PRIVATE GTest::gtest_main)