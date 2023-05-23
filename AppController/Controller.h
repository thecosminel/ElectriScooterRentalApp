//
// Created by Robert on 13/05/2023.
//

#pragma once
#include "../AppRepository/CrudRepository.h"
#include "Scooter.h"
using namespace repository;
using namespace scooter;
using std::string, std::vector;


namespace controller
{
    class Controller {
    private:
        shared_ptr<CrudRepository> repository;

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
        explicit Controller(shared_ptr<CrudRepository> repository);

        ///Copy-constructor
        Controller(Controller& controller) = default;

        ///Assignment operator
        Controller& operator=(const Controller& repository) = default;

        ///Destructor
        ~Controller();

        /// Reserve scooter
        /// \param ID scooter ID
        /// \return true if the scooter was successfully reserved, false otherwise
        bool reserveScooter(const string& ID, const string& username);

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
        bool modifyScooterFromRepo(const string& ID, double km = -1, const string& location = "", ScooterStatus status = UNKNOWN);

        /// Filter scooters by location
        /// \param location string after which to search scooter
        /// \return shared pointer to a vector of scooters that contain the given location string
        shared_ptr<vector<Scooter>> filterScootersByLocation(string location);

        /// Filter scooters that have Km in between two specified values
        /// \param kmMin minimum value to filter
        /// \param kmMax maximum value to filter
        /// \return shared pointer to a vector of scooters that have a km value in between the given values
        shared_ptr<vector<Scooter>> filterScootersByKmBetweenTwoValues(double kmMin, double kmMax);

        /// Filter scooters that have been manufactured in between the given dates
        /// \param dateMin minimum date to filter
        /// \param dateMax maximum date to filter
        /// \return shared pointer to a vector of scooters that have been manufactured in between the given dates
        shared_ptr<vector<Scooter>> filterScootersByAgeBetweenTwoDates(string dateMin, string dateMax);

        /// Sort scooters by age
        /// \return shared pointer to a vector of scooters that have been sorted by their age
        shared_ptr<vector<Scooter>> sortScootersByDate();

        /// Sort scooters by ID
        /// \return shared pointer to a vector of scooters that have been sorted by their ID
        shared_ptr<vector<Scooter>> sortScootersByID();

        /// Filter parked scooters
        /// \return shared pointer to a vector of scooters that are currently parked
        shared_ptr<vector<Scooter>> filterParkedScooters();

        /// Get all reserved scooters of a user
        /// \param userName person's user name
        /// \return shared pointer to a vector of scooters that have been reserved by the respective user
        shared_ptr<vector<Scooter>> getAllReservedScootersOfAnUser(string userName);

    };
}
