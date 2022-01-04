#include "Duelist.h"

int main()
{
	std::cout << "Welcome to the battle arena!\n" 
		<< "1 - Battle!\n" 
		<< "2 - Wanna quit, retarded?" 
		<< std::endl;

	int input = 0;
	//std::cin >> input;

	CpuDuelist d = {};
	std::cout << "\n\n" << d.GetStrength();
	std::cout << "\n" << d.GetAgility();
	std::cout << "\n" << d.GetEndurance();
	std::cout << "\n" << d.GetLife();
	std::cout << "\n" << d.GetEnergy();

	if (input == 1)
	{
		return 69;
	}

	return 0;
}