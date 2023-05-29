#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstring>
#include "Domain/Scooter.h"
#include "Utils/AuxiliaryFunctions.h"
#include "CrudRepository.h"
#include "InMemoryRepository.h"

using namespace scooter;
using std::vector, std::shared_ptr, std::string, std::ifstream, std::endl, std::strcmp;

namespace repository
{

    class CsvFileRepository : public InMemoryRepository{

    public:
        ///default constructor
        CsvFileRepository() = default;
        CsvFileRepository(CsvFileRepository &repository) = default;
        CsvFileRepository& operator=(const CsvFileRepository& other);

        ///default destructor
        ~CsvFileRepository();


        /// method for saving to file
        /// \param fileName
        void saveToFile(const string &fileName = "data.csv");
    };
}