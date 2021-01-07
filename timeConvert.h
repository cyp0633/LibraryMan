#ifndef _TIMECONVERT_H_INCLUDED
#define _TIMECONVERT_H_INCLUDED
#include<cstdio>
#include<iostream>
#include <ctime>
using namespace std;

struct Time
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
};
Time stampConvert(const time_t &timestamp)
{

}
#endif