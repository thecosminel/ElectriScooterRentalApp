//
// Created by george on 5/12/2023.
//

#include "Scooter.h"
#include "Utils/AuxiliaryFunctions.h"
using std::string, std::cout, std::endl, std::string, std::cin;

void printIndexing(int index)
{
    if (index < 10)
    {
        cout << 0 << index << "-> ";
    }
    else
    {
        cout << index << "-> ";
    }
}

void pressEnterToContinue()
{
    std::cout << std::endl;
#ifdef _WIN64
    system("pause");
#else
    system("read -p 'Press any key to continue...' -n1 -s");
#endif
}

void printScooterContainer(std::vector<Scooter> scooterContainer)
{
    cout << endl;

    for (int i = 0; i < scooterContainer.size(); i++)
    {
        Scooter scooter = scooterContainer[i];
        printIndexing(i+1);
        cout << "ID: " << scooter.getIdentifier() << "  ";
        cout << "Model: " << scooter.getModel();
        insertBlankSpaces(scooter.getModel());
        cout << "Commissioning date: " << scooter.getDate();
        insertBlankSpaces(scooter.getDate());
        cout << "Km: ";
        printDoubleNumber(scooter.getKilometers());
        cout << "Location: " << scooter.getLocation();
        insertBlankSpaces(scooter.getLocation());
        cout << "Status: " << getScooterStatusString(scooter.getStatus());
        cout << endl;
    }
    cout << endl;
}

void insertBlankSpaces(const string& text)
{
    unsigned long long length = text.size();
    for (unsigned long long  i = length; i < 12; ++i)
    {
        cout << ' ';
    }
}

void printDoubleNumber(double number)
{
    int intValueOfNumber;
    intValueOfNumber = static_cast<int>(number);
    if (intValueOfNumber < 100000)
        cout << ' ';
    if (intValueOfNumber < 10000)
        cout << ' ';
    if (intValueOfNumber < 1000)
        cout << ' ';
    if (intValueOfNumber < 100)
        cout << ' ';
    if (intValueOfNumber < 10)
        cout << ' ';
    cout << intValueOfNumber;
    cout << '.';
    if (static_cast<int>(number * 100) % 100 < 10)
        cout << 0;
    cout << static_cast<int>(number * 100) % 100;
    cout << " ";
}

bool checkIdFormat(const string& ID)
{
    if (ID.length() != 3) {
        return false;
    }

    for (char c : ID) { // NOLINT
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}


bool checkDateFormat(const string& date)
{
    if (date.length() != 10)
        return false;
    // Check format 'dd.mm.yyyy'
    if (date.at(2) != '.' || date.at(5) != '.' )
        return false;
    // Get day, month, year
    int day, month, year;
    sscanf(date.c_str() ,"%d.%d.%d", &day, &month, &year); //NOLINT
    if (day < 1 || day > 31)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (year < 1000 || year > 9999)
        return false;
    // Check day exceptions
    if (month == 2 && day > 29)
        return false;
    if (month == 2 && day == 29 && (year % 4 != 0))
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
        return false;
    return true;
}

string enterModel()
{
    string model;
    cout << endl;
    cout << "Enter scooter model: ";
    cin >> model;
    return model;
}

string enterManufacturingDate()
{
    string manufacturingDate;
    cout << endl;
    cout << "Enter manufacturing date: ";
    cin >> manufacturingDate;
    while (!checkDateFormat(manufacturingDate))
    {
        cout << endl << "Please enter a valid manufacturing date:";
        cin >> manufacturingDate;
    }
    return manufacturingDate;
}

double enterKm()
{
    double km;
    cout << endl;
    cout << "Enter km: ";
    cin >> km;
    return km;
}

string enterLocation()
{
    string location;
    cout << endl;
    cout << "Enter location: ";
    cin >> location;
    return location;
}

ScooterStatus enterStatus()
{
    cout << endl;
    cout << "Enter status (PARKED, RESERVED, IN_USE, MAINTENANCE, OUT_OF_SERVICE, UNKNOWN): ";
    string statusAsString;
    cin >> statusAsString;
    auto statusVector = getStatusVector();
    for (int i = 0; i < statusVector.size(); i++)
    {
        if(statusAsString == getScooterStatusString(getScooterStatusWithIndex(i)))
            return getScooterStatusWithIndex(i);
    }
    cout << endl << "Status unknown";
    return UNKNOWN;
}

string enterID()
{
    string ID;
    cout << endl;
    cout << "Enter an id: ";
    cin >> ID;
    while (!checkIdFormat(ID))
    {
        cout << endl << "Please enter a valid ID format (ex. xyz): ";
        cin >> ID;
    }
    return ID;
}

bool compareManufacturingDates(const string& manufacturingDate, const string& scooterManufacturingDate) {
    struct currentManufacturingDate {
        int day, month, year;
    };

    struct S_manufacturingDate {
        string S_day, S_month, S_year;
    };

    S_manufacturingDate s_checkDate, s_scooterDate;
    s_checkDate.S_day = manufacturingDate.substr(0, 2);
    s_checkDate.S_month = manufacturingDate.substr(3, 2);
    s_checkDate.S_year = manufacturingDate.substr(6,4);
    s_scooterDate.S_day = scooterManufacturingDate.substr(0, 2);
    s_scooterDate.S_month = scooterManufacturingDate.substr(3, 2);
    s_scooterDate.S_year = scooterManufacturingDate.substr(6,4);

    currentManufacturingDate checkDate{}, scooterDate{};
    checkDate.day = stoi(s_checkDate.S_day);
    checkDate.month = stoi(s_checkDate.S_month);
    checkDate.year = stoi(s_checkDate.S_year);
    scooterDate.day = stoi(s_scooterDate.S_day);
    scooterDate.month = stoi(s_scooterDate.S_month);
    scooterDate.year = stoi(s_scooterDate.S_year);

    if(checkDate.year > scooterDate.year) { //NOLINT
        return false;
    }
    else if (checkDate.year == scooterDate.year and checkDate.month > scooterDate.month) {
        return false;
    }
    else if (checkDate.year == scooterDate.year and checkDate.month == scooterDate.month and checkDate.day >
    scooterDate.day) {
        return false;
    }
    return true;
}

string getScooterStatusString(ScooterStatus status)
{
    switch (status) {
        case PARKED:
            return "PARKED";
        case RESERVED:
            return "RESERVED";
        case IN_USE:
            return "IN_USE";
        case MAINTENANCE:
            return "MAINTENANCE";
        case OUT_OF_SERVICE:
            return "OUT_OF_SERVICE";
        default:
            return "UNKNOWN";
    }
}

ScooterStatus getScooterStatusWithIndex(int index)
{
    switch (index) {
        case 1:
            return PARKED;
        case 2:
            return RESERVED;
        case 3:
            return IN_USE;
        case 4:
            return MAINTENANCE;
        case 5:
            return OUT_OF_SERVICE;
        default:
            return UNKNOWN;
    }
}

vector<ScooterStatus> getStatusVector()
{
    std::vector<ScooterStatus> ScooterStatusVector = { PARKED, RESERVED, IN_USE,
                                                       MAINTENANCE, OUT_OF_SERVICE, UNKNOWN
    };
    return ScooterStatusVector;
}