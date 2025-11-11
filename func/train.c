#include <stdio.h>

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

int loadTrains(struct Train trains[])
{
    FILE *fp = fopen("data/trains.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening trains.txt\n");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%d %49s %49s %49s %d",
                  &trains[count].number,
                  trains[count].name,
                  trains[count].starting,
                  trains[count].destination,
                  &trains[count].seats) == 5)
    {
        count++;
    }
    fclose(fp);
    return count;
}

void showTrains(struct Train trains[], int n)
{
    printf("\n%-10s %-20s %-15s %-15s %-10s\n",
           "Train No", "Train Name", "starting", "Destination", "Available Seats");

    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-10d %-20s %-15s %-15s %-10d\n",
               trains[i].number, trains[i].name, trains[i].starting,
               trains[i].destination, trains[i].seats);
    }
}

// ================ TICKET SYSTEM =================

void bookTicket(struct Train trains[], int n)
{
    FILE *fp = fopen("data/tickets.txt", "ab");
    struct Ticket t;
    int trainNum, found = 0;

    if (fp == NULL)
    {
        printf("Error opening tickets.txt!\n");
        return;
    }

    printf("\nEnter Train Number: ");
    scanf("%d", &trainNum);
    getchar();

    for (int i = 0; i < n; i++)
    {
        if (trains[i].number == trainNum)
        {
            found = 1;
            if (trains[i].seats > 0)
            {
                printf("Enter Passenger Name: ");
                fgets(t.passengerName, sizeof(t.passengerName), stdin);
                t.passengerName[strcspn(t.passengerName, "\n")] = '\0';
                printf("Enter Contact No: ");
                scanf("%d", &t.mobile);
                getchar();

                t.trainNumber = trainNum;
                t.seatNumber = trains[i].seats;
                trains[i].seats--;

                fwrite(&t, sizeof(struct Ticket), 1, fp);

                printf("\nTicket booked successfully!\n");
                printf("Train: %s\nSeat No: %d\n", trains[i].name, t.seatNumber);
            }
            else
            {
                printf("No seats available in this train.\n");
            }
            break;
        }
    }

    if (!found)
        printf("Train not found!\n");

    fclose(fp);
}

void cancelTicket(struct Train trains[], int n, char loggedInUser[])
{
    FILE *fp, *temp;
    struct Ticket t;
    char name[50];
    int found = 0;

    printf("Enter Passenger Name to cancel ticket: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    fp = fopen("data/tickets.txt", "rb");
    temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&t, sizeof(struct Ticket), 1, fp) == 1)
    {
        if (strcmp(name, t.passengerName) != 0)
        {
            fwrite(&t, sizeof(struct Ticket), 1, temp);
        }
        else
        {
            found = 1;
            for (int i = 0; i < n; i++)
            {
                if (trains[i].number == t.trainNumber)
                {
                    trains[i].seats++;
                    break;
                }
            }
        }
    }

    fclose(fp);
    fclose(temp);
    remove("data/tickets.txt");
    rename("temp.txt", "data/tickets.txt");

    if (found)
        printf("Ticket cancelled successfully by %s!\n", loggedInUser);
    else
        printf("Ticket not found!\n");
}

void viewBookedTickets()
{
    FILE *fp = fopen("data/tickets.txt", "rb");
    struct Ticket t;

    if (fp == NULL)
    {
        printf("No tickets booked yet.\n");
        return;
    }

    printf("\n%-20s %-10s %-10s %-10s\n",
           "Passenger Name", "Contact Number", "Train No", "Seat No");
           
    printf("\n");

    while (fread(&t, sizeof(struct Ticket), 1, fp) == 1)
    {
        printf("%-20s %-10d %-10d %-10d\n",
               t.passengerName, t.mobile, t.trainNumber, t.seatNumber);
    }

    fclose(fp);
}