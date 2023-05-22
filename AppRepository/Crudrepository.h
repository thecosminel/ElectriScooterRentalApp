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

        CrudRepository &operator=(const CrudRepository &repository) = default;

        ///default destructor
        ~CrudRepository() = default;

        /// add an electric scooter to the repository
        /// \param scooter
        virtual void addScooter(const Scooter &scooter) = 0;

        /// remove an electric scooter from the repository
        /// \param scooter
        virtual void deleteScooter(const Scooter &scooter) = 0;

        /// update an existing electric oldScooter in the repository
        /// \param oldScooter
        virtual void updateScooterInfo(const Scooter &oldScooter, const Scooter &updatedScooter) = 0;


        /// method for saving to file
        /// \param fileName
        virtual void saveToFile(const string &fileName) = 0;

        /// method for loading from file
        /// \param fileName
        virtual void loadFromFile(const string &fileName) = 0;
    };
};