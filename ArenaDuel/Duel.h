#pragma once

#include <vector>
#include "Duelist.h"

class Duel
{
public:
	Duel(std::vector<Duelist> duelists)
		:
		duelists(std::move(duelists))
	{};
	void PlayRound()
	{
		if (std::any_of(duelists.begin(), duelists.end(), [&](const Duelist& d)
			{return d  == CPU_DUELIST && d.GetLife() > 0.0f; }))
		{
			auto userD = std::find(duelists.begin(), duelists.end(), [&](const Duelist& d)
				{return d.GetName() == CPU_DUELIST; });

			while (userD->GetLife() > 0.0f)
			{
				//userD->Attack([duelists]());
			}
			nRounds++;
		}
	}
private:
	std::vector<Duelist> duelists;
	int nRounds = 0;
};