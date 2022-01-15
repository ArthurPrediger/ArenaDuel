#include "Duel.h"

int main()
{
	std::cout << "Welcome to the battle arena!\n" 
		<< "1 - Battle!\n" 
		<< "2 - Wanna quit, retarded?" 
		<< std::endl;

	int input = 0;
	std::cin >> input;

	std::vector<Duellist> cpuD = { CpuDuellist(), CpuDuellist() };
	std::vector<Duellist> userD = { UserDuellist("Dick-butt", 5, 3, 2), UserDuellist("Poo", 4, 2, 4) };

	Duel d = { userD, cpuD };

	if (input == 1)
	{
		system("CLS");
		d.PlayMatch();
	}

	return 0;
}