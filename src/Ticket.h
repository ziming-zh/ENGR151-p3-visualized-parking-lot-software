#ifndef P3_TICKET_H
#define P3_TICKET_H

#include <iostream>
#include <string>
#include <vector>

class Ticket {
public:
    Ticket(){}
    virtual ~Ticket() {};
    virtual void printTicket()  = 0;
    float get_arr() const ;
    float get_dep() const ;
    int get_row() const ;
    int get_col() const ;
    int get_type() const ;
    void set_row(int r);
    void set_col(int c);
    void set_arr(float arr);
    void set_dep(float dep);
    void set_type(float type);
protected:
    unsigned int vehicleType;
    float arrivalTime, departureTime;
    int row, col;

private:
};

class ArrivalTicket : public Ticket {
public:
    ArrivalTicket(){}
    ~ArrivalTicket() { }
    void printTicket();

};

class DepartureTicket : public Ticket {
public:
    DepartureTicket(){}
    ~DepartureTicket() {}
    void printTicket();
    float getTotalPrice() const;

private:
    float calcTotalPrice() const;
    static std::vector<float> unitPrices;
    float totalTime; // Total time spent in the parking lot.
    float totalPrice;
};

#endif
