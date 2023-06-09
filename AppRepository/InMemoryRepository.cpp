#include "InMemoryRepository.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

void repository::InMemoryRepository::addScooter(const Scooter &scooter)
{
    Scooters.push_back(scooter);
}

void repository::InMemoryRepository::deleteScooter(const Scooter &scooter)
{
    //iterator to find 'scooter' object in the 'electricScooters' vector
    auto it = Scooters.begin();
    while (it != Scooters.end())
    {
        if ((*it).checkIfSameIdentifier(scooter))
        {
            Scooters.erase(it);
            return;
        }
        it++;
    }
}

void repository::InMemoryRepository::updateScooterInfo(const Scooter& oldScooter, const Scooter& updatedScooter)
{
    //find the oldScooter in the repository based on its identifier
    //iterator to find 'oldScooter' object in the 'electricScooters' vector
    auto it = Scooters.begin();
    while (it != Scooters.end() && !(*it).checkIfSameIdentifier(oldScooter))
    {
        it++;
    }
    if (it != Scooters.end())
    {
        //update the attributes of the oldScooter with the new values
        (*it).setModel(updatedScooter.getModel());
        (*it).setDate(updatedScooter.getDate());
        (*it).setKilometers(updatedScooter.getKilometers());
        (*it).setLocation(updatedScooter.getLocation());
        (*it).setStatus(updatedScooter.getStatus());
        (*it).setUser(updatedScooter.getUser());
    }
}

void repository::InMemoryRepository::loadFromFile(const std::string& fileName)
{
    ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    if (file.is_open())
    {

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string element;

            std::string identifier;
            std::string model;
            std::string date;
            double kilometers;
            std::string location;
            string userName;
            int status;

            // Read each element separated by commas
            std::getline(ss, identifier, ',');
            std::getline(ss, model, ',');
            std::getline(ss, date, ',');
            ss >> kilometers;
            ss.ignore(); // Ignore the comma after 'kilometers'
            std::getline(ss, location, ',');
            std::getline(ss, userName, ',');
            ss >> status;

            auto scooterStatus = static_cast<ScooterStatus>(status);
            Scooter scooter(identifier, model, date, kilometers, location, scooterStatus);
            scooter.setUser(userName);
            Scooters.push_back(scooter);
        }
        file.close();
    }
    else
    {
        std::cout << "Error opening file: " << fileName << std::endl;
    }
}



shared_ptr<vector<Scooter>> repository::InMemoryRepository::getAllScootersByLocation(string location)
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
        for (auto &c : location)
            c = tolower(c); //NOLINT
        string currentLocation = scooter.getLocation();
        for (auto &c : currentLocation)
            c = tolower(c); //NOLINT
        if (currentLocation.find(location) != std::string::npos)
        {
            result->push_back(scooter);
        }
    }
    return result;
}

shared_ptr<vector<Scooter>> repository::InMemoryRepository::getAllScootersByKmBetweenTwoValues(double kmMin, double kmMax)
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
        double km = scooter.getKilometers();
        if ((kmMin == -1 || km >= kmMin) && (kmMax == -1 || km <= kmMax))
        {
            result->push_back(scooter);
        }
    }
    return result;
}

shared_ptr<vector<Scooter>> repository::InMemoryRepository::getAllScootersByAgeBetweenTwoDates(string dateMin, string dateMax)
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
        string date = scooter.getDate();
        if (compareManufacturingDates(dateMin, date) && compareManufacturingDates(date, dateMax))
        {
            result->push_back(scooter);
        }
    }
    return result;
}

shared_ptr<vector<Scooter>> repository::InMemoryRepository::getAllParkedScooters()
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
        if (scooter.getStatus() == ScooterStatus::PARKED)
        {
            result->push_back(scooter);
        }
    }
    return result;
}

Scooter repository::InMemoryRepository::getScooterById(string id)
{
    for (const Scooter& scooter : Scooters)
    {
        if (scooter.getIdentifier() == id)
        {
            return scooter;
        }
    }
    return {};
}

shared_ptr<vector<Scooter>> repository::InMemoryRepository::getAllScootersReservedByAnUser(string userName)
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
        if (scooter.getUser() == userName && scooter.getStatus() == RESERVED)
        {
            result->push_back(scooter);
        }
    }
    return result;
}

shared_ptr<vector<Scooter>> repository::InMemoryRepository::getAllScootersFromRepo()
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const auto& scooter : Scooters)
        result->push_back(scooter);
    return result;
}

repository::InMemoryRepository &repository::InMemoryRepository::operator=(const repository::InMemoryRepository &other) {
    if (this == &other)
    {
        return *this;
    }

    // Perform deep copy of the Scooters vector
    Scooters = other.Scooters;

    return *this;
}

repository::InMemoryRepository::InMemoryRepository()
{
    loadFromFile();
}
