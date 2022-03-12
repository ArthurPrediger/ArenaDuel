#include "Duel.h"

int main()
{
	std::cout << "Welcome to the battle arena!\n"
		<< "1 - Battle!\n"
		<< "2 - Wanna quit, retarded?"
		<< std::endl;

	int input = 0;
	std::cin >> input;

	Duel d;

	d.cpuDuellists.push_back(std::make_unique<CpuDuellist>(std::make_unique<Fists>()));
	d.cpuDuellists.push_back(std::make_unique<CpuDuellist>(std::make_unique<Bat>()));
	d.userDuellists.push_back(std::make_unique<UserDuellist>("Dick-butt", 5, 3, 2, std::make_unique<Hammer>()));
	d.userDuellists.push_back(std::make_unique<UserDuellist>("Poo", 4, 2, 4, std::make_unique<Knife>()));

	if (input == 1)
	{
		system("CLS");
		d.PlayMatch();
	}

	return 0;
}