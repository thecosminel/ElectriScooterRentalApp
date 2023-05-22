//
// Created by naomi on 5/13/2023.
//
#pragma once

#include "CrudRepository.h"

/// unit test for add method
/// \param repository
void testAddScooter(repository::Repository& repository);

/// unit test for remove method
/// \param repository
void testRemoveScooter(repository::Repository& repository);

/// unit test for update method
/// \param repository
void testUpdateScooter(repository::Repository& repository);

void testSaveToFile(repository::Repository& repository, const std::string& fileName);

void testAllRepo();

