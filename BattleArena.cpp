#include <iostream>
using namespace std;

#include "BattleArena.h"

BattleArena::BattleArena()
{
    display_code = 'A';
    pokemon_count = 0;
    max_num_rivals = 3;
    num_rivals_remaining = max_num_rivals;
    dollar_cost_per_fight = 4;
    stamina_cost_per_fight = 3;
    state = RIVALS_AVAILABLE;
    
    cout << "BattleArena default constructed." << endl;
}

BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost, double dollar_cost, int in_Id, Point2D in_loc) : Building('A', in_Id, in_loc)
{
    max_num_rivals = max_rivals;
    num_rivals_remaining = max_num_rivals;
    stamina_cost_per_fight = stamina_cost;
    dollar_cost_per_fight = dollar_cost;
    state = RIVALS_AVAILABLE;
    pokemon_count = 0;

    cout << "BattleArena constructed." << endl;
}

unsigned int BattleArena::GetNumRivalsRemaining()
{
    return num_rivals_remaining;
}

bool BattleArena::HasEnoughRivals()
{
    return (num_rivals_remaining >= 1 ? true : false);
}

double BattleArena::GetDollarCost()
{
    return dollar_cost_per_fight;
}

unsigned int BattleArena::GetStaminaCost()
{
    return stamina_cost_per_fight;
}

// return true if pokemon has enough money and stamina for one fight
bool BattleArena::IsAbleToFight(double budget, unsigned int stamina)
{
    return (budget >= dollar_cost_per_fight && stamina >= stamina_cost_per_fight ? true : false);
}

bool BattleArena::Update()
{

    if (HasEnoughRivals())
        return false;
    else if (!HasEnoughRivals() && state == RIVALS_AVAILABLE)
    {
        state = NO_RIVALS_AVAILABLE;
        return true;
    }
    else
        return false;
}

bool BattleArena::IsBeaten()
{
    return num_rivals_remaining == 0;
}

void BattleArena::AddOneRival()
{
    max_num_rivals++;
    num_rivals_remaining++;
}

void BattleArena::ShowStatus()
{
    cout << "Battle Arena: ";
    Building::ShowStatus();
    // max num of rivals available in battle arena
    cout << "\tMax number of rivals: " << num_rivals_remaining << endl;
    cout << "\tStamina cost per fight: " << stamina_cost_per_fight << endl;
    cout << "\tPokemon dollar per fight: " << dollar_cost_per_fight << endl;
    cout << "\t" << num_rivals_remaining << " rival(s) are remaining for this arena" << endl;
}
