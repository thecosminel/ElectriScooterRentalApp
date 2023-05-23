//
// Created by Robert on 14/05/2023.
//

#include <iostream>
#include <cassert>
#include "ControllerTest.h"
#include "Controller.h"
#include "InMemoryRepository.h"
#include "CsvFileRepository.h"
using std::cout;
using namespace controller;
using namespace repository;

void testReserveScooter() {
    auto repository = std::make_shared<InMemoryRepository>();
    repository->addScooter(Scooter("ABC", "Model1", "10.12.2022", 100.0, "New York", PARKED));
    repository->addScooter(Scooter("DEF", "Model2", "05.06.2021", 200.0, "Los Angeles", PARKED));
    repository->addScooter(Scooter("GHI", "Model3", "20.08.2022", 300.0, "San Francisco", PARKED));

    Controller controller(repository);
    auto scooters = repository->getAllScootersFromRepo();
    assert(controller.reserveScooter("ABC", ""));
    assert(controller.reserveScooter("DEF", ""));
    assert(!controller.reserveScooter("abc", ""));
    cout << "Reserve scooter tests done...\n";
}

void testAddScooterToRepo() {
    auto repository = std::make_shared<InMemoryRepository>();
    Controller controller(repository);

    string model = "gush";
    string manufacturingDate = "10.12.2022";
    double km = 1234.5;
    string location = "Manhattanstur";
    ScooterStatus scooterStatus = PARKED;

    controller.addScooterToRepo(model, manufacturingDate, km, location, scooterStatus);

    model = "shush";
    manufacturingDate = "10.11.2022";
    km = 1234.5;
    location = "Manhattanstur";
    scooterStatus = PARKED;

    controller.addScooterToRepo(model, manufacturingDate, km, location, scooterStatus);

    model = "slush";
    manufacturingDate = "10.09.2022";
    km = 1234.5;
    location = "Manhattanstur";
    scooterStatus = PARKED;

    controller.addScooterToRepo(model, manufacturingDate, km, location, scooterStatus);

    auto allScooters = repository->getAllScootersFromRepo();
    vector<Scooter> testScooters;
    for(const Scooter& currentScooter : *allScooters) {
        testScooters.push_back(currentScooter);
    }

    cout << "Add scooter to repo tests done...\n";
}

void testDeleteScooterFromRepo() {
    auto repository = std::make_shared<InMemoryRepository>();
    repository->addScooter(Scooter("ABC", "Model1", "10.12.2022", 100.0, "New York", PARKED));
    repository->addScooter(Scooter("DEF", "Model2", "05.06.2021", 200.0, "Los Angeles", PARKED));
    repository->addScooter(Scooter("GHI", "Model3", "20.08.2022", 300.0, "San Francisco", PARKED));

    Controller controller(repository);
    auto scooters = repository->getAllScootersFromRepo();
    assert(controller.deleteScooterFromRepo("ABC"));
    assert(!controller.deleteScooterFromRepo("ABC"));
    assert(controller.deleteScooterFromRepo("DEF"));
    assert(!controller.deleteScooterFromRepo("abc"));
    cout << "Delete scooter from repo tests done...\n";
}

void testModifyScooterFromRepo() {
    auto repository = std::make_shared<InMemoryRepository>();
    repository->addScooter(Scooter("ABC", "Model1", "10.12.2022", 100.0, "New York", PARKED));
    repository->addScooter(Scooter("DEF", "Model2", "05.06.2021", 200.0, "Los Angeles", PARKED));
    repository->addScooter(Scooter("GHI", "Model3", "20.08.2022", 300.0, "San Francisco", PARKED));

    Controller controller(repository);
    assert(controller.modifyScooterFromRepo("ABC", 150.0, "", UNKNOWN));
    assert(controller.modifyScooterFromRepo("DEF", 150.0, "LA", RESERVED));

    cout << "Modify scooter from repo tests done...\n";
}

void testFilterScootersByDate() {
    auto repository = std::make_shared<InMemoryRepository>();
    repository->addScooter(Scooter("ABC", "Model1", "10.12.2022", 100.0, "New York", PARKED));
    repository->addScooter(Scooter("DEF", "Model2", "05.06.2021", 200.0, "Los Angeles", PARKED));
    repository->addScooter(Scooter("GHI", "Model3", "20.08.2022", 300.0, "San Francisco", PARKED));

    Controller controller(repository);

    auto filteredScooters = controller.filterScootersByAgeBetweenTwoDates("21.08.2022", "12.12.2022");
    assert(filteredScooters->size() == 1);

    filteredScooters = controller.filterScootersByAgeBetweenTwoDates("15.08.2022", "10.12.2022");
    assert(filteredScooters->size() == 2);

    cout << "Filter scooters by date tests done...\n";
}

void testSortScootersByAge() {
    auto repository = std::make_shared<InMemoryRepository>();
    repository->addScooter(Scooter("ABC", "Model1", "10.12.2022", 100.0, "New York", PARKED));
    repository->addScooter(Scooter("DEF", "Model2", "05.06.2021", 200.0, "Los Angeles", PARKED));
    repository->addScooter(Scooter("GHI", "Model3", "20.08.2022", 300.0, "San Francisco", PARKED));

    Controller controller(repository);

    auto filteredScooters = controller.sortScootersByDate();
    vector<Scooter> testScooters;
    for(const Scooter& currentScooter : *filteredScooters) {
        testScooters.push_back(currentScooter);
    }


    cout << "Sort scooters by age tests done...\n";
}

void testSortScootersByID() {
    auto repository = std::make_shared<InMemoryRepository>();
    repository->addScooter(Scooter("ABC", "Model1", "10.12.2022", 100.0, "New York", PARKED));
    repository->addScooter(Scooter("GHI", "Model3", "20.08.2022", 300.0, "San Francisco", PARKED));
    repository->addScooter(Scooter("DEF", "Model2", "05.06.2021", 200.0, "Los Angeles", PARKED));

    Controller controller(repository);

    auto filteredScooters = controller.sortScootersByID();
    vector<Scooter> testScooters;
    for(const Scooter& currentScooter : *filteredScooters) {
        testScooters.push_back(currentScooter);
    }

    assert(testScooters[0].getIdentifier() == "ABC");
    assert(testScooters[1].getIdentifier() == "DEF");
    assert(testScooters[2].getIdentifier() == "GHI");

    cout << "Sort scooters by ID tests done...\n";
}

void testAllController() {
    testReserveScooter();
    testAddScooterToRepo();
    testDeleteScooterFromRepo();
    testModifyScooterFromRepo();
    testFilterScootersByDate();
    testSortScootersByAge();
    testSortScootersByID();
    cout << "\nAll controller tests passed!\n";
}
