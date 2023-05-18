//
// Created by Robert on 13/05/2023.
//
#pragma once
#include "../Domain/Scooter.h"

#include <vector>
#include <iostream>

using namespace scooter;
using std::vector, std::string;

// AppUI

string enterID();
string enterModel();
string enterManufacturingDate();
double enterKm();
string enterLocation();
ScooterStatus enterStatus();
bool compareManufacturingDates(const string& manufacturingDate, const string& scooterManufacturingDate);

bool checkIdFormat(const string& ID);
bool checkDateFormat(const string& date);

void pressEnterToContinue();
void printIndexing(int index);
void insertBlankSpaces(const string& text);
void printDoubleNumber(double number);
void printScooterContainer(std::vector<Scooter> scooterContainer);


// Repo
string getScooterStatusString(ScooterStatus status);
ScooterStatus getScooterStatusWithIndex(int index);
vector<ScooterStatus> getStatusVector();