//
// Created by george on 5/12/2023.
//

#include "ManagerUI.h"
#include <iostream>

using std::cout, std::cin, std::endl;

bool managerUi::ManagerUI::run()
{
    controller->load();
    cout << "\n\n\nManager interface -->" << endl;
    char choice;
    do
    {
        pressEnterToContinue();
        cout << "Choose option: " << endl;
        cout << "  1. Add new scooter" << endl;
        cout << "  2. Delete existing scooter" << endl;
        cout << "  3. Modify existing scooter" << endl;
        cout << "  4. Search scooter by location" << endl;
        cout << "  5. Display scooters with km between two values" << endl;
        cout << "  6. Display scooters manufactured between two dates" << endl;
        cout << "  7. Display all scooters sorted ascending by manufacturing date" << endl;
        cout << "  8. Display all scooters sorted ascending by ID" << endl;
        cout << "  R. Return to main ui" << endl;
        cout << "  X. Close app" << endl;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
            case '1':
                cout << "Add new scooter: ";
                addNewScooter();
                break;
            case '2':
                cout << "Delete existing scooter: ";
                deleteExistingScooter();
                break;
            case '3':
                cout << "Modify existing scooter: ";
                if(modifyExistingScooter())
                    cout << "Modify successful";
                else
                    cout << "Modify failed";
                break;
            case '4':
                cout << "Search scooter by location: ";
                searchScooterByLocation();
                break;
            case '5':
                cout << "Display scooters with km less than:  ";
                displayScootersFilteredByKm();
                break;
            case '6':
                cout << "Display scooters newer than date:  ";
                displayScootersFilteredByAge();
                break;
            case '7':
                cout << "Display all scooters sorted ascending by age: ";
                displayAllScootersSortedByAge();
                break;
            case '8':
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

void managerUi::ManagerUI::addNewScooter()
{
    string model = enterModel();
    string manufacturingDate = enterManufacturingDate();
    double km = enterKm();
    string location = enterLocation();
    ScooterStatus status = enterStatus();
    controller->addScooterToRepo (model, manufacturingDate, km, location, status);
}

void managerUi::ManagerUI::deleteExistingScooter()
{
    string ID = enterID();
    if (controller->deleteScooterFromRepo(ID))
    {
        cout << endl << "Delete successful!";
    }
    else
    {
        cout << endl << "Delete failed!";
    }
}

bool managerUi::ManagerUI::modifyExistingScooter()
{
    string ID = enterID();
    double km;
    string location;
    ScooterStatus status;
    cout << "Modify scooter" << endl;
    char choice;
    do
    {
        pressEnterToContinue();
        cout << "Choose option: " << endl;
        cout << "  1. Modify km" << endl;
        cout << "  2. Modify location" << endl;
        cout << "  3. Modify status" << endl;
        cout << "  C. Cancel" << endl;
        cin >> choice;
        cout << endl;
        bool result;
        switch (choice)
        {
            case '1':
                cout << "Modify km: ";
                km = enterKm();
                result = controller->modifyScooterFromRepo(ID, km);
                return result;
            case '2':
                cout << "Modify location: ";
                location = enterLocation();
                result = controller->modifyScooterFromRepo(ID, -1, location);
                return result;
            case '3':
                cout << "Modify status: ";
                status = enterStatus();
                result = controller->modifyScooterFromRepo(ID, -1, "", status);
                return result;
            case 'c':
            case 'C':
                cout << "\n\n Closing app.....";
                return false;
            default:
                cout << "Not an option...";
                break;
        }
    }
    while (choice);
    return false;
}

void managerUi::ManagerUI::searchScooterByLocation()
{
    string location = enterLocation();
    shared_ptr<vector<Scooter>> scooters = controller->filterScootersByLocation(location);
    printScooterContainer(scooters);
}

void managerUi::ManagerUI::displayScootersFilteredByKm()
{
    pair<double, double> km = enterKmMultiple();
    shared_ptr<vector<Scooter>> scooters = controller->filterScootersByKmBetweenTwoValues(km.first, km.second);
    printScooterContainer(scooters);
}

void managerUi::ManagerUI::displayScootersFilteredByAge()
{
    pair <string, string> dates;
    dates = enterManufacturingDates();
    shared_ptr<vector<Scooter>> scooters = controller->filterScootersByAgeBetweenTwoDates(dates.first, dates.second);
    printScooterContainer(scooters);
}

void managerUi::ManagerUI::displayAllScootersSortedByAge()
{
    shared_ptr<vector<Scooter>> scooters = controller->sortScootersByDate();
    printScooterContainer(scooters);
}

void managerUi::ManagerUI::displayAllScootersSortedByID()
{
    shared_ptr<vector<Scooter>> scooters =controller->sortScootersByID();
    printScooterContainer(scooters);
}

managerUi::ManagerUI::ManagerUI(shared_ptr<Controller> controller)
{
    this->controller = std::move(controller);
}

void managerUi::ManagerUI::exit() //NOLINT
{
    cout << "\n\n Closing app.....";
}

