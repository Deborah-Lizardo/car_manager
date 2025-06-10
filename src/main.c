#include <stdio.h>
#include <stdlib.h>
#include "../include/car.h"
#include "../include/year_list.h"

int main() {
// Example cars|
    Car car1 = {"Honda", "HRV EX", 2022, 15000, 80000.00};
    Car car2 = {"Renault", "Sandero Stepway", 2023, 20000, 60000.00};
    Car car3 = {"Toyota", "Yaris XLS", 2020, 60000, 80000.00};
    Car car4 = {"Ford", "Focus SE", 2020, 10000, 120000.00};

    // Create an empty year list (initially NULL)
    YearNode* yearList = NULL;

    // Insert cars into the year list
    yearList = insertYear(yearList, car1.year, &car1);
    yearList = insertYear(yearList, car2.year, &car2);
    yearList = insertYear(yearList, car3.year, &car3);
    yearList = insertYear(yearList, car4.year, &car4);

    // Display all cars from years >= 2020
    displayCarsFromYear(yearList, 2020);

    // Display all cars from years >= 2023
    displayCarsFromYear(yearList, 2023);

    // Free the allocated memory
    freeYearList(yearList);

    return 0;
}
