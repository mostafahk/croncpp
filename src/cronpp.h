#ifndef _CRON_PP_
#define _CRON_PP_

#include "croncpp/croncpp.h"
#include <time.h>

class cronpp
{
private:
        int comparetime(time_t time1, time_t time2);
        bool made;

public:
    cron::cronexpr expr;
    tm next_run;

    // if true: cron is in runtime
    bool triggered;

    cronpp(/* args */);
    ~cronpp();
    bool make(String expresion);
    bool make(const char *expresion);
    bool check(tm *now);
    bool check(time_t now);
};

#endif
