//
// Created by george on 5/12/2023.
//

#include "ClientUI.h"
#include <iostream>

using std::cout, std::cin, std::endl;

// Sunt smecher

void clientUi::ClientUI::run()
{
    controller->load();
    cout << "\n\n\nDear Client, welcome to our Electric Scooter Rental App!!" << endl;
    char choice;
    do
    {
        pressEnterToContinue();
        cout << "Choose option: " << endl;
        cout << "  1. Search scooter by location" << endl;
        cout << "  2. Display scooters with km less than x" << endl;
        cout << "  3. Display scooters newer than date" << endl;
        cout << "  4. Reserve scooter" << endl;
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
                cout << "Reserve scooter: ";
                reserveScooter();
                break;
            case 'X':
            case 'x':
                exit();
                return;
            default:
                cout << "Not an option...";
                break;
        }
    }
    while (choice);
}

void clientUi::ClientUI::searchScooterByLocation()
{
    string location = enterLocation();
    vector<Scooter> scooters = controller->filterScootersByLocation(location);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::displayScootersFilteredByKM()
{
    double km = enterKm();
    vector<Scooter> scooters = controller->filterScootersByKm(km);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::displayScootersFilteredByAge()
{
    string manufacturingDate = enterManufacturingDate();
    vector<Scooter> scooters = controller->filterScootersByDate(manufacturingDate);
    printScooterContainer(scooters);
}

void clientUi::ClientUI::reserveScooter()
{
    string ID = enterID();
    while (!checkIdFormat(ID))
    {
        cout << endl << "Please enter a valid ID: ";
    }
    if (controller->reserveScooter(ID))
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
}

void clientUi::ClientUI::exit()
{
    cout << "\n\n Closing app.....";
    controller->save();
}

