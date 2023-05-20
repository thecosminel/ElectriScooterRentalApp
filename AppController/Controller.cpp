//
// Created by Robert on 13/05/2023.
//

#include "Controller.h"
#include "Scooter.h"
#include "Utils/AuxiliaryFunctions.h"
#include <stdexcept>
#include <utility>
using std::vector;

controller::Controller::Controller(shared_ptr<Repository> repository)
{
    this->repository = std::move(repository);
}

controller::Controller::~Controller() = default;

string controller::Controller::generateID() {
    string s1, s2, s3;
    s1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    s2 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    s3 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string ID = "???";
    int len = static_cast<int>(s1.length());

    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            for(int k = 0; k < len; k++) {
                ID[0] = s1[i];
                ID[1] = s2[j];
                ID[2] = s3[k];
                if(checkIDAvailability(ID)) {
                    return ID;
                }
            }
        }
    }
    throw std::overflow_error("Repo is full, no available ID left");
}

bool controller::Controller::checkIDAvailability(const string& ID) {
    vector<Scooter> allScooters = repository->getAllScootersFromRepo();
    for(int i = 0; i < allScooters.size(); i++) { //NOLINT
        if(allScooters[i].getIdentifier() == ID) {
            return false;
        }
    }
    return true;
}

Scooter controller::Controller::findScooterById(const string& ID) {
    vector<Scooter> allScooters = repository->getAllScootersFromRepo();
    for(int i = 0; i < allScooters.size(); i++) { //NOLINT
        if(allScooters[i].getIdentifier() == ID) {
            return allScooters[i];
        }
    }
    throw std::invalid_argument("Given scooter ID is not in repo");
}

bool controller::Controller::reserveScooter(const string& ID) {
    if(checkIDAvailability(ID)) {
        return false;
    }
    Scooter scooter = findScooterById(ID);
    Scooter oldScooter = scooter;
    if(scooter.getStatus() == PARKED) {
        scooter.setStatus(RESERVED);
        repository->updateScooterInfo(oldScooter, scooter);
        return true;
    }
    return false;
}

void controller::Controller::addScooterToRepo(string model, std::string manufacturingDate, double km, string location, ScooterStatus status) {
    try{
        string ID = generateID();
        Scooter newScooter(ID, std::move(model), std::move(manufacturingDate), km, std::move(location), status);
        repository->addScooter(newScooter);
    }
    catch (...) {
        return;
    }
}

bool controller::Controller::deleteScooterFromRepo(const string& ID) {
    vector<Scooter> allScooters = repository->getAllScootersFromRepo();
    for(int i = 0; i < allScooters.size(); i++) { //NOLINT
        if(allScooters[i].getIdentifier() == ID) {
            repository->deleteScooter(allScooters[i]);
            return true;
        }
    }
    return false;
}

bool controller::Controller::modifyScooterFromRepo(const string& ID, double km, const string& location, ScooterStatus status) {
    try {
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
    catch (...) {
        return false;
    }
}

vector<Scooter> controller::Controller::filterScootersByLocation(string location) {
    for (auto &c : location)
        c = static_cast<char>(tolower(c));
    vector<Scooter> allScooters = repository->getAllScootersFromRepo();
    vector<Scooter> filteredScooters;
    for(int i = 0; i < allScooters.size(); i++) { //NOLINT
        string currentLocation = allScooters[i].getLocation();
        for (auto &c : currentLocation)
            c = static_cast<char>(tolower(c));
        if(currentLocation.find(location) != string::npos) {
            filteredScooters.push_back(allScooters[i]);
        }
    }
    return filteredScooters;
}

vector<Scooter> controller::Controller::filterScootersByKm(double km) {
    vector<Scooter> allScooters = repository->getAllScootersFromRepo();
    vector<Scooter> filteredScooters;

    for(int i = 0; i < allScooters.size(); i++) { // NOLINT
        if(allScooters[i].getKilometers() < km) {
            filteredScooters.push_back(allScooters[i]);
        }
    }

    return filteredScooters;
}

vector<Scooter> controller::Controller::filterScootersByDate(const string& manufacturingDate) {
    vector<Scooter> allScooters = repository->getAllScootersFromRepo();
    vector<Scooter> filteredScooters;

    for(int i = 0; i < allScooters.size(); i++) { // NOLINT
        string scooterManufacturingDate = allScooters[i].getDate();
        if(compareManufacturingDates(manufacturingDate, scooterManufacturingDate)) {
            filteredScooters.push_back(allScooters[i]);
        }
    }

    return filteredScooters;
}

vector<Scooter> controller::Controller::sortScootersByDate() {
    struct manufacturingDate {
        int day, month, year;
    };

    struct S_manufacturingDate {
        string S_day, S_month, S_year;
    };

    vector<Scooter> scooters = repository->getAllScootersFromRepo();
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
    return scooters;
}

vector<Scooter> controller::Controller::sortScootersByID() {
    vector<Scooter> scooters = repository->getAllScootersFromRepo();

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
    return scooters;
}

void controller::Controller::save() {
    repository->saveToFile("data.txt");
}

void controller::Controller::load() {
    repository->loadFromFile("data.txt");
}
