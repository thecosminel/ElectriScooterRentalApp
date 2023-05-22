#pragma once

#include "AppController/Controller.h"
#include "Utils/AuxiliaryFunctions.h"

using namespace controller;

namespace managerUi
{
    class ManagerUI {
    private:
        shared_ptr<Controller> controller;

    public:

        /// Explicit constructor
        explicit ManagerUI(shared_ptr<Controller> controller);

        /// Trivial destructor
        ~ManagerUI()=default;

        /// Copy-constructor
        ManagerUI(ManagerUI& managerUi) = default;

        /// Assignment operator
        ManagerUI& operator=(const ManagerUI& repository) = default;

        /// Method to run manager UI
        /// \return true to go back to main UI, false to exit
        bool run();

        /// Method for exiting the app
        void exit();

        /// Method to add a new scooter
        void addNewScooter();

        /// Method to delete an existing scooter
        void deleteExistingScooter();

        /// Method to modify an existing scooter
        bool modifyExistingScooter();

        /// Method to search for a certain scooter by location
        void searchScooterByLocation();

        /// Method to display certain scooters filtered by range of kilometers
        void displayScootersFilteredByKm();

        /// Method to display certain scooters filtered by age
        void displayScootersFilteredByAge();

        /// Method to display certain scooters sorted by age
        void displayAllScootersSortedByAge();

        /// Method to display certain scooters sorted by ID
        void displayAllScootersSortedByID();
    };
}
