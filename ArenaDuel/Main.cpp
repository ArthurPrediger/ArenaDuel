#include "Duel.h"

int main()
{
	std::cout << "Welcome to the battle arena!\n" 
		<< "1 - Battle!\n" 
		<< "2 - Wanna quit, retarded?" 
		<< std::endl;

	int input = 0;
	std::cin >> input;

	std::vector<Duelist> cpuD = { CpuDuelist(), CpuDuelist() };
	std::vector<Duelist> userD = { UserDuelist("Dick-butt", 5, 3, 2), UserDuelist("Poo", 4, 2, 4) };

	Duel d = { userD, cpuD };

	if (input == 1)
	{
		system("CLS");
		d.PlayMatch();
	}

	return 0;
}