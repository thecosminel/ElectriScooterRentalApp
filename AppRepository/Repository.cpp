//
// Created by naomi on 5/13/2023.
//
#include "Repository.h"
#include <iostream>
#include <fstream>
#include <memory>
//modificare
void repository::Repository::addScooter(const Scooter &scooter)
{
    Scooters.push_back(scooter);
}

void repository::Repository::deleteScooter(const Scooter &scooter)
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

void repository::Repository::updateScooterInfo(const Scooter& oldScooter, const Scooter& updatedScooter)
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

//vector<Scooter> repository::Repository::getAllScootersFromRepo() const
shared_ptr<vector<Scooter>>  repository::Repository::getAllScootersFromRepo() const
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const auto& scooter : Scooters)
        result->push_back(scooter);
    return result;
}

void repository::Repository::saveToFile(const std::string& fileName)
{
    std::ofstream file(fileName);
    if (file.is_open())
    {
        file << Scooters.size() << endl;
        for (const auto& scooter : Scooters)
        {
            file << scooter.getIdentifier() << ' ';
            file << scooter.getModel() << ' ';
            file << scooter.getDate() << ' ';
            file << scooter.getKilometers() << ' ';
            file << scooter.getLocation() << ' ';
            file << static_cast<int>(scooter.getStatus()) << endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Error opening file: " << fileName << endl;
    }
}

void repository::Repository::loadFromFile(const std::string& fileName)
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

shared_ptr<vector<Scooter>> repository::Repository::getAllScootersByLocation(string location)
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
        if (scooter.getLocation() == location)
        {
            result->push_back(scooter);
        }
    }
    return result;
}

shared_ptr<vector<Scooter>> repository::Repository::getAllScootersByKmBetweenTwoValues(double kmMin, double kmMax)
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

shared_ptr<vector<Scooter>> repository::Repository::getAllScootersByAgeBetweenTwoDates(string dateMin, string dateMax)
{
    auto result = std::make_shared<std::vector<Scooter>>();
    for (const Scooter& scooter : Scooters)
    {
       string date = scooter.getDate();
        if (date >= dateMin && date <= dateMax)
        {
            result->push_back(scooter);
        }
    }
    return result;
}

shared_ptr<vector<Scooter>> repository::Repository::getAllParkedScooters()
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

Scooter repository::Repository::getScooterById(string id)
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
