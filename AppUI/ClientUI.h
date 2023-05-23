#pragma once
#include "AppController/Controller.h"
#include <memory>
#include "Utils/AuxiliaryFunctions.h"
using std::shared_ptr, std::pair;

using namespace controller;

namespace clientUi
{
    class ClientUI{
    private:
        shared_ptr<Controller> controller;
        string userName;

    public:
        /// Explicit constructor
        explicit ClientUI(shared_ptr<Controller> controller);

        /// Trivial destructor
        ~ClientUI()=default;

        /// Copy-constructor
        ClientUI(ClientUI& managerUi) = default;

        ///Assignment operator
        ClientUI& operator=(const ClientUI& repository) = default;

        /// Method to run the app
        /// \return true to go back to main UI, false to exit
        bool run();

        /// Method for exiting the app
        void exit();

        /// Method for searching a certain scooter by location
        void searchScooterByLocation();

        /// Method for displaying certain scooters filtered by kilometer range
        void displayScootersFilteredByKM();

        /// Method for displaying certain scooters filtered by age
        void displayScootersFilteredByAge();

        /// Method for displaying certain scooters reserved by an user
        void displayScootersReservedByUser();

        /// Method for displaying reservable scooters (parked)
        void displayScootersThatCanBeReserved();

        /// Method to display certain scooters sorted by ID
        void displayAllScootersSortedByID();

        /// Method for reserving a scooter
        void reserveScooter();
    };
}