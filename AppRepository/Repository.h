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
    class Repository {
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
        void addScooter(const Scooter& scooter);

        /// remove an electric scooter from the repository
        /// \param scooter
        void deleteScooter(const Scooter& scooter);

        /// update an existing electric oldScooter in the repository
        /// \param oldScooter
        void updateScooterInfo(const Scooter& oldScooter, const Scooter& updatedScooter);

        /// get all the electric scooters in the repository
        /// \return
        [[nodiscard]] vector<Scooter> getAllScootersFromRepo() const;

        /// method for saving to file
        /// \param fileName
        void saveToFile(const string &fileName);

        /// method for loading from file
        /// \param fileName
        void loadFromFile(const string &fileName);
    };
}
