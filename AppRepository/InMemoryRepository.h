//
// Created by naomi on 5/13/2023.
//
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Domain/Scooter.h"
#include "Utils/AuxiliaryFunctions.h"

using namespace scooter;
using std::vector, std::shared_ptr, std::string, std::ifstream, std::endl;

namespace repository
{
    class CrudRepository{
    private:
        vector<Scooter> Scooters;

    public:
        ///default constructor
        CrudRepository() = default;

        CrudRepository(CrudRepository &repository) = default;
        CrudRepository& operator=(const CrudRepository& repository) = default;

        ///default destructor
        ~CrudRepository() = default;

        /// add an electric scooter to the repository
        /// \param scooter
        virtual void addScooter(const Scooter& scooter) = 0;

        /// remove an electric scooter from the repository
        /// \param scooter
        virtual void deleteScooter(const Scooter& scooter) = 0;

        /// update an existing electric oldScooter in the repository
        /// \param oldScooter
        virtual void updateScooterInfo(const Scooter& oldScooter, const Scooter& updatedScooter) = 0;

        /// method for loading from file
        /// \param fileName
        virtual void loadFromFile(const string &fileName) = 0;
    };


    class InMemoryRepository : CrudRepository{
    private:
        vector<Scooter> Scooters;

    public:
        ///default constructor
        InMemoryRepository() = default;

        InMemoryRepository(InMemoryRepository &repository) = default;
        InMemoryRepository& operator=(const InMemoryRepository& repository) = default;

        ///default destructor
        ~InMemoryRepository() = default;

        /// add an electric scooter to the repository
        /// \param scooter
        void addScooter(const Scooter& scooter) override;

        /// remove an electric scooter from the repository
        /// \param scooter
        void deleteScooter(const Scooter& scooter);

        /// update an existing electric oldScooter in the repository
        /// \param oldScooter
        void updateScooterInfo(const Scooter& oldScooter, const Scooter& updatedScooter);

        /// get all the electric scooters in the repository
        /// \return
        shared_ptr<vector<Scooter>> getAllScootersFromRepo() const;

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

        /// method for loading from file
        /// \param fileName
        void loadFromFile(const string &fileName) override;
    };
}