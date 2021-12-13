//
// Created by Ziming on 2021/12/5.
// Changed by Ming on purpose on 2021/12/7 =)
//
#include "Ticket.h"
#include <time.h>
void Ticket::putin(unsigned long long int in){timein=in;}
void Ticket::putout(unsigned long long int out){timeout=out;}
void Ticket::calprice(){price=unitprice*(timeout-timein);}
double Ticket::getprice(){return price;}