#include "CsvFileRepository.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

void repository::CsvFileRepository::saveToFile(const std::string& fileName)
{
    std::ofstream file(fileName);
    if (file.is_open())
    {
        file << Scooters.size() << std::endl;
        for (const auto& scooter : Scooters) {
            file << scooter.getIdentifier() << ',';
            file << scooter.getModel() << ',';
            file << scooter.getDate() << ',';
            file << scooter.getKilometers() << ',';
            file << scooter.getLocation() << ',';
            file << scooter.getUser() << ',';
            file << static_cast<int>(scooter.getStatus()) << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Error opening file: " << fileName << endl;
    }
}


repository::CsvFileRepository &repository::CsvFileRepository::operator=(const repository::CsvFileRepository &other) {
    if (this == &other)
    {
        return *this;
    }

    // Perform deep copy of the Scooters vector
    Scooters = other.Scooters;

    return *this;
}

repository::CsvFileRepository::~CsvFileRepository()
{
    saveToFile();
}
