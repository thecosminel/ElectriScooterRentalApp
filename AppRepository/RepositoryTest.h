//
// Created by naomi on 5/13/2023.
//
#pragma once

#include "InMemoryRepository.h"

/// unit test for add method
/// \param repository
void testAddScooter(repository::InMemoryRepository& repository);

/// unit test for remove method
/// \param repository
void testRemoveScooter(repository::InMemoryRepository& repository);

/// unit test for update method
/// \param repository
void testUpdateScooter(repository::InMemoryRepository& repository);

void testSaveToFile(repository::InMemoryRepository& repository, const std::string& fileName);

void testAllRepo();

