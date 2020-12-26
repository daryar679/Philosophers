#include "Philosophers.h"

using namespace std;

Philosopher::Philosopher()
{
	philosophers.emplace_back(&Philosopher::Phil, this, 0, "Socrat");
	philosophers.emplace_back(&Philosopher::Phil, this, 1, "Platon");
	philosophers.emplace_back(&Philosopher::Phil, this, 2, "Decart");
	philosophers.emplace_back(&Philosopher::Phil, this, 3, "Popper");
	philosophers.emplace_back(&Philosopher::Phil, this, 4, "Aristotel");

	for (auto& t : philosophers) t.join();
}

void Philosopher::print_msg(const string& msg)
{
	cout_mutex.lock();
	cout << msg << flush;
	cout_mutex.unlock();
}


void Philosopher::Phil(size_t idx, const string& id)
{
	mutex& left_fork = forks[idx == 0 ? 4 : idx - 1];
	mutex& right_fork = forks[idx];
	ostringstream ostr;

	while (true)
	{
		{
			ostr << id << " is thinking " << endl;
			print_msg(ostr.str());
		}

		// Thinking ...
		this_thread::sleep_for(chrono::seconds(rand() % 5));

		// Got hungry
		{
			ostr << id << " got hungry" << endl;
			print_msg(ostr.str());
		}

		// wait for forks

		if (left_fork.try_lock())
		{
			ostr << id << " got left fork! " << endl;
			print_msg(ostr.str());

			if (right_fork.try_lock())
			{
				ostr << id << " got right fork! " << endl;
				print_msg(ostr.str());

				ostr << id << " can eat!" << endl;
				print_msg(ostr.str());

				this_thread::sleep_for(chrono::seconds(1));

				right_fork.unlock();
				left_fork.unlock();
			}
			else
			{
				ostr << id << " can't eat!" << endl;
				print_msg(ostr.str());

				left_fork.unlock();
				this_thread::sleep_for(chrono::seconds(rand() % 5));
			}
		}
	}
}



int main()
{
	srand(time(0));
	Philosopher p;

	return 0;
}