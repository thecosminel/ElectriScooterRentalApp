//
// Created by naomi on 5/13/2023.
//
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Domain/Scooter.h"

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

        virtual shared_ptr<vector<Scooter>> getAllScootersByLocation (string location) = 0;
        // kmMin = -1 -> no min limit ..... same for kmMax
        virtual shared_ptr<vector<Scooter>> getAllScootersByKmBetweenTwoValues (double kmMin, double kmMax) = 0;
        virtual shared_ptr<vector<Scooter>> getAllScootersByAgeBetweenTwoDates (string dateMin, string dateMax) = 0;
        virtual shared_ptr<vector<Scooter>> getAllParkedScooters() = 0;
        virtual Scooter getScooterById (string id) = 0;
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

        shared_ptr<vector<Scooter>> getAllScootersByLocation (string location) override;
        // kmMin = -1 -> no min limit ..... same for kmMax
        shared_ptr<vector<Scooter>> getAllScootersByKmBetweenTwoValues (double kmMin, double kmMax) override;
        shared_ptr<vector<Scooter>> getAllScootersByAgeBetweenTwoDates (string dateMin, string dateMax) override;
        shared_ptr<vector<Scooter>> getAllParkedScooters() override;
        Scooter getScooterById (string id) override;
        shared_ptr<vector<Scooter>> getAllScootersReservedByAnUser (string userName) override;

        /// method for saving to file
        /// \param fileName
        void saveToFile(const string &fileName) override;

        /// method for loading from file
        /// \param fileName
        void loadFromFile(const string &fileName) override;
    };
}