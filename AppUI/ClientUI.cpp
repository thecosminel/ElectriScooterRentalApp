//
// Created by george on 5/12/2023.
//

#include "ClientUI.h"
#include <iostream>

using std::cout, std::cin, std::endl;

// Sunt smecher

bool clientUi::ClientUI::run()
{
    // Login
    this->userName = enterUserName();
    cout << "\n\n\nDear Client, welcome to our Electric Scooter Rental App!!" << endl;
    char choice;
    do
    {
        pressEnterToContinue();
        cout << "Choose option: " << endl;
        cout << "  1. Search scooter by location" << endl;
        cout << "  2. Display scooters with km between x and y" << endl;
        cout << "  3. Display scooters between two manufacturing dates" << endl;
        cout << "  4. Print available scooters to reserve" << endl; // Implement
        cout << "  5. Reserve scooter" << endl;
        cout << "  6. Print my reserved scooters" << endl; // Implement
        cout << "  7. Display all scooters sorted ascending by ID" << endl;
        cout << "  R. Return to main UI" << endl;
        cout << "  X. Close app" << endl;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
            case '1':
                cout << "Search scooter by location: ";
                searchScooterByLocation();
                break;
            case '2':
                cout << "Display scooters with km less than: ";
                displayScootersFilteredByKM();
                break;
            case '3':
                cout << "Display scooters newer than date: ";
                displayScootersFilteredByAge();
                break;
            case '4':
                cout << "Print available scooters to reserve: ";
                displayScootersThatCanBeReserved();
                break;
            case '5':
                cout << "Reserve scooter: ";
                reserveScooter();
                break;
            case '6':
                cout << "Print my reserved scooters: ";
                displayScootersReservedByUser();
                break;
            case '7':
                cout << "Display all scooters sorted ascending by ID: ";
                displayAllScootersSortedByID();
                break;
            case 'R':
            case 'r':
                exit();
                return true;
            case 'X':
            case 'x':
                exit();
                return false;
            default:
                cout << "Not an option...";
                break;
        }
    }
    while (choice);
    return false;
}

void clientUi::ClientUI::searchScooterByLocation()
{
    string location = enterLocation();
    shared_ptr<vector<Scooter>> scooters = controller->filterScootersByLocation(location);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::displayScootersFilteredByKM()
{
    pair<double, double> km = enterKmMultiple();
    shared_ptr<vector<Scooter>> scooters = controller->filterScootersByKmBetweenTwoValues(km.first, km.second);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::displayScootersFilteredByAge()
{
    pair <string, string> dates;
    dates = enterManufacturingDates();
    shared_ptr<vector<Scooter>> scooters = controller->filterScootersByAgeBetweenTwoDates(dates.first, dates.second);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::reserveScooter()
{
    string ID = enterID();
    while (!checkIdFormat(ID))
    {
        cout << endl << "Please enter a valid ID: ";
    }
    if (controller->reserveScooter(ID, this->userName))
    {
        cout << "Scooter " << ID << " successfully reserved";
    }
    else
    {
        cout << "Invalid! Scooter not reserved, because it might not exist or is not available";
    }
}

clientUi::ClientUI::ClientUI(shared_ptr<Controller> controller)
{
    this->controller = std::move(controller);
    this->userName = "";
}

void clientUi::ClientUI::exit() //NOLINT
{
    cout << "\n\n Closing app.....";
}

void clientUi::ClientUI::displayScootersReservedByUser()
{
    shared_ptr<vector<Scooter>> scooters = controller->getAllReservedScootersOfAnUser(userName);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::displayScootersThatCanBeReserved()
{
    shared_ptr<vector<Scooter>> scooters = controller->filterParkedScooters();
    printScooterContainer(scooters);
}

void clientUi::ClientUI::displayAllScootersSortedByID()
{
    shared_ptr<vector<Scooter>> scooters =controller->sortScootersByID();
    printScooterContainer(scooters);
}
