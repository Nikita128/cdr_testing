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

    int i = 0;

    boost::asio::steady_timer tm(ioc);
    tm.expires_after(dur);
    tm.async_wait(boost::bind(print, boost::asio::placeholders::error, &tm, &i));

    std::future<void> f = std::async(std::launch::async, [&]()
    {
        while (true)
        {
            cdr record;
            pqxx::work w(c);
            w.exec("insert into cdr values(" + record.prep_str_for_insert() +")");
            w.commit();
            ++i;
        }
    });


    ioc.run();
    f.wait();

    return EXIT_SUCCESS;
}
