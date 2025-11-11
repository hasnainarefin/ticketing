#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>
#include <string.h>

// ================= STRUCTURES =================

struct Train
{
    int number;
    char name[50];
    char starting[50];
    char destination[50];
    int seats;
};

struct Ticket
{
    int trainNumber;
    char passengerName[50];
    int mobile;
    int seatNumber;
};

// ================= FUNCTION DECLARATIONS =================

int loadTrains(struct Train trains[]);
void showTrains(struct Train trains[], int n);

void bookTicket(struct Train trains[], int n);
void cancelTicket(struct Train trains[], int n, char loggedInUser[]);
void viewBookedTickets();

#endif
