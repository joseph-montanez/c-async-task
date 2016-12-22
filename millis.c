//
// Created by josephmontanez on 12/18/2016.
//

#include "millis.h"
#include <time.h>

clock_t millis_start_time;
clock_t millis_current_time;

unsigned long millis() {
    millis_current_time = clock();

    return (unsigned long) (millis_current_time - millis_start_time);

}
void millis_start() {
    if (millis_start_time == 0) {
        millis_start_time = clock();
    }

}