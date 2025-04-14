#include<iostream>
using namespace std;


class Time
{
    private:
        friend ostream& operator <<(ostream&,const Time&);

        int hour;
        int minutes;
        int seconds;

    public:
        Time(int=0, int=30, int=0);
};
