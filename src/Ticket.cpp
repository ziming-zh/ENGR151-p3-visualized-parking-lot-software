#include "Ticket.h"

// Print arrival ticket to standard output.
void ArrivalTicket::printTicket()  {
    // Convert row and col into string. +1 is because the row and col begins with 0.
    std::string r = std::to_string(row + 1), c = std::to_string(col + 1);

    std::string guide = "There is an empty slot in row: " + r + ", column: " + c + "\n"
            + "Please drive straight forward, and turn right at the " + r + "th crossing.\n"
            + "Then your slot will be the " + c + "th slot on your right hand side.";
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Arrival Ticket" << std::endl;
    std::cout << "Arrival Time: " << arrivalTime << "s" << std::endl;
    std::cout << "Vehicle Type: " << vehicleType << std::endl;
    std::cout << "Where to find an empty slot: \n" << guide << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}
int Ticket::get_type() const {
    return vehicleType;
}
float Ticket::get_arr() const {
    return arrivalTime;
}
float Ticket::get_dep() const {
    return departureTime;
}
int Ticket::get_col() const {
    return col;
}
int Ticket::get_row() const {
    return row;
}
void Ticket::set_row(int r){
    row=r;
}
void Ticket::set_col(int c){
    col=c;
}
void Ticket::set_arr(float arr){
    arrivalTime=arr;
}
void Ticket::set_dep(float dep){
    departureTime=dep;
}
void Ticket::set_type(float type){
    vehicleType=type;
}

// Set the unit prices for different types of vehicles.
std::vector<float> DepartureTicket::unitPrices = {0.01, 0.02, 0.03, 0.04, 0.05};

// Return the total price.
float DepartureTicket::getTotalPrice() const {
    return totalPrice;
}

// Calculate the total price.
float DepartureTicket::calcTotalPrice() const {
    return unitPrices[vehicleType] * totalTime;
}

// Print departure ticket to cout.
void DepartureTicket::printTicket()  {
    // The total time spent in the parking lot.
    totalTime = departureTime - arrivalTime;
    totalPrice = calcTotalPrice();

    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Departure Ticket" << std::endl;
    std::cout << "Total Time: " << totalTime << "s" << std::endl;
    std::cout << "Vehicle Type: " << vehicleType << std::endl;
    std::cout << "Total Price: " << totalPrice << "$" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}
