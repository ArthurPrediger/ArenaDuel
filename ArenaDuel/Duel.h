#pragma once

#include <vector>
#include "Duelist.h"
#include <algorithm>

class Duel
{
public:
	Duel(std::vector<Duelist> userDuelists, std::vector<Duelist> cpuDuelists)
		:
		userDuelists(std::move(userDuelists)),
		cpuDuelists(std::move(cpuDuelists))
	{};
	void PlayMatch()
	{
		const auto alive_pred = [](const Duelist& d) {return d.IsAlive(); };
		while (std::any_of(userDuelists.begin(), userDuelists.end(), alive_pred) && 
			std::any_of(cpuDuelists.begin(), cpuDuelists.end(), alive_pred))
		{
			std::mt19937 rng(std::random_device{}());
			std::shuffle(userDuelists.begin(), userDuelists.end(), rng);
			std::partition(userDuelists.begin(), userDuelists.end(), alive_pred);
			std::shuffle(cpuDuelists.begin(), cpuDuelists.end(), rng);
			std::partition(cpuDuelists.begin(), cpuDuelists.end(), alive_pred);

			for (size_t i = 0; i < std::min(userDuelists.size(), cpuDuelists.size()); i++)
			{
				Engage(userDuelists[i], cpuDuelists[i]);
			}
			std::cout << std::endl;

			for (size_t i = 0; i < std::max(userDuelists.size(), cpuDuelists.size()); i++)
			{
				userDuelists[i].Recover();
				cpuDuelists[i].Recover();
			}

			std::cout << "\n=================================================\n";
		}

		if (std::any_of(userDuelists.begin(), userDuelists.end(), alive_pred))
		{
			std::cout << "You win!" << std::endl;
		}
		else
		{
			std::cout << "Of course you had lost! What controls this, retarded?" << std::endl;
		}
	}
	void Engage(Duelist& d1, Duelist& d2)
	{
		auto* pd1 = &d1;
		auto* pd2 = &d2;

		if (pd1->GetInitiative() < pd2->GetInitiative())
		{
			std::swap(pd1, pd2);
		}

		pd1->Attack(*pd2);
		pd2->Attack(*pd1);
	}
private:
	std::vector<Duelist> userDuelists;
	std::vector<Duelist> cpuDuelists;
	int nRounds = 0;
};