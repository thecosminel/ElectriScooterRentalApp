//
// Created by naomi on 5/13/2023.
//
#include "InMemoryRepository.h"
#include <iostream>
#include <fstream>
#include <memory>

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
    }
}





void repository::InMemoryRepository::loadFromFile(const std::string& fileName)
{
    ifstream file(fileName);
    if (file.is_open())
    {
        Scooters.clear(); //clear the existing scooters before loading from file
        int size;
        file >> size;
        for (int i = 0; i < size; ++i)
        {
            string identifier;
            string model;
            string date;
            double kilometers;
            string location;
            int status;
            file >> identifier;
            file >> model;
            file >> date;
            file >> kilometers;
            file >> location;
            file >> status;
            auto scooterStatus = static_cast<ScooterStatus>(status);
            Scooter scooter(identifier, model, date, kilometers, location, scooterStatus);
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
        if (scooter.getUser() == userName)
        {
            result->push_back(scooter);
        }
    }
    return result;
}