#pragma once
#include "ManagerUI.h"
#include "ClientUI.h"

#include <memory>
using namespace managerUi;
using namespace clientUi;
using std::shared_ptr;

namespace mainUi
{
    class MainUI {
    private:
        shared_ptr<ManagerUI> managerUi;
        shared_ptr<ClientUI> clientUi;

    public:
        /// Constructor
        /// \param ctrl
        MainUI(shared_ptr<ManagerUI> &managerUI, shared_ptr<ClientUI> &clientUi);

        /// Trivial destructor
        ~MainUI()=default;

        /// Copy-constructor
        MainUI(MainUI& managerUi) = default;

        /// Assignment operator
        MainUI& operator=(const MainUI& repository) = default;

        /// Method to run the menu
        void runMain();
    };
}




