#include <iostream>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"
 
boost::gregorian::date my_from_string (std::string x)
{
    long year = strtol(x.substr(0, 4).c_str(), nullptr, 10);
    long month = strtol(x.substr(5, 2).c_str(), nullptr, 10);
    long day = strtol(x.substr(8, 2).c_str(), nullptr, 10);
    boost::gregorian::date res(year, month, day);
    return res;
}
 
int main()
{
    std::string f, s;
    unsigned long long x = 0;
    std::cin >> f;
    boost::gregorian::date df = my_from_string(f);
    while (std::cin >> s) {
        boost::gregorian::date ds = my_from_string(s);
        if (df > ds) {
            boost::gregorian::date_period dp(ds, df);
            x += dp.length().days();
        } else if (df < ds) {
            boost::gregorian::date_period dp(df, ds);
            x += dp.length().days();
        }
        df = ds;        
    }
    std::cout << x;
}
