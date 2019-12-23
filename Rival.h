#ifndef RIVAL_H
#define RIVAL_H

#include <string>
#include <cstdlib>
#include "GameObject.h"
#include "BattleArena.h"

enum RivalStates 
{
    ALIVE_RIVAL = 0,
    FAINTED_RIVAL = 1
};

class Rival: public GameObject
{
    public:
        Rival(string name, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc);
        Rival(int in_id, Point2D in_loc);
        void TakeHit(int physical_damage, int magical_damage, int defense);
        double get_phys_dmg();
        double get_magic_dmg();
        double get_defense();
        double get_health();
        bool Update();
        void ShowStatus();
        bool IsAlive();
        bool ShouldBeVisible(); // declare in order to not become abstract class
        void SetArena(BattleArena* arena);
        string GetName();
    protected:
        string name;
        double health;
        double physical_damage;
        double magical_damage;
        double defense;
        bool is_in_arena;
        BattleArena* current_arena;
};

#endif
