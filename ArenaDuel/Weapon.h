#pragma once
#include <iostream>

class Weapon
{
public:
	Weapon(std::string name, int rank)
		:
		name(name),
		rank(rank)
	{}
	const std::string& GetName() const
	{
		return name;
	}
	int GetRank() const
	{
		return rank;
	}
	virtual int Damage(int strength, int agility) = 0;
private:
	std::string name;
	int rank;
};

class Fists : public Weapon
{
public:
	Fists()
		:
		Weapon("fists", 0)
	{}
	int Damage(int strength, int agility)
	{
		return strength;
	}
};

class Hammer : public Weapon
{
public:
	Hammer()
		:
		Weapon("hammer", 1)
	{}
	int Damage(int strength, int agility)
	{
		return strength + agility;
	}
};

class Knife : public Weapon
{
public:
	Knife()
		:
		Weapon("knife", 2)
	{}
	int Damage(int strength, int agility)
	{
		return strength + 2 * agility;
	}
};

class Bat : public Weapon
{
public:
	Bat()
		:
		Weapon("bat", 3)
	{}
	int Damage(int strength, int agility)
	{
		return 3 * strength + agility;
	}
};