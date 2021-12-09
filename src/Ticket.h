//
// Created by Ziming on 2021/12/5.
// Changed by Ming on purpose on 2021/12/7 =)
//
#ifndef P3_TICKET_H
#define P3_TICKET_H


class Ticket {
public:
    Ticket();
    void calprice();
    double getprice();
    void putin(unsigned long long int in);
    void putout(unsigned long long int out);
    ~Ticket();
private:
    unsigned long long int timein,timeout;
    double unitprice,price;
};


#endif //P3_TICKET_H
