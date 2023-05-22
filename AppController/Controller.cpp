//
// Created by Robert on 13/05/2023.
//

#include "Controller.h"
#include "Scooter.h"
#include <stdexcept>
#include <utility>
using std::vector;

controller::Controller::Controller(shared_ptr<CrudRepository> repository) {
    this->repository = std::move(repository);
}

controller::Controller::~Controller() = default;

string controller::Controller::generateID() {
    string ID = "---";
    string s1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = static_cast<int>(s1.length());

    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            for(int k = 0; k < len; k++) {
                ID[0] = s1[i];
                ID[1] = s1[j];
                ID[2] = s1[k];
                if(checkIDAvailability(ID)) {
                    return ID;
                }
            }
        }
    }
    throw std::overflow_error("Repo is full, no available ID left");
}

bool controller::Controller::checkIDAvailability(const string& ID) {
    auto allScooters = repository->getAllScootersFromRepo();
    for(const Scooter& currentScooter : *allScooters) { //NOLINT
        if(currentScooter.getIdentifier() == ID) {
            return false;
        }
    }
    return true;
}

Scooter controller::Controller::findScooterById(const string& ID) {
    auto allScooters = repository->getAllScootersFromRepo();
    for(const Scooter& currentScooter : *allScooters) { //NOLINT
        if(currentScooter.getIdentifier() == ID) {
            return currentScooter;
        }
    }
    throw std::invalid_argument("Given scooter ID is not in repo");
}

bool controller::Controller::reserveScooter(const string& ID, const string& userName) {
    if(checkIDAvailability(ID))
    {
        return false;
    }
    Scooter scooter = findScooterById(ID);
    Scooter oldScooter = scooter;
    if(scooter.getStatus() == PARKED)
    {
        scooter.setStatus(RESERVED);
        scooter.setUser(userName);
        repository->updateScooterInfo(oldScooter, scooter);
        return true;
    }
    return false;
}

void controller::Controller::addScooterToRepo(string model, std::string manufacturingDate, double km, string location, ScooterStatus status) {
    string ID = generateID();
    Scooter newScooter(ID, std::move(model), std::move(manufacturingDate), km, std::move(location), status);
    newScooter.setUser("");
    repository->addScooter(newScooter);
}

bool controller::Controller::deleteScooterFromRepo(const string& ID) {
    auto allScooters = repository->getAllScootersFromRepo();
    for(const Scooter& currentScooter : *allScooters) { //NOLINT
        if(currentScooter.getIdentifier() == ID) {
            repository->deleteScooter(currentScooter);
            return true;
        }
    }
    return false;
}

bool controller::Controller::modifyScooterFromRepo(const string& ID, double km, const string& location, ScooterStatus status) {
    Scooter oldScooter = findScooterById(ID);
    Scooter updatedScooter = oldScooter;

    if(km != -1) {
        updatedScooter.setKilometers(km);
    }

    if(!location.empty()) {
        updatedScooter.setLocation(location);
    }

    if(status != UNKNOWN) {
        updatedScooter.setStatus(status);
    }

    repository->updateScooterInfo(oldScooter, updatedScooter);
    return true;
}

shared_ptr<vector<Scooter>> controller::Controller::filterScootersByLocation(string location) {
    return repository->getAllScootersByLocation(std::move(location));
}

shared_ptr<vector<Scooter>> controller::Controller::filterScootersByKmBetweenTwoValues(double kmMin, double kmMax) {
    return repository->getAllScootersByKmBetweenTwoValues(kmMin, kmMax);
}

shared_ptr<vector<Scooter>> controller::Controller::filterScootersByAgeBetweenTwoDates(string dateMin, string dateMax)
{
    return repository->getAllScootersByAgeBetweenTwoDates(std::move(dateMin), std::move(dateMax));
}

shared_ptr<vector<Scooter>> controller::Controller::sortScootersByDate() {
    struct manufacturingDate {
        int day, month, year;
    };

    struct S_manufacturingDate {
        string S_day, S_month, S_year;
    };

    shared_ptr<vector<Scooter>> allScooters = repository->getAllScootersFromRepo();
    vector<Scooter> scooters;
    for(const Scooter& currentScooter : *allScooters) {
        scooters.push_back(currentScooter);
    }

    vector<manufacturingDate> manufacturingDates(scooters.size());

    for(int i = 0; i < scooters.size(); i++) {
        Scooter scooter = scooters[i];

        string S_manufacturingDate_scooter = scooter.getDate();

        S_manufacturingDate currentManufacturingDate;
        currentManufacturingDate.S_day = S_manufacturingDate_scooter.substr(0, 2);
        currentManufacturingDate.S_month = S_manufacturingDate_scooter.substr(3, 2);
        currentManufacturingDate.S_year = S_manufacturingDate_scooter.substr(6,4);

        manufacturingDates[i].day = stoi(currentManufacturingDate.S_day);
        manufacturingDates[i].month = stoi(currentManufacturingDate.S_month);
        manufacturingDates[i].year = stoi(currentManufacturingDate.S_year);
    }

    for(int i = 0; i < scooters.size() - 1; i++) {
        for(int j = i + 1; j < scooters.size(); j++) {

            manufacturingDate auxiliary; //NOLINT
            Scooter auxiliaryScooter = scooters[i];

            if(manufacturingDates[i].year > manufacturingDates[j].year) { //NOLINT
                auxiliary = manufacturingDates[i];
                manufacturingDates[i] = manufacturingDates[j];
                manufacturingDates[j] = auxiliary;

                auxiliaryScooter = scooters[i];
                scooters[i] = scooters[j];
                scooters[j] = auxiliaryScooter;
            }
            else if (manufacturingDates[i].year == manufacturingDates[j].year and manufacturingDates[i].month > manufacturingDates[j].month) {
                auxiliary = manufacturingDates[i];
                manufacturingDates[i] = manufacturingDates[j];
                manufacturingDates[j] = auxiliary;

                auxiliaryScooter = scooters[i];
                scooters[i] = scooters[j];
                scooters[j] = auxiliaryScooter;
            }
            else if (manufacturingDates[i].year == manufacturingDates[j].year and manufacturingDates[i].month == manufacturingDates[j].month and manufacturingDates[i].day > manufacturingDates[j].day) {
                auxiliary = manufacturingDates[i];
                manufacturingDates[i] = manufacturingDates[j];
                manufacturingDates[j] = auxiliary;

                auxiliaryScooter = scooters[i];
                scooters[i] = scooters[j];
                scooters[j] = auxiliaryScooter;
            }
        }
    }
    auto result = std::make_shared<vector<Scooter>>();
    for(const Scooter& scooter : scooters) {
        result->push_back(scooter);
    }
    return result;
}

shared_ptr<vector<Scooter>> controller::Controller::sortScootersByID() {
    auto allScooters = repository->getAllScootersFromRepo();

    vector<Scooter> scooters;
    for(const Scooter& scooter : *allScooters) {
        scooters.push_back(scooter);
    }

    for(int i = 0; i < scooters.size() - 1; i++) {
        for(int j = i + 1; j < scooters.size(); j++) {
            Scooter auxiliaryScooter = scooters[i];
            string id1 = scooters[i].getIdentifier();
            string id2 = scooters[j].getIdentifier();
            if(id1 > id2) {
                auxiliaryScooter = scooters[i];
                scooters[i] = scooters[j];
                scooters[j] = auxiliaryScooter;
            }
        }
    }
    auto result = std::make_shared<vector<Scooter>>();
    for(const Scooter& scooter : scooters) {
        result->push_back(scooter);
    }

    return result;
}

shared_ptr<vector<Scooter>> controller::Controller::filterParkedScooters() {
    return repository->getAllParkedScooters();
}

shared_ptr<vector<Scooter>> controller::Controller::getAllReservedScootersOfAnUser(string userName) {
    return repository->getAllScootersReservedByAnUser(std::move(userName));
}


void controller::Controller::load()
{
    repository->loadFromFile();
}
