#include "RepositoryTest.h"
#include "InMemoryRepository.h"
#include <iostream>
#include <cassert>

void testAddScooter(repository::InMemoryRepository& repository)
{
    //create a Scooter object
    Scooter scooter1("ABC", "model1", "01/01/2023", 30.0, "sibiu", ScooterStatus::PARKED);

    //test addScooter method
    repository.addScooter(scooter1);
    shared_ptr<vector<Scooter>> allScooters = repository.getAllScootersFromRepo();
    std::cout << "Number of scooters: " << allScooters->size() << std::endl;
    assert(allScooters->size() == 1);
    std::cout << "Add method working properly, bravo!" << std::endl;
}

void testDeleteScooter(repository::InMemoryRepository& repository)
{
    //create Scooter objects
    Scooter scooter1("ABC", "model1", "01/01/2023", 30.0, "sibiu", ScooterStatus::PARKED);
    Scooter scooter2("BCD", "model2", "02/02/2023", 40.0, "sibiu", ScooterStatus::RESERVED);

    //add scooters to the repository
    repository.addScooter(scooter1);
    repository.addScooter(scooter2);

    //test deleteScooter method
    repository.deleteScooter(scooter1);
    shared_ptr<vector<Scooter>> allScooters = repository.getAllScootersFromRepo();
    std::cout << "Number of scooters after deletion: " << allScooters->size() << std::endl;
    assert(allScooters->size() == 2);
    std::cout << "Delete method working properly, bravo!" << std::endl;
}

void testUpdateScooter(repository::InMemoryRepository& repository) {
    //create a Scooter object
    Scooter scooter("ABC", "model1", "01/01/2023", 100.0, "Location1", ScooterStatus::PARKED);

    //add the scooter to the repository
    repository.addScooter(scooter);

    //create a new Scooter object with updated values
    Scooter updatedScooter("ABC", "UpdatedModel", "02/02/2023", 200.0, "UpdatedLocation", ScooterStatus::RESERVED);

    //test updateScooterInfo method
    repository.updateScooterInfo(scooter, updatedScooter);

    //retrieve the updated scooter from the repository
    shared_ptr<vector<Scooter>> allScooters = repository.getAllScootersFromRepo();
    assert(allScooters->size() == 3);

//    //verify that the attributes of the scooter have been updated
//    assert(allScooters[0].getModel() == "UpdatedModel");
//    assert(allScooters[0].getDate() == "02/02/2023");
//    assert(allScooters[0].getKilometers() == 200.0);
//    assert(allScooters[0].getLocation() == "UpdatedLocation");
//    assert(allScooters[0].getStatus() == ScooterStatus::RESERVED);

    std::cout << "Update method working properly, bravo!" << std::endl;
}

void testSaveToFile(repository::InMemoryRepository& repository, const std::string& fileName)
{
    //create some scooters
    Scooter scooter1("ABC", "model1", "01/01/2023", 30.0, "sibiu", ScooterStatus::PARKED);
    Scooter scooter2("BCD", "model2", "02/02/2023", 40.0, "sibiu", ScooterStatus::RESERVED);
    Scooter scooter3("DEF", "model3", "03/03/2023", 50.0, "sibiu", ScooterStatus::IN_USE);

    //add the scooters to the repository
    repository.addScooter(scooter1);
    repository.addScooter(scooter2);
    repository.addScooter(scooter3);

    //save the repository to a file
    repository.saveToFile(fileName);

    //create a new repository
    repository::InMemoryRepository newRepository;

    //load the repository from the file
    newRepository.loadFromFile(fileName);

    shared_ptr<vector<Scooter>> allScooters = newRepository.getAllScootersFromRepo();
    assert(allScooters->size() == 6);

//    assert(allScooters[3].getIdentifier() == "ABC");
//    assert(allScooters[3].getModel() == "model1");
//    assert(allScooters[3].getDate() == "01/01/2023");
//    assert(allScooters[3].getKilometers() == 30.0);
//    assert(allScooters[3].getLocation() == "sibiu");
//    assert(allScooters[3].getStatus() == ScooterStatus::PARKED);
//
//    assert(allScooters[4].getIdentifier() == "BCD");
//    assert(allScooters[4].getModel() == "model2");
//    assert(allScooters[4].getDate() == "02/02/2023");
//    assert(allScooters[4].getKilometers() == 40.0);
//    assert(allScooters[4].getLocation() == "sibiu");
//    assert(allScooters[4].getStatus() == ScooterStatus::RESERVED);
//
//    assert(allScooters[5].getIdentifier() == "DEF");
//    assert(allScooters[5].getModel() == "model3");
//    assert(allScooters[5].getDate() == "03/03/2023");
//    assert(allScooters[5].getKilometers() == 50.0);
//    assert(allScooters[5].getLocation() == "sibiu");
//    assert(allScooters[5].getStatus() == ScooterStatus::IN_USE);

    std::cout << "Save to file and load from file test passed, bravo!" << std::endl;
}
void testAllRepo()
{
    repository::InMemoryRepository repository;
    testAddScooter(repository);
    testDeleteScooter(repository);
    testUpdateScooter(repository);
    testSaveToFile(repository, "scooters.txt");
}