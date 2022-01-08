#pragma once
#include <iostream>
#include <random>

int RollDice()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dice(1, 6);
	return dice(rng);
}

class Duelist
{
public:
	Duelist(const std::string name, int strength, int agility, int endurance)
		:
		name(name),
		strength(strength),
		agility(agility),
		endurance(endurance),
		energy(6 * (endurance * agility + strength)),
		life(6 * (endurance * strength + agility))
	{};
	virtual ~Duelist() = default;
	const std::string GetName() const
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
	void Attack(Duelist& foe)
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
private:
	std::string name;
	int strength;
	int agility;
	int endurance;
	int energy;
	int life;
};

class CpuDuelist : public Duelist
{
public:
	CpuDuelist(std::string name = "Cpu Powerslave")
		:
		Duelist(name, 0, 0, 0)
	{
		SetStrength(GenerateStren());
		SetAgility(GenerateAgili());
		SetEndurance(GenerateEndur());
		SetEnergy(6 * (GetEndurance() * GetAgility() + GetStrength()));
		SetLife(6 * (GetEndurance() * GetStrength() + GetAgility()));
	}
private:
	int GenerateStren()
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> stren(1, 8);
		return stren(rng);
	}
	int GenerateAgili()
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> agili(1, 9 - GetStrength());
		return agili(rng);
	}
	int GenerateEndur()
	{
		return 10 - (GetStrength() + GetAgility());
	}
};

class UserDuelist : public Duelist
{
public:
	UserDuelist(const std::string name, int strength, int agility, int endurance)
		:
		Duelist(name, strength, agility, endurance)
	{}
};