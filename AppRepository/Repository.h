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

using namespace scooter;
using std::vector, std::shared_ptr, std::string, std::ifstream, std::endl, std::strcmp;

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

        /// get all the electric scooters in the repository
        /// \return
        [[nodiscard]] virtual  shared_ptr<vector<Scooter>> getAllScootersFromRepo() const = 0;

        /// method for saving to file
        /// \param fileName
        virtual void saveToFile(const string &fileName) = 0;

        /// method for loading from file
        /// \param fileName
        virtual void loadFromFile(const string &fileName) = 0;
    };


    class Repository : CrudRepository{
    private:
        vector<Scooter> Scooters;

    public:
        ///default constructor
        Repository() = default;

        Repository(Repository &repository) = default;
        Repository& operator=(const Repository& repository) = default;

        ///default destructor
        ~Repository() = default;

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
        [[nodiscard]] shared_ptr<vector<Scooter>> getAllScootersFromRepo() const override;

        /// Gets all scooters with given location from repo
        /// \param location
        /// \return all matching scooters
        shared_ptr<vector<Scooter>> getAllScootersByLocation (string location) override;

        /// Gets all scooters with km between two given values
        /// \param kmMin
        /// \param kmMax
        /// \return matching scooters
        shared_ptr<vector<Scooter>> getAllScootersByKmBetweenTwoValues (double kmMin, double kmMax) override;

        /// Gets all scooters with dates between two given values
        /// \param dateMin
        /// \param dateMax
        /// \return matching scooters
        shared_ptr<vector<Scooter>> getAllScootersByAgeBetweenTwoDates (string dateMin, string dateMax) override;

        /// Gets all parked scooters (they can be reserved
        /// \return parked scooters
        shared_ptr<vector<Scooter>> getAllParkedScooters() override;

        /// Gets scooters from repo with given ID
        /// \param id
        /// \return scooters with given id
        Scooter getScooterById (string id) override;

        /// Gets all scooters reserved by an user
        /// \param userName
        /// \return matching scooters
        shared_ptr<vector<Scooter>> getAllScootersReservedByAnUser (string userName) override;

        /// method for saving to file
        /// \param fileName
        void saveToFile(const string &fileName) override;

        /// method for loading from file
        /// \param fileName
        void loadFromFile(const string &fileName) override;
    };
}