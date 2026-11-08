// Kruhlienia Yulia K-28
#include <iostream>
#include <syncstream>
#include <future>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

void slow(const string& name)
{
    this_thread::sleep_for(chrono::seconds(7));
    osyncstream(cout) << name << endl;
}


void quick(const string& name)
{
    this_thread::sleep_for(chrono::seconds(1));
    osyncstream(cout) << name << endl;
}

void runB()
{
    quick("B1");
    slow("B2");
    quick("B3");
}

void work()
{
    auto start = chrono::steady_clock::now();

    future<void> fb = async(launch::async, runB);

    quick("A1");
    slow("A2");
    quick("A3");

    fb.get();
    quick("C");

    auto end = chrono::steady_clock::now();
    double secs = chrono::duration<double>(end - start).count();

    osyncstream(cout) << "Execution time: " << secs << " s" << endl;
    osyncstream(cout) << "Work is done!" << endl;
}


int main() {
    work();
	return 0;
}