#include <iostream>
#include <pqxx/pqxx>
#include <chrono>
#include <future>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "cdr.h"

constexpr auto dur = std::chrono::seconds(1);
int old_i = 0;

void print(const boost::system::error_code& ec, boost::asio::steady_timer* tm, int* num)
{
    if (ec)
    {
        return;
    }

    std::cerr << "Amount of transactions in 1 second: " << *num - old_i << ". Total: " << *num;
    old_i = *num;
    tm->expires_after(dur);
    tm->async_wait(boost::bind(print, boost::asio::placeholders::error, tm, num));
}

int main()
{
    boost::asio::io_context ioc;

    pqxx::connection c(
                "user=postgres password=12345 host=localhost port=5432 dbname=test");
    c.prepare("insert record",
              "insert into cdr values(default,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21);");

    int i = 0;

    boost::asio::steady_timer tm(ioc);
    tm.expires_after(dur);
    tm.async_wait(boost::bind(print, boost::asio::placeholders::error, &tm, &i));

    std::future<void> f = std::async(std::launch::async, [&]()
    {
        auto w = std::make_unique<pqxx::work>(c);
        while (true)
        {
            cdr record;

            w->exec_prepared("insert record", record.int_param1, record.int_param2, record.int_param3, record.int_param4, record.int_param5, record.int_param6,
                             record.int_param7, record.int_param8, record.int_param9, record.int_param10, record.str_param1, record.str_param2, record.str_param3,
                             record.str_param4, record.str_param5, record.str_param6, record.str_param7, record.str_param8, record.str_param9, record.str_param10,
                             record.get_formated_date());

            if (i % 10000 == 0)
            {
                w->commit();
                w = std::make_unique<pqxx::work>(c);
            }

            ++i;
        }
    });


    ioc.run();
    f.wait();

    return EXIT_SUCCESS;
}
