cmake_minimum_required(VERSION 3.24.2)
project(ElectricScooterRentalApp)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(AppUI)
include_directories(AppController)
include_directories(Domain)
include_directories(AppRepository)

add_executable(ElectricScooterRentalApp
        AppUI/ClientUI.cpp
        AppUI/ClientUI.h
        AppUI/MainUI.cpp
        AppUI/MainUI.h
        AppUI/ManagerUI.cpp
        AppUI/ManagerUI.h
        AppController/Controller.cpp
        AppController/Controller.h
        Domain/Scooter.cpp
        Domain/Scooter.h
        Utils/AuxiliaryFunctions.cpp
        Utils/AuxiliaryFunctions.h
        App.cpp AppRepository/CrudRepository.cpp AppRepository/RepositoryTest.cpp AppController/ControllerTest.cpp AppRepository/CsvFileRepository.h AppRepository/CsvFileRepository.cpp AppRepository/InMemoryRepository.h AppRepository/InMemoryRepository.cpp)
