#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./func/login.h"
#include "./func/train.h"

#ifdef _WIN32
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() printf("\033[H\033[J")
#endif

int registerUser();
int loginUser();
void showTrains(struct Train trains[], int n);
void bookTicket(struct Train trains[], int n);
void cancelTicket(struct Train trains[], int n, char loggedInUser[]);
void viewBookedTickets();
int loadTrains(struct Train trains[]);

int main()
{
    struct Train trains[100];
    int trainCount = loadTrains(trains);
    if (trainCount == 0)
    {
        printf("No train data found!!\n");
        return 0;
    }

    int loggedIn = 0;
    char currentUser[50];

    int choice;
    while (1)
    {
        CLEAR_SCREEN();
        printf("\n*****Railway Ticket Booking System*****\n");
        if (!loggedIn)
        {
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            getchar();

            if (choice == 1)
                registerUser();
            else if (choice == 2)
                loggedIn = loginUser(currentUser);
            else if (choice == 3)
                exit(0);
            else
                printf("Invalid choice!\n");

            if (!loggedIn)
            {
                printf("\nPress Enter to continue...");
                getchar();
            }
        }
        else
        {
            // Once logged in
            CLEAR_SCREEN();
            printf("\nWelcome, %s\n", currentUser);
            printf("\n*****Main Menu*****\n");
            printf("1. View Available Trains\n");
            printf("2. Book Ticket\n");
            printf("3. Cancel Ticket\n");
            printf("4. View All Booked Tickets\n");
            printf("5. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                CLEAR_SCREEN();
                showTrains(trains, trainCount);
                break;
            case 2:
                CLEAR_SCREEN();
                showTrains(trains, trainCount);
                bookTicket(trains, trainCount);
                break;
            case 3:
                CLEAR_SCREEN();
                cancelTicket(trains, trainCount, currentUser);
                break;
            case 4:
                CLEAR_SCREEN();
                viewBookedTickets();
                break;
            case 5:
                loggedIn = 0;
                printf("Logged out successfully!\n");
                break;
            default:
                printf("Invalid choice!\n");
            }

            printf("\nPress Enter to continue...");
            getchar();
        }
    }
    return 0;
}

// ================ TRAIN SYSTEM =================

// updated