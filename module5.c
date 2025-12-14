#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct
{
    char passengerName[50];
    char source[30];
    char destination[30];
    int distance;
    float fare;
    int seatNo;
} Ticket;

int seatCounter = 1;

const float farePerKm = 1.5;

// Module 1: Passenger Entry Form
void getPassengerDetails(Ticket *t)
{
    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", t->passengerName);

    printf("Enter Source Location: ");
    scanf("%s",t->source);

    printf("Enter Destination Location: ");
    scanf("%s",t->destination);

    printf("Enter Distance (in km): ");
    scanf("%d",&t->distance);
}

// Module 2: Fare Calculator
void calculateFare(Ticket *t)
{
    t->fare = t->distance * farePerKm;
}

// Module 3: Seat Number Generator
void generateSeatNumber(Ticket *t)
{
    t->seatNo = seatCounter++;
}

// Module 4: Ticket Formatter
void printTicket(const Ticket *t)
{
    printf("\n========== BUS TICKET ==========\n");
    printf("Passenger Name : %s\n", t->passengerName);
    printf("From           : %s\n", t->source);
    printf("To             : %s\n", t->destination);
    printf("Distance       : %d km\n", t->distance);
    printf("Seat Number    : %d\n", t->seatNo);
    printf("Fare           : ₹%.2f\n", t->fare);
    printf("================================\n");
}

// Module 5: File Saver
void saveTicketToFile(const Ticket *t)
{
    FILE *file = fopen("tickets.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file to save ticket.\n");
        return;
    }
    fprintf(file, "Passenger: %s | From: %s | To: %s | Distance: %d | Seat: %d | Fare: ₹%.2f\n",
            t->passengerName, t->source, t->destination, t->distance, t->seatNo, t->fare);
    fclose(file);
}

void viewTickets()
{
    FILE *file = fopen("tickets.txt", "r");
    if (file == NULL)
    {
        printf("No tickets found (file cannot be opened).\n");
        return;
    }

    printf("\n===== ALL BOOKED TICKETS =====\n");
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }
    printf("===== END OF LIST =====\n\n");

    fclose(file);
}

int main()
{
    Ticket t;
    char choice;

    do
    {
        getPassengerDetails(&t);
        calculateFare(&t);
        generateSeatNumber(&t);
        printTicket(&t);
        saveTicketToFile(&t);
        viewTickets();

        printf("\nDo you want to book another ticket? (y/n): ");
        scanf("%c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("Thank you for using the Bus Ticket Generator!\n");

    return 0;
}