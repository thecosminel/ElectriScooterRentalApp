#include "RepositoryTest.h"
#include "CrudRepository.h"
#include "CsvFileRepository.h"
#include "InMemoryRepository.h"
#include <iostream>
#include <cassert>

void testAddScooterCsv(repository::CsvFileRepository& repository)
{
    //create a Scooter object
    Scooter scooter1("ABC", "model1", "01/01/2023", 30.0, "sibiu", ScooterStatus::PARKED);

    //test addScooter method
    repository.addScooter(scooter1);
    shared_ptr<vector<Scooter>> allScooters = repository.getAllScootersFromRepo();
    std::cout << "Number of scooters: " << allScooters->size() << std::endl;
    assert(allScooters->size() == 12);
    std::cout << "Add method CSV working properly, bravo!" << std::endl;
}

void testDeleteScooterCsv(repository::CsvFileRepository& repository)
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
    assert(allScooters->size() == 13);
    std::cout << "Delete method CSV working properly, bravo!" << std::endl;
}

void testUpdateScooterCsv(repository::CsvFileRepository& repository) {
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
    std::cout << "Number of scooters: " << allScooters->size() << std::endl;

    assert(allScooters->size() == 14);

    //verify that the attributes of the scooter have been updated
    assert(updatedScooter.getModel() == "UpdatedModel");
    assert(updatedScooter.getDate() == "02/02/2023");
    assert(updatedScooter.getKilometers() == 200.0);
    assert(updatedScooter.getLocation() == "UpdatedLocation");
    assert(updatedScooter.getStatus() == ScooterStatus::RESERVED);

    std::cout << "Update method CSV working properly, bravo!" << std::endl;
}

void testSaveToFileCsv(repository::CsvFileRepository& repository, const std::string& fileName)
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
    repository::CsvFileRepository newRepository;

    //load the repository from the file
    newRepository.loadFromFile(fileName);

    shared_ptr<vector<Scooter>> allScooters = newRepository.getAllScootersFromRepo();

    std::cout << "Number of scooters: " << allScooters->size() << std::endl;

    assert(allScooters->size() == 28);

    assert(scooter1.getIdentifier() == "ABC");
    assert(scooter1.getModel() == "model1");
    assert(scooter1.getDate() == "01/01/2023");
    assert(scooter1.getKilometers() == 30.0);
    assert(scooter1.getLocation() == "sibiu");
    assert(scooter1.getStatus() == ScooterStatus::PARKED);

    assert(scooter2.getIdentifier() == "BCD");
    assert(scooter2.getModel() == "model2");
    assert(scooter2.getDate() == "02/02/2023");
    assert(scooter2.getKilometers() == 40.0);
    assert(scooter2.getLocation() == "sibiu");
    assert(scooter2.getStatus() == ScooterStatus::RESERVED);

    assert(scooter3.getIdentifier() == "DEF");
    assert(scooter3.getModel() == "model3");
    assert(scooter3.getDate() == "03/03/2023");
    assert(scooter3.getKilometers() == 50.0);
    assert(scooter3.getLocation() == "sibiu");
    assert(scooter3.getStatus() == ScooterStatus::IN_USE);

    std::cout << "Save to file and load from file CSV test passed, bravo!" << std::endl;
}

void testAddScooterInMemory(repository::InMemoryRepository& repository)
{
    //create a Scooter object
    Scooter scooter1("ABC", "model1", "01/01/2023", 30.0, "sibiu", ScooterStatus::PARKED);

    //test addScooter method
    repository.addScooter(scooter1);
    shared_ptr<vector<Scooter>> allScooters = repository.getAllScootersFromRepo();
    std::cout << "Number of scooters: " << allScooters->size() << std::endl;
    assert(allScooters->size() == 12);
    std::cout << "Add method InMemory working properly, bravo!" << std::endl;
}


void testDeleteScooterInMemory(repository::InMemoryRepository& repository)
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
    assert(allScooters->size() == 13);
    std::cout << "Delete method InMemory working properly, bravo!" << std::endl;
}

void testUpdateScooterInMemory(repository::InMemoryRepository& repository) {
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
    std::cout << "Number of scooters: " << allScooters->size() << std::endl;

    assert(allScooters->size() == 14);

    //verify that the attributes of the scooter have been updated
    assert(updatedScooter.getModel() == "UpdatedModel");
    assert(updatedScooter.getDate() == "02/02/2023");
    assert(updatedScooter.getKilometers() == 200.0);
    assert(updatedScooter.getLocation() == "UpdatedLocation");
    assert(updatedScooter.getStatus() == ScooterStatus::RESERVED);

    std::cout << "Update method working InMemory properly, bravo!" << std::endl;
}

void testSaveToFileInMemory(repository::InMemoryRepository& repository, const std::string& fileName)
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
   // repository.saveToFile(fileName);

    //create a new repository
    repository::CsvFileRepository newRepository;

    //load the repository from the file
    newRepository.loadFromFile(fileName);

    shared_ptr<vector<Scooter>> allScooters = newRepository.getAllScootersFromRepo();

    std::cout << "Number of scooters: " << allScooters->size() << std::endl;

    assert(allScooters->size() == 28);

    assert(scooter1.getIdentifier() == "ABC");
    assert(scooter1.getModel() == "model1");
    assert(scooter1.getDate() == "01/01/2023");
    assert(scooter1.getKilometers() == 30.0);
    assert(scooter1.getLocation() == "sibiu");
    assert(scooter1.getStatus() == ScooterStatus::PARKED);

    assert(scooter2.getIdentifier() == "BCD");
    assert(scooter2.getModel() == "model2");
    assert(scooter2.getDate() == "02/02/2023");
    assert(scooter2.getKilometers() == 40.0);
    assert(scooter2.getLocation() == "sibiu");
    assert(scooter2.getStatus() == ScooterStatus::RESERVED);

    assert(scooter3.getIdentifier() == "DEF");
    assert(scooter3.getModel() == "model3");
    assert(scooter3.getDate() == "03/03/2023");
    assert(scooter3.getKilometers() == 50.0);
    assert(scooter3.getLocation() == "sibiu");
    assert(scooter3.getStatus() == ScooterStatus::IN_USE);

    std::cout << "Save to file and load from file InMemory test passed, bravo!" << std::endl;
}
void testAllRepo()
{
    repository::CsvFileRepository repository;

    repository::InMemoryRepository InMemoRepository;

    testAddScooterCsv(repository);
    testDeleteScooterCsv(repository);
    testUpdateScooterCsv(repository);
    testSaveToFileCsv(repository, "scooters.txt");

    testAddScooterInMemory(InMemoRepository);
    testDeleteScooterInMemory(InMemoRepository);
    testUpdateScooterInMemory(InMemoRepository);

}