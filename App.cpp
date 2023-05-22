#include "AppUI/MainUI.h"
#include "AppController/ControllerTest.h"
#include "AppRepository/RepositoryTest.h"
#include "AppRepository/Crudrepository.h"
#include <memory>

using namespace mainUi;
using std::make_shared;
using std::shared_ptr;

int main() {
    auto repo = make_shared<Repository>();
    auto ctrl = make_shared<Controller>(repo);
    auto managerUI = make_shared<ManagerUI>(ctrl);
    auto clientUI = make_shared<ClientUI>(ctrl);
    auto mainUI = make_shared<MainUI>(managerUI, clientUI);
//    testAllController();
//    testAllRepo();
    mainUI->runMain();
    return 0;
}
