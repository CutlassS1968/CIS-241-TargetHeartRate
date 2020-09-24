//
//  CIS 241 02, Professor Vijay Bhuse
//   Target-Heart-Rate Calculator
//
//  Created by Evan Johns on 9/13/20
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AGE_MAX 122
#define AGE_MIN -1

void getData(void);
int calcAge(int, int, int);
int concat(int, int, int);
int calcMax(int);
float calcUp(int);
float calcLo(int);
int dateValid(void);
int isLeap(int);

int day;    // User's birth day
int month;  // User's birth month
int year;   // User's birth year

int currentDay;
int currentMonth;
int currentYear;

int main(int argc, const char * argv[]) {

    int age;                // User's age
    int maxHeartRate;       // User's max heart rate
    float upperHeartRate;   // User's upper target heart rate
    float lowerHeartRate;   // User's lower target heart rate

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    currentDay = tm.tm_mday;            // tm day is current day
    currentMonth = tm.tm_mon + 1;		// tm_mon is months from 0-11
    currentYear = tm.tm_year + 1900;	// tm_year is years since 1900

//    //TODO: Combine these statements into one loop
//    do {
//        getData();
//    } while (!dateValid());
//
//    age = calcAge(day, month, year);
//
//    // Error checking user's age
//    while (age > AGE_MAX || age < AGE_MIN) {
//        puts("ERROR: Invalid birth date! Try again");
//        getData();
//        age = calcAge(day, month, year);
//    }

    maxHeartRate = calcMax(age);
    upperHeartRate = calcUp(age);
    lowerHeartRate = calcLo(age);

    puts("\n-------------------------------------------------");
    printf("  Age: %i\n  Max Heart Rate: %ibpm\n  Target Heart Rate Range: "
           "%.1fbpm - %.1fbpm\n", age, maxHeartRate, lowerHeartRate, upperHeartRate);
    puts("-------------------------------------------------\n");

    return 0;
}

// Calculate the user's maximum heart rate
int calcMax(int age) {
    return 220 - age;
}

// Calculate the user's upper target heart rate
float calcUp(int age) {
    return (float) (0.85 * calcMax(age));
}

// Calculate the user's lower target heart rate
float calcLo(int age) {
    return (float) (0.5 * calcMax(age));
}

// Get input data from the user
void getData() {
    printf("Enter your birthday (MM/DD/YYYY): ");
     if (scanf("%d/%d/%d", &month, &day, &year) != 3) {
         puts("ERROR: Invalid input");
         exit(EXIT_FAILURE);
     }
}

// concatenate the year, month, day into one integer
int concat(int d, int m, int y) {
    char string1[3];
    char string2[3];
    char string3[5];
    char result[9];

    sprintf(string1, "%02d", d);
    sprintf(string2, "%02d", m);
    sprintf(string3, "%d", y);

    strcpy(result, string3);
    strcat(result, string2);
    strcat(result, string1);

    return atoi(result);
}

// Calculates the difference between the concatenated birth date
// and the concatenated current date resulting in the age of the user
int calcAge(int birthDay, int birthMonth, int birthYear) {
    int birthDate = concat(birthDay, birthMonth, birthYear);
    int currentDate = concat(currentDay, currentMonth, currentYear);

    return (currentDate - birthDate) / 10000;
}

// Checks if the year is a leap year
int isLeap(int y) {
    if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

// Checks if the date is valid
int dateValid() {
    if (year < 1800 || year > currentYear) {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1 || day > 31) {
        return 0;
    }

    // Check day is in month
    if (month == 2) {
        if (isLeap(year)) {
            if (day <= 29) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    // Check months with 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day <= 30) {
            return 1;
        } else {
            return 0;
        }
    }
    return 1;
}