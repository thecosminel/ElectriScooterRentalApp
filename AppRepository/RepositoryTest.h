//
// Created by naomi on 5/13/2023.
//
#pragma once

#include "CrudRepository.h"
#include "CsvFileRepository.h"
#include "InMemoryRepository.h"

/// unit test for add method
/// \param repository
void testAddScooterCsv(repository::CsvFileRepository& repository);

/// unit test for remove method
/// \param repository
void testRemoveScooterCsv(repository::CsvFileRepository& repository);

/// unit test for update method
/// \param repository
void testUpdateScooterCsv(repository::CsvFileRepository& repository);

void testSaveToFileCsv(repository::CsvFileRepository& repository, const std::string& fileName);

void testAddScooterInMemory(repository::InMemoryRepository& repository);

void testDeleteScooterInMemory(repository::InMemoryRepository& repository);

void testUpdateScooterInMemory(repository::InMemoryRepository& repository);

void testSaveToFileInMemory(repository::InMemoryRepository& repository, const std::string& fileName);

void testAllRepo();

