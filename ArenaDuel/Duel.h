#pragma once

#include "Duellist.h"

class Duel
{
public:
	Duel(std::vector<Duellist> userDuellists, std::vector<Duellist> cpuDuellists)
		:
		userDuellists(std::move(userDuellists)),
		cpuDuellists(std::move(cpuDuellists))
	{};
	void PlayMatch()
	{
		const auto alive_pred = [](const Duellist& d) {return d.IsAlive(); };
		while (std::any_of(userDuellists.begin(), userDuellists.end(), alive_pred) && 
			std::any_of(cpuDuellists.begin(), cpuDuellists.end(), alive_pred))
		{
			std::mt19937 rng(std::random_device{}());
			std::shuffle(userDuellists.begin(), userDuellists.end(), rng);
			std::partition(userDuellists.begin(), userDuellists.end(), alive_pred);
			std::shuffle(cpuDuellists.begin(), cpuDuellists.end(), rng);
			std::partition(cpuDuellists.begin(), cpuDuellists.end(), alive_pred);

			for (size_t i = 0; i < std::min(userDuellists.size(), cpuDuellists.size()); i++)
			{
				Engage(userDuellists[i], cpuDuellists[i]);
			}
			std::cout << std::endl;

			for (size_t i = 0; i < std::max(userDuellists.size(), cpuDuellists.size()); i++)
			{
				userDuellists[i].Recover();
				cpuDuellists[i].Recover();
			}

			std::cout << "\n=================================================\n";
		}

		if (std::any_of(userDuellists.begin(), userDuellists.end(), alive_pred))
		{
			std::cout << "You win!" << std::endl;
		}
		else
		{
			std::cout << "Of course you had lost! What controls this, retarded?" << std::endl;
		}
	}
	void Engage(Duellist& d1, Duellist& d2)
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
	std::vector<Duellist> userDuellists;
	std::vector<Duellist> cpuDuellists;
	int nRounds = 0;
};