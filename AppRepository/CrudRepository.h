#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstring>
#include "Domain/Scooter.h"
#include "Utils/AuxiliaryFunctions.h"

using namespace scooter;
using std::vector, std::shared_ptr, std::string, std::ifstream, std::endl, std::strcmp;

namespace repository {
    class CrudRepository {
    private:
        vector <Scooter> Scooters;

    public:
        ///default constructor
        CrudRepository() = default;

        CrudRepository(CrudRepository &repository) = default;

        CrudRepository &operator=(const CrudRepository &other);

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

        /// get all the electric scooters in the repository
        /// \return
        virtual shared_ptr<vector<Scooter>> getAllScootersFromRepo() = 0; //NOLINT

        /// Gets all scooters with given location from repo
        /// \param location
        /// \return all matching scooters
        virtual shared_ptr<vector<Scooter>> getAllScootersByLocation (string location) = 0;

        /// Gets all scooters with km between two given values
        /// \param kmMin
        /// \param kmMax
        /// \return matching scooters
        virtual shared_ptr<vector<Scooter>> getAllScootersByKmBetweenTwoValues (double kmMin, double kmMax) = 0;

        /// Gets all scooters with dates between two given values
        /// \param dateMin
        /// \param dateMax
        /// \return matching scooters
        virtual shared_ptr<vector<Scooter>> getAllScootersByAgeBetweenTwoDates (string dateMin, string dateMax) = 0;

        /// Gets all parked scooters (they can be reserved
        /// \return parked scooters
        virtual shared_ptr<vector<Scooter>> getAllParkedScooters() = 0;

        /// Gets scooters from repo with given ID
        /// \param id
        /// \return scooters with given id
        virtual Scooter getScooterById (string id) = 0;

        /// Gets all scooters reserved by an user
        /// \param userName
        /// \return matching scooters
        virtual shared_ptr<vector<Scooter>> getAllScootersReservedByAnUser (string userName) = 0;
    };
};