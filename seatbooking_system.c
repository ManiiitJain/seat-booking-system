#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SEATS = 20;
int NAME = 100;
int GENDER = 10;
char seats[20][100];
char genders[20][10];

void saveToFile() {
  FILE *f = fopen("seats.dat", "w");
  if (!f)
    return;
  for (int i = 0; i < SEATS; i++) {
    fprintf(f, "%s\n%s\n", seats[i], genders[i]);
  }
  fclose(f);
}

void loadFromFile() {
  FILE *f = fopen("seats.dat", "r");
  if (!f)
    return;
  for (int i = 0; i < SEATS; i++) {
    fscanf(f, " %[^\n]", seats[i]);
    fscanf(f, " %[^\n]", genders[i]);
  }
  fclose(f);
}

void initializeSeats() {
  for (int i = 0; i < SEATS; i++) {
    strcpy(seats[i], "Empty");
    strcpy(genders[i], "N/A");
  }
  loadFromFile(); // Load saved seat data if available
}

void displayAvailableSeats() {
  printf("\nAvailable Seats:\n");
  for (int i = 0; i < SEATS; i++) {
    if (strcmp(seats[i], "Empty") == 0) {
      printf("Seat %d: Available\n", i + 1);
    } else {
      printf("Seat %d: Booked\n", i + 1);
    }
  }
}

void bookSeat() {
  int seatNumber;
  char name[100];
  char gender[10];

  printf("Enter the seat number to book (1-%d): ", SEATS);
  scanf("%d", &seatNumber);

  if (seatNumber < 1 || seatNumber > SEATS) {
    printf("Invalid seat number! Please enter a number between 1 and %d.\n",
           SEATS);
    return;
  }

  if (strcmp(seats[seatNumber - 1], "Empty") != 0) {
    printf("Seat %d is already booked.\n", seatNumber);
    return;
  }

  printf("Enter passenger's name: ");
  scanf(" %[^\n]", name);
  printf("Enter passenger's gender (Male/Female): ");
  scanf(" %[^\n]", gender);

  strcpy(seats[seatNumber - 1], name);
  strcpy(genders[seatNumber - 1], gender);
  saveToFile(); // Save the new state

  printf("Seat %d successfully booked for %s.\n", seatNumber, name);
}

void cancelBooking() {
  int seatNumber;

  printf("Enter the seat number to cancel booking (1-%d): ", SEATS);
  scanf("%d", &seatNumber);

  if (seatNumber < 1 || seatNumber > SEATS) {
    printf("Invalid seat number! Please enter a number between 1 and %d.\n",
           SEATS);
    return;
  }

  if (strcmp(seats[seatNumber - 1], "Empty") == 0) {
    printf("Seat %d is already empty.\n", seatNumber);
    return;
  }

  printf("Booking for seat %d (Passenger: %s) has been canceled.\n", seatNumber,
         seats[seatNumber - 1]);

  strcpy(seats[seatNumber - 1], "Empty");
  strcpy(genders[seatNumber - 1], "N/A");
  saveToFile(); // Save the new state
}

void displayPassengerList() {
  printf("\nPassenger List:\n");
  printf("| Seat# | Name            | Gender |\n");

  for (int i = 0; i < SEATS; i++) {
    if (strcmp(seats[i], "Empty") != 0) {
      printf("| %-5d | %-15s | %-6s |\n", i + 1, seats[i], genders[i]);
    }
  }
}

int main() {
  int choice;

  initializeSeats();

  do {
    printf("\n=== Bus Booking System ===\n");
    printf("1. Display Available Seats\n");
    printf("2. Book a Seat\n");
    printf("3. Cancel a Booking\n");
    printf("4. Display Passenger List\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      displayAvailableSeats();
      break;
    case 2:
      bookSeat();
      break;
    case 3:
      cancelBooking();
      break;
    case 4:
      displayPassengerList();
      break;
    case 5:
      printf("Exiting the system. Goodbye!\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 5);

  return 0;
}