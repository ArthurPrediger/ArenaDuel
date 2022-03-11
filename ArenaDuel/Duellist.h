#pragma once
#include <iostream>
#include <random>

int RollDice()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dice(1, 6);
	return dice(rng);
}

class Duellist
{
public:
	Duellist(std::string name, int strength, int agility, int endurance)
		:
		name(name),
		strength(strength),
		agility(agility),
		endurance(endurance),
		energy(6 * (endurance * agility + strength)),
		life(6 * (endurance * strength + agility))
	{};
	Duellist(std::string name)
		:
		name(name)
	{};
	virtual ~Duellist() = default;
	const std::string& GetName() const
	{
		return name;
	}
	int GetLife() const
	{
		return life;
	}
	int GetEnergy() const
	{
		return energy;
	}
	int GetStrength() const
	{
		return strength;
	}
	int GetAgility() const
	{
		return agility;
	}
	int GetEndurance() const
	{
		return endurance;
	}
	void Attack(Duellist& foe)
	{
		if (IsAlive() && foe.IsAlive())
		{
			const int damage = strength * RollDice();
			SetEnergy(-std::max(1, (damage - agility * endurance)));
			if (energy >= 0)
			{
				foe.SetLife(-damage);
				std::cout << GetName() << " attacks " << foe.GetName() << " applying " << damage << " of damage." << std::endl;
				if (!foe.IsAlive())
				{
					std::cout << foe.GetName() << " is dead!" << std::endl;
				}
			}
			else
			{
				std::cout << GetName() << " has no energy to attack!" << std::endl;
			}
		}
	}
	void Recover()
	{
		if (IsAlive())
		{
			const int r = agility * RollDice();
			energy += r;
			std::cout << GetName() << " recovered " << r << " of energy\n";
		}
	};
	int GetInitiative() const
	{
		return GetAgility() * RollDice();
	}
	bool IsAlive() const
	{
		return GetLife() > 0;
	}
protected:
	void SetLife(int difference)
	{
		life += difference;
	}
	void SetEnergy(int difference)
	{
		energy += difference;
	}
	void SetStrength(int strength_in)
	{
		strength = strength_in;
	}
	void SetAgility(int agility_in)
	{
		agility = agility_in;
	}
	void SetEndurance(int endurance_in)
	{
		endurance = endurance_in;
	}
	static constexpr int ptsToDist = 10;
	static constexpr int maxPtsPerAttr = 8;
private:
	std::string name;
	int strength = 1;
	int agility = 1;
	int endurance = 1;
	int energy = 1;
	int life = 1;
};

class CpuDuellist : public Duellist
{
public:
	CpuDuellist(std::string name = "Cpu Powerslave")
		:
		Duellist(name)
	{
		GenerateAttributes();
		SetEnergy(6 * (GetEndurance() * GetAgility() + GetStrength()));
		SetLife(6 * (GetEndurance() * GetStrength() + GetAgility()));
	}
private:
	void GenerateAttributes()
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> stren(1, std::min(maxPtsPerAttr, ptsToDist - (GetAgility() + GetEndurance())));
		SetStrength(stren(rng));
		std::uniform_int_distribution<int> agili(1, std::min(maxPtsPerAttr, ptsToDist - (GetStrength() + GetEndurance())));
		SetAgility(agili(rng));
		SetEndurance(ptsToDist - (GetStrength() + GetAgility()));
	}
};

class UserDuellist : public Duellist
{
public:
	UserDuellist(const std::string name, int strength, int agility, int endurance)
		:
		Duellist(name, strength, agility, endurance)
	{}
};