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
	Duelist(const std::string name, float strength, float agility, float endurance)
		:
		name(name),
		strength(strength),
		agility(agility),
		endurance(endurance)
	{
		energy = endurance * agility + strength;
		life = endurance * strength + agility;
	};
	const std::string GetName() const
	{
		return name;
	}
	float GetLife() const
	{
		return life;
	}
	void SetLife(float difference)
	{
		life += difference;
	}
	float GetEnergy() const
	{
		return energy;
	}
	void SetEnergy(float difference)
	{
		energy += difference;
	}
	float GetStrength() const
	{
		return strength;
	}
	float GetAgility() const
	{
		return agility;
	}
	float GetEndurance() const
	{
		return endurance;
	}
	void Attack(Duelist& enemy)
	{
		const float damage = strength * (float)RollDice();
		energy -= std::max(1.0f, (damage - agility * endurance));
		if (energy >= 0.0f)
		{
			enemy.SetLife(damage);
		}
		else
		{
			Recover();
		}
	}
	void Recover()
	{
		energy += std::max(agility * RollDice(), 6.0f);
	};
private:
	std::string name;
	float strength;
	float agility;
	float endurance;
	float energy;
	float life;
};

class CpuDuelist : public Duelist
{
public:
	CpuDuelist(std::string name = "Cpu Powerslave")
		:
		Duelist(name, GenerateStren(), GenerateAgili(), GenerateEndur())
	{}
private:
	float GenerateStren() const
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float> stren(1.0f, 8.0f);
		return stren(rng);
	}
	float GenerateAgili() const
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float> agili(1.0f, 9.0f - GetStrength());
		return agili(rng);
	}
	float GenerateEndur() const
	{
		return 10.0f - (GetStrength() + GetAgility());
	}
};
