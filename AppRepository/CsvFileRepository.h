//
// Created by naomi on 5/13/2023.
//
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstring>
#include "Domain/Scooter.h"
#include "Utils/AuxiliaryFunctions.h"
#include "Crudrepository.h"

using namespace scooter;
using std::vector, std::shared_ptr, std::string, std::ifstream, std::endl, std::strcmp;

namespace repository
{

    class CsvFileRepository : CrudRepository{
    private:
        vector<Scooter> Scooters;

    public:
        ///default constructor
        CsvFileRepository() = default;

        CsvFileRepository(CsvFileRepository &repository) = default;
        CsvFileRepository& operator=(const CsvFileRepository& repository) = default;

        ///default destructor
        ~CsvFileRepository() = default;

        /// add an electric scooter to the repository
        /// \param scooter
        void addScooter(const Scooter& scooter) override;

        /// remove an electric scooter from the repository
        /// \param scooter
        void deleteScooter(const Scooter& scooter) override;

        /// update an existing electric oldScooter in the repository
        /// \param oldScooter
        void updateScooterInfo(const Scooter& oldScooter, const Scooter& updatedScooter) override;

        /// get all the electric scooters in the repository
        /// \return
        shared_ptr<vector<Scooter>> getAllScootersFromRepo() const; //NOLINT

        /// Gets all scooters with given location from repo
        /// \param location
        /// \return all matching scooters
        shared_ptr<vector<Scooter>> getAllScootersByLocation (string location);

        /// Gets all scooters with km between two given values
        /// \param kmMin
        /// \param kmMax
        /// \return matching scooters
        shared_ptr<vector<Scooter>> getAllScootersByKmBetweenTwoValues (double kmMin, double kmMax);

        /// Gets all scooters with dates between two given values
        /// \param dateMin
        /// \param dateMax
        /// \return matching scooters
        shared_ptr<vector<Scooter>> getAllScootersByAgeBetweenTwoDates (string dateMin, string dateMax);

        /// Gets all parked scooters (they can be reserved
        /// \return parked scooters
        shared_ptr<vector<Scooter>> getAllParkedScooters();

        /// Gets scooters from repo with given ID
        /// \param id
        /// \return scooters with given id
        Scooter getScooterById (string id);

        /// Gets all scooters reserved by an user
        /// \param userName
        /// \return matching scooters
        shared_ptr<vector<Scooter>> getAllScootersReservedByAnUser (string userName);

        /// method for saving to file
        /// \param fileName
        void saveToFile(const string &fileName) override;

        /// method for loading from file
        /// \param fileName
        void loadFromFile(const string &fileName) override;
    };
}