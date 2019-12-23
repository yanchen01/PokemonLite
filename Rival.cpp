#include <iostream>
using namespace std;

#include "Rival.h"

Rival::Rival(string name, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc) : GameObject(in_loc, id, 'R')
{
    this->name = name;
    health = hp;
    physical_damage = phys_dmg;
    magical_damage = magic_dmg;
    defense = def;
    state = ALIVE_RIVAL;

    cout << "Rival constructed." << endl;
}

Rival::Rival(int in_id, Point2D in_loc) : GameObject(in_loc, in_id, 'R')
{
    name = "Rival";
    health = 10;
    physical_damage = 2;
    magical_damage = 4.2;
    defense = 15;
    state = ALIVE_RIVAL;

    cout << "Rival constructed." << endl;
}

void Rival::TakeHit(int physical_damage, int magical_damage, int defense)
{
    // if random is even number, choose physical_damage
    if (rand() % 2 == 0)
    {
        double damage = (100.0 - defense) / 100.0 * physical_damage;
        health -= damage;

        cout << "Aaagh, no physical pain no gain!" << endl;
        cout << "Damage: " << damage << endl;
        cout << "Health: " << health << endl;
        cout << "*******" << endl;
    }
    else // magical damage
    {
        double damage = (100.0 - defense) / 100.0 * magical_damage;
        health -= damage;
        
        cout << "Ouch, I don't believe magic!" << endl;
        cout << "Damage: " << damage << endl;
        cout << "Health: " << health << endl;
        cout << "*******" << endl;
    }
}

double Rival::get_phys_dmg()
{
    return physical_damage;
}

double Rival::get_magic_dmg()
{
    return magical_damage;
}

double Rival::get_defense()
{
    return defense;
}

double Rival::get_health()
{
    return health;
}

string Rival::GetName() {
    return name;
}

bool Rival::IsAlive()
{
    if (state != FAINTED_RIVAL)
    {
        return true;
    }
    else
    {
        state = FAINTED_RIVAL;
        return false;
    }
}

bool Rival::Update()
{
    switch (state)
    {
        case ALIVE_RIVAL:
            // if health is 0 or below, state becomes fainted
            if (health <= 0)
            {
                state = FAINTED_RIVAL;
                return true;
            }
            return false;
        case FAINTED_RIVAL:
            return false;
    }
}

void Rival::SetArena(BattleArena* arena)
{
    current_arena = arena;
}

bool Rival::ShouldBeVisible() {
    return IsAlive(); // if alive, make visible
}

void Rival::ShowStatus()
{
    cout << name << " status: ";
    GameObject::ShowStatus();
    
    // print out if rival is alive or dead
    switch(state)
    {
        case ALIVE_RIVAL:
            cout << " alive" << endl;
            break;
        case FAINTED_RIVAL:
            cout << " dead, RIP..." << endl;
            break;
        default:
            break;
    }

    // print out basic info about rival
    cout << "\tHealth: " << health << endl;
    cout << "\tPhysical Damage: " << physical_damage << endl;
    cout << "\tMagical Damage: " << magical_damage << endl;
    cout << "\tDefense: " << defense << endl;
}
