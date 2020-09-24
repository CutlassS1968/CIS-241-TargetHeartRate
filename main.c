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

#define AGE_MAX 122 // Oldest person to ever live
#define AGE_MIN -1

void getData(int *, int *, int *);
int calcAge(int, int, int, int, int, int);
int concat(int, int, int);
int calcMax(int);
float calcUp(int);
float calcLo(int);
int dateValid(int, int, int, int);
int isLeap(int);

int main(int argc, const char * argv[]) {

    int bDay;    // User's birth day
    int bMonth;  // User's birth month
    int bYear;   // User's birth year

    int age;                // User's age
    int maxHeartRate;       // User's max heart rate
    float upperHeartRate;   // User's upper target heart rate
    float lowerHeartRate;   // User's lower target heart rate

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int cDay = tm.tm_mday;          // Current day
    int cMonth = tm.tm_mon + 1;		// Current month
    int cYear = tm.tm_year + 1900;	// Current year

    do {
        getData(&bDay, &bMonth, &bYear);
        age = calcAge(bDay, bMonth, bYear, cDay, cMonth, cYear);
    } while ((!dateValid(bDay, bMonth, bYear, cYear) ? puts("ERROR: That date isn't possible! try again") : printf("")) ||
             (age > AGE_MAX ? puts("ERROR: No one can be that old! try again") : printf("")) ||
             (age < AGE_MIN ? puts("ERROR: You haven't been born yet! try again") : printf("")));

    maxHeartRate = calcMax(age);
    upperHeartRate = calcUp(age);
    lowerHeartRate = calcLo(age);

    puts("\n-------------------------------------------------");
    printf("  Age: %i\n  Max Heart Rate: %ibpm\n  Target Heart Rate Range: "
           "%.1fbpm - %.1fbpm\n", age, maxHeartRate, lowerHeartRate, upperHeartRate);
    puts("-------------------------------------------------\n");

    return 0;
}

// Get input data from the user
void getData(int * day, int * month, int * year) {
    printf("\nEnter your birthday (MM/DD/YYYY): ");
    if (scanf("%d/%d/%d", month, day, year) != 3) {
        puts("ERROR: Invalid input type");
        exit(EXIT_FAILURE);
    }
}

// Calculates the difference between the concatenated birth date
// and the concatenated current date resulting in the age of the user
int calcAge(int bDay, int bMonth, int bYear, int cDay, int cMonth, int cYear) {
    int bDate = concat(bDay, bMonth, bYear);
    int cDate = concat(cDay, cMonth, cYear);

    return (cDate - bDate) / 10000;
}

// concatenate the year, month, day into one integer
int concat(int day, int month, int year) {
    char string1[3];
    char string2[3];
    char string3[5];
    char result[9];

    sprintf(string1, "%02d", day);
    sprintf(string2, "%02d", month);
    sprintf(string3, "%d", year);

    strcpy(result, string3);
    strcat(result, string2);
    strcat(result, string1);

    return atoi(result);
}

// Checks if the date is valid
int dateValid(int day, int month, int year, int cYear) {
    if (year < 1800 || year > cYear) {
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
            if (day > 29) {
                return 0;
            }
        } else if (day > 28) {
            return 0;
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

// Checks if the year is a leap year
int isLeap(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            }
        } else {
            return 1;
        }
    }
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