#pragma once
#include <string>
#include <vector>
using std::string, std::move;

enum ScooterStatus {
    PARKED,
    RESERVED,
    IN_USE,
    MAINTENANCE,
    OUT_OF_SERVICE,
    UNKNOWN
};

namespace scooter
{
    class Scooter {

    private:
        string identifier;
        string model;
        string manufacturingDate;
        double kilometers;
        string location;
        ScooterStatus status;
        string user;

    public:
        /// Default constructor
        Scooter();

        /// Constructor with parameters
        Scooter(string identifier, string model, string manufacturingDate, double kilometers, string location, ScooterStatus status);

        Scooter& operator=(const Scooter &scooter);

        /// Destructor
        ~Scooter()=default;

        /// Getter method for the scooter identifier
        [[nodiscard]] string getIdentifier() const;

        /// Getter method for the scooter model
        [[nodiscard]] string getModel() const;

        /// Getter method for the scooter's date of commissioning
        [[nodiscard]] string getDate() const;

        /// Getter method for the kilometers traveled by the scooter
        [[nodiscard]] double getKilometers() const;

        /// Getter method for the scooter's last known location
        [[nodiscard]] string getLocation() const;

        /// Getter method for the scooter's status
        [[nodiscard]] ScooterStatus getStatus() const;

        /// Getter method for the scooter's user
        [[nodiscard]] string getUser() const;

        /// Setter method for the scooter model
        void setModel(string model);

        /// Setter method for the scooter's date of commissioning
        void setDate(string manufacturingDate);

        /// Setter method for the kilometers traveled by the scooter
        void setKilometers(double kilometers);

        /// Setter method for the scooter's last known location
        void setLocation(string location);

        /// Setter method for the scooter's status
        void setStatus(ScooterStatus status);

        /// Setter method for the scooter's user
        void setUser(string scooterUser);

        /// Checks if two scooters have the same identifier
        /// \param scooter
        /// \return True if they do
        bool checkIfSameIdentifier(const Scooter& scooter);
    };
}
