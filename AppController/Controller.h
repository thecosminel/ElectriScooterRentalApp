//
// Created by Robert on 13/05/2023.
//

#pragma once
#include "../AppRepository/InMemoryRepository.h"
#include "Scooter.h"
using namespace repository;
using namespace scooter;
using std::string, std::vector;


namespace controller
{
    class Controller {
    private:
        shared_ptr<InMemoryRepository> repository;

        /// Generates an ID for the scooter
        /// \return an original ID for the scooter
        string generateID();

        /// Checks ID of the scooter
        /// \param ID given ID
        /// \return false if the ID is already used, true otherwise
        bool checkIDAvailability(const string& ID);

        /// Gets scooter instance
        /// \param ID given ID
        /// \return scooter instance with the given ID, throws exception if no such scooter was found
        Scooter findScooterById(const string& ID);

    public:

        ///Constructor
        explicit Controller(shared_ptr<InMemoryRepository> repository);

        ///Copy-constructor
        Controller(Controller& controller) = default;

        ///Assignment operator
        Controller& operator=(const Controller& repository) = default;

        ///Destructor
        ~Controller();

        /// Reserve scooter
        /// \param ID scooter ID
        /// \return true if the scooter was successfully reserved, false otherwise
        bool reserveScooter(const string& ID);

        /// Adds a scooter to the repository
        /// \param ID scooter's ID
        /// \param model scooter's model
        /// \param manufacturingDate scooter's manufacturing date
        /// \param km scooter's km
        /// \param location scooter's last location
        /// \param status scooter's status
        void addScooterToRepo(string model, string manufacturingDate, double km, string location, ScooterStatus status);

        /// Deletes a scooter from the repository
        /// \param ID scooter's ID
        /// \return true if scooter was deleted, false if delete was unsuccessful
        bool deleteScooterFromRepo(const string& ID);

        /// Update scooter from repo
        /// \param ID scooter's ID
        /// \param km scooter's km
        /// \param location scooter's last location
        /// \param status scooter's status
        bool modifyScooterFromRepo(const string& ID, double km = -1, const string& location = "", ScooterStatus status=UNKNOWN);

        /// Filter scooters by location
        /// \param location string after which to search scooter
        /// \return vector of scooters that contain the given location string
        vector<Scooter> filterScootersByLocation(string location);

        /// Filter scooters that have less Km than a specified value
        /// \param km maximum value to filter
        /// \return vector of instances that have fewer km than the given value
        vector<Scooter> filterScootersByKm(double km);

        /// Filter scooters that have been manufactured after the given date
        /// \param manufacturingDate manufacturing date to filter
        /// \return vector of instances that have been manufactured after the given date
        vector<Scooter> filterScootersByDate(const string& manufacturingDate);

        /// Sort scooters by age
        /// \return vector of instances that have been sorted by their age
        vector<Scooter> sortScootersByAge();

        /// Sort scooters by ID
        /// \return vector of instances that have been sorted by their ID
        vector<Scooter> sortScootersByID();

        /// Save scooter instances to repo
        void save();

        /// Load scooter instances to repo
        void load();
    };
}
