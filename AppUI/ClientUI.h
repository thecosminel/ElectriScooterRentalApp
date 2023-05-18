#pragma once
#include "AppController/Controller.h"
#include <memory>
#include "Utils/AuxiliaryFunctions.h"
using std::shared_ptr;

using namespace controller;

namespace clientUi
{
    class ClientUI{
    private:
        shared_ptr<Controller> controller;

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
        void run();

        /// Method for exiting the app
        void exit();

        /// Method for searching a certain scooter by location
        void searchScooterByLocation();

        /// Method for displaying certain scooters filtered by kilometer range
        void displayScootersFilteredByKM();

        /// Method for displaying certain scooters filtered by age
        void displayScootersFilteredByAge();

        /// Method for reserving a scooter
        void reserveScooter();
    };
}