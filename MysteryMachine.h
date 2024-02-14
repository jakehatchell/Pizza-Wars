#ifndef MYSTERYMACHINE_H
#define MYSTERYMACHINE_H
#include "Date.h"
#include <string>
// returns the string of the day of the week
// for the given date Object.
class MysteryMachine
{
    public:
        static string getDayOfWeek(Date inDate);
};
#endif