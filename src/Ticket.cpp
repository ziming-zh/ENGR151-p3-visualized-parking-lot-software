#include "Ticket.h"

Ticket::Ticket(unsigned int _vehicleType, float _arrivalTime, float _departureTime) : 
    vehicleType(_vehicleType), arrivalTime(_arrivalTime), departureTime(_departureTime) {}

ArrivalTicket::ArrivalTicket(unsigned int _vehicleType, float _arrivalTime, float _departureTime, std::string _guide) : 
    Ticket(_vehicleType, _arrivalTime, _departureTime), guide(_guide) {}

// Print arrival ticket to cout.
void ArrivalTicket::printTicket() const {
    std::cout << "Arrival Ticket" << std::endl;
    std::cout << "Arrival Time: " << arrivalTime << "s" << std::endl;
    std::cout << "Vehicle Type: " << vehicleType << std::endl;
    std::cout << "Where to find an empty slot: \n" << guide << std::endl;
}

DepartureTicket::DepartureTicket(unsigned int _vehicleType, float _arrivalTime, float _departureTime) : 
    Ticket(_vehicleType, _arrivalTime, _departureTime) {
    totalTime = departureTime - arrivalTime;
    totalPrice = calcTotalPrice();
}

// Set the unit prices for different types of vehicles.
std::vector<float> DepartureTicket::unitPrices = {0.01, 0.01, 0.01, 0.01, 0.01};

// Return the total price.
float DepartureTicket::getTotalPrice() const {
    return totalPrice;
}

// Calculate the total price.
float DepartureTicket::calcTotalPrice() const {
    return unitPrices[vehicleType] * totalTime;
}

// Print departure ticket to cout.
void DepartureTicket::printTicket() const {
    std::cout << "Departure Ticket" << std::endl;
    std::cout << "Total Time: " << totalTime << "s" << std::endl;
    std::cout << "Vehicle Type: " << vehicleType << std::endl;
    std::cout << "Total Price: " << totalPrice << "$" << std::endl;
}