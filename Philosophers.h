#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Philosopher 
{

public:
	Philosopher();
	//~Philosopher();
	void print_msg(const string& msg);
	[[noreturn]]void Phil(size_t idx, const string& id);

private:
	mutex forks[5];
	mutex cout_mutex;
	vector<thread> philosophers;
};