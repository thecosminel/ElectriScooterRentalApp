//
// Created by Robert on 13/05/2023.
//
#pragma once
#include "../Domain/Scooter.h"

#include <vector>
#include <iostream>
#include <cctype>
#include <memory>

using namespace scooter;
using std::vector, std::string, std::isalnum, std::shared_ptr, std::pair;

// AppUI
string enterUserName();
string enterID();
string enterModel();
pair <string, string> enterManufacturingDates();
string enterManufacturingDate();
pair<double, double> enterKmMultiple();
double enterKm();
string enterLocation();
ScooterStatus enterStatus();
bool choseIfSaveActions();

bool compareManufacturingDates(const string& manufacturingDate, const string& scooterManufacturingDate);

bool checkIdFormat(const string& ID);
bool checkDateFormat(const string& date);
bool checkAlphanumericString(const string& str);

void pressEnterToContinue();
void printIndexing(int index);
void insertBlankSpaces(const string& text);
void printDoubleNumber(double number);
void printScooterContainer(const shared_ptr<vector<Scooter>>& scooterContainer);


// Repo
string getScooterStatusString(ScooterStatus status);
ScooterStatus getScooterStatusWithIndex(int index);
vector<ScooterStatus> getStatusVector();