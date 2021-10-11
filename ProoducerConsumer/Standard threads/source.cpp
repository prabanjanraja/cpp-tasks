#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>
using namespace std;

const int num_producers = 3;
const int num_consumers = 5;
const int producer_delay_to_produce = 1000;
const int consumer_delay_to_consume = 3000;

const int consumer_max_wait_time = 2000;

const int max_production = 5;
const int max_products = 10;

atomic<int> num_producers_working(0);
stack<int> products;
mutex xmutex;

condition_variable is_not_full;
condition_variable is_not_empty;

void produce(int producer_id)
{
    unique_lock<mutex> lock(xmutex);
    int product;

    is_not_full.wait(lock, []
                     { return products.size() != max_products; });
    product = products.size();
    products.push(product);
    cout << "Producer " << producer_id << " produced " << product << "\n";
    is_not_empty.notify_all();
}

void consume(int consumer_id)
{
    unique_lock<mutex> lock(xmutex);
    int product;

    if (is_not_empty.wait_for(lock, chrono::milliseconds(consumer_max_wait_time),
                              []
                              { return products.size() > 0; }))
    {
        product = products.top();
        products.pop();

        cout << "\t\t\tConsumer " << consumer_id << " consumed " << product << "\n";
        is_not_full.notify_all();
    }
}

void producer(int id)
{
    ++num_producers_working;
    for (int i = 0; i < max_production; i++)
    {
        produce(id);
        this_thread::sleep_for(chrono::milliseconds(producer_delay_to_produce));
    }
    --num_producers_working;
}

void consumer(int id)
{
    while (num_producers_working == 0)
        this_thread::yield();

    while (num_producers_working != 0 || products.size() > 0)
    {
        consume(id);
        this_thread::sleep_for(chrono::milliseconds(consumer_delay_to_consume));
    }
}

int main()
{
    vector<thread> producers_and_consumers;

    // Create producers
    for (int i = 0; i < num_producers; ++i)
        producers_and_consumers.push_back(thread(producer, i));

    // Create consumers
    for (int i = 0; i < num_consumers; ++i)
        producers_and_consumers.push_back(thread(consumer, i));

    // Wait for consumers and producers to finish
    for (auto &t : producers_and_consumers)
        t.join();
}