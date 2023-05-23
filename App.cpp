#include "AppUI/MainUI.h"
//#include "AppController/ControllerTest.h"
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
    // In memory
//    shared_ptr<CrudRepository> repo_memo;
//    repo_memo = make_shared<InMemoryRepository>();
//    // CSV
//    auto repo_csv = make_shared<CsvFileRepository>();
//    shared_ptr<CrudRepository> repo_csv_crude =repo_csv;
//    shared_ptr<Controller> ctrl;
//    if (choseIfSaveActions())
//    {
//        ctrl = make_shared<Controller>(repo_csv_crude);
//    }
//    else
//    {
//        ctrl = make_shared<Controller>(repo_memo);
//    }
//    auto managerUI = make_shared<ManagerUI>(ctrl);
//    auto clientUI = make_shared<ClientUI>(ctrl);
//    auto mainUI = make_shared<MainUI>(managerUI, clientUI);
//
//    mainUI->runMain();
//    repo_csv->saveToFile();
//    return 0;
testAllRepo();
}
