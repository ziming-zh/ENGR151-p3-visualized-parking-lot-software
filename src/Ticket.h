#ifndef __TICKET_H__
#define __TICKET_H__

#include <iostream>
#include <string>
#include <vector>

class Ticket {
public:
    Ticket(unsigned int _vehicleType, float _arrivalTime, float _departureTime);
    virtual ~Ticket() = 0;
    virtual void printTicket() const = 0;

protected:
    unsigned int vehicleType;
    float arrivalTime, departureTime;

private:
};

class ArrivalTicket : public Ticket {
public:
    ArrivalTicket(unsigned int _vehicleType, float _arrivalTime, float _departureTime, std::string _guide);
    ~ArrivalTicket() = default;
    void printTicket() const;

private:
    std::string guide; // Guide about how to find an empty slot.
};

class DepartureTicket : Ticket{
public:
    DepartureTicket(unsigned int _vehicleType, float _arrivalTime, float _departureTime);
    ~DepartureTicket() = default;
    void printTicket() const;
    float getTotalPrice() const;

private:
    float calcTotalPrice() const;
    static std::vector<float> unitPrices;
    float totalTime; // Total time spent in the parking lot.
    float totalPrice;
};

#endif