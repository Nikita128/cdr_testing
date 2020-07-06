#ifndef CDR_H
#define CDR_H

#include <string>
#include <chrono>
#include <iostream>
#include <ctime>
#include <iomanip>

std::string quote(const std::string& str)
{
    return "\'" + str + "\'";
}

class cdr
{
public:

    cdr() :
        int_param1(1), int_param2(2), int_param3(3), int_param4(4), int_param5(5), int_param6(6), int_param7(7), int_param8(8), int_param9(9), int_param10(0),
        str_param1("1"), str_param2("2"), str_param3("3"), str_param4("4"), str_param5("5"), str_param6("6"), str_param7("7"), str_param8("8"), str_param9 ("9"), str_param10("0"),
        call_date(std::chrono::system_clock::now())
    {}

    std::string prep_str_for_insert()
    {
        const auto tp = std::chrono::system_clock::to_time_t(call_date);
        std::stringstream date;
        date << std::put_time(std::gmtime(&tp), "%F %T");

        return  "default," + std::to_string(int_param1) + "," + std::to_string(int_param2) + "," + std::to_string(int_param3) + "," + std::to_string(int_param4)
                + "," + std::to_string(int_param5) + "," + std::to_string(int_param6) + "," + std::to_string(int_param7) + "," + std::to_string(int_param8)
                + "," + std::to_string(int_param9) + "," + std::to_string(int_param10)
                + "," + quote(str_param1) + "," + quote(str_param2) + "," + quote(str_param3) + "," + quote(str_param4) + "," + quote(str_param5)
                + "," + quote(str_param6) + "," + quote(str_param7) + "," + quote(str_param8) + "," + quote(str_param9) + "," + quote(str_param10)
                + "," + quote(date.str());
    }

private:
    int int_param1;
    int int_param2;
    int int_param3;
    int int_param4;
    int int_param5;
    int int_param6;
    int int_param7;
    int int_param8;
    int int_param9;
    int int_param10;

    std::string str_param1;
    std::string str_param2;
    std::string str_param3;
    std::string str_param4;
    std::string str_param5;
    std::string str_param6;
    std::string str_param7;
    std::string str_param8;
    std::string str_param9;
    std::string str_param10;

    std::chrono::system_clock::time_point call_date;
};

#endif // CDR_H
