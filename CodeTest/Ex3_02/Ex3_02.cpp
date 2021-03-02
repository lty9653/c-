// Ex3_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>

#include "Customer.h"
#include "Checkout.h"

using namespace std;
using distribution = uniform_int_distribution<>;

void histogram(const vector<int>& v, int min)
{
    string bar(60, '*');
    for (size_t i{}; i < v.size(); ++i) {
        cout << setw(3) << i + min << " "
            << setw(4) << v[i] << " "
            << bar.substr(0, v[i])
            << (v[i] > static_cast<int>(bar.size()) ? "..." : "")
            << endl;
    }
}
int main()
{
    random_device random_n;
    int service_t_min{ 2 }, service_t_max{ 15 };
    distribution service_t_d{ service_t_min, service_t_max };

    int min_customers{ 15 }, max_customers{ 20 };
    distribution n_lst_customer_d{ min_customers, max_customers };

    int min_arr_interval{ 1 }, max_arr_interval{ 5 };
    distribution arrival_interval_d{ min_arr_interval, max_arr_interval };

    size_t n_checkouts{};
    cout << "Enter the number of checkouts in the supermarket: ";
    cin >> n_checkouts;
    if (!n_checkouts) {
        cout << "Number of checkouts be greater than 0, Setting to 1" << endl;
        n_checkouts = 1;
    }

    vector<Checkout> checkouts{ n_checkouts };
    vector<int> service_times(service_t_max - service_t_min+1);

    int count{ n_lst_customer_d(random_n) };
    cout << "Customers waiting at store opening: " << count << endl;
    int added{};
    int service_t{};
    while (added++ < count)
    {
        service_t = service_t_d(random_n);
        min_element(begin(checkouts), end(checkouts))->add(Customer(service_t));
        ++service_times[service_t - service_t_min];
    }

    size_t time{};
    const size_t total_time{ 600 };
    size_t longest_q{};
    int new_cust_interval{ arrival_interval_d(random_n) };
    while (time < total_time) {
        ++time;
        if (--new_cust_interval == 0) {
            service_t = service_t_d(random_n);
            min_element(begin(checkouts), end(checkouts))->add(Customer(service_t));
            service_times[service_t - service_t_min]++;

            for (auto & checkout : checkouts)
                longest_q = max(longest_q, checkout.qlength());
            new_cust_interval = arrival_interval_d(random_n);
        }

        for (auto& checkout : checkouts)
            checkout.time_increment();
    }

    cout << "Maxium queue length = " << longest_q << endl;
    cout << "Histogram of service times:" << endl;
    histogram(service_times, service_t_min);

    cout << "Total number of customers today: "
        << accumulate(begin(service_times), end(service_times), 0)
        << endl;
}

