//
// Created by naomi on 5/13/2023.
//
#include "CrudRepository.h"

repository::CrudRepository &repository::CrudRepository::operator=(const repository::CrudRepository &other){
    if (this == &other)
    {
        return *this;
    }

    // Perform deep copy of the Scooters vector
    Scooters = other.Scooters;

    return *this;
}
