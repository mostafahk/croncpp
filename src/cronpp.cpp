#include "cronpp.h"

cronpp::cronpp(/* args */)
{
    memset((void *)&next_run, 0, sizeof(next_run));
    this->triggered = false;
    this->made = false;
}

cronpp::~cronpp()
{
}

void cronpp::make(String expresion)
{
    make(expresion.c_str());
}

void cronpp::make(const char *expresion)
{
    if (strlen(expresion) >= 5)
    {
        this->expr = cron::make_cron(expresion);
        this->made = true;
        this->next_run = {};
    }
}

int cronpp::comparetime(time_t time1, time_t time2)
{
    return difftime(time1, time2) > 0.0 ? 1 : -1;
}

bool cronpp::check(time_t now)
{
    tm val;
    return check(cron::utils::time_to_tm(&now, &val));
}

bool cronpp::check(tm *now)
{
    if (!made)
        return false;
    bool trigger_edge = false;
    if (now->tm_year < 110 && now->tm_year > 200)
        return false;
    if ((next_run.tm_hour < 110 && next_run.tm_year > 200) ||
        next_run.tm_year == -1)
        this->next_run = cron::cron_next(expr, *now);

    // check time reached next execute
    if (difftime(mktime(now), mktime(&next_run)) > 0.0)
    {
        if (!triggered)
        {
            this->next_run = cron::cron_next(expr, *now);
            this->triggered = true;
            trigger_edge = true;
        }
    }
    else
    {
        this->triggered = false;
    }

    return trigger_edge;
}
