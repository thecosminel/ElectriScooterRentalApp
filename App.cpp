#include "AppUI/MainUI.h"
#include "AppController/ControllerTest.h"
#include "AppRepository/RepositoryTest.h"
//#include "AppRepository/CrudRepository.h"
#include "AppRepository/CsvFileRepository.h"
#include "AppRepository/InMemoryRepository.h"
#include "Utils/AuxiliaryFunctions.h"
#include <memory>

using namespace repository;
using namespace mainUi;
using std::make_shared;
using std::shared_ptr;

int main() {
//    // Tests
//    testAllRepo();
//    testAllController();

    // Define
    shared_ptr<CrudRepository> repo;
    shared_ptr<Controller> ctrl;
    shared_ptr<MainUI> mainUi;
    shared_ptr<ManagerUI> managerUi;
    shared_ptr<ClientUI> clientUi;

    // Chose save actions and create ctrl
    shared_ptr<CsvFileRepository> repo_in_CSV;
    if (choseIfSaveActions())
    {
        repo_in_CSV = make_shared<CsvFileRepository>();
        repo = repo_in_CSV;
    }
    else
    {
        repo = make_shared<InMemoryRepository>();
    }

    ctrl = make_shared<Controller>(repo);
    managerUi = make_shared<ManagerUI>(ctrl);
    clientUi = make_shared<ClientUI>(ctrl);
    mainUi = make_shared<MainUI>(managerUi, clientUi);

    // Run
    mainUi->runMain();
    // Exit
    repo_in_CSV->saveToFile();

    return 0;

}
