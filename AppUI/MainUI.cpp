//
// Created by george on 5/12/2023.
//

#include "MainUI.h"
#include <iostream>
#include <utility>
using std::cout, std::cin, std::endl;


void mainUi::MainUI::runMain()
{
    bool restartMainUi;
    do
    {
        cout << endl << endl;
        cout << "Welcome to our Electric Scooter Rental App!!" << endl;
        cout << "What are you?" << endl;
        cout << " 1. Manager" << endl;
        cout << " 2. User" << endl;
        cout << "I am: ";
        int choice; cin >> choice;
        while (choice != 1 && choice != 2)
        {
            cout << "Choose between 1 or 2" << endl;
            cout << "I am: ";
            cin >> choice;
        }
        if (choice == 1)
            restartMainUi = managerUi->run();
        if (choice == 2)
            restartMainUi = clientUi->run();
    } while (restartMainUi);
}

mainUi::MainUI::MainUI(shared_ptr<ManagerUI> managerUI, shared_ptr<ClientUI> clientUi)
{
    this->managerUi = std::move(managerUI);
    this->clientUi = std::move(clientUi);
}



