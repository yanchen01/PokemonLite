#ifndef MODEL_H
#define MODEL_H
#include "GameObject.h"
#include "Pokemon.h"
#include "Rival.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "BattleArena.h"
#include "View.h"
#include <list>
#include <iterator>

class Model {
    
public:
    //simulation time
    int time;
    list<GameObject*> object_ptrs;
    list<GameObject*> active_ptrs;
    list<Pokemon*> pokemon_ptrs;
    list<PokemonCenter*> center_ptrs;
    list<PokemonGym*> gym_ptrs;
    list<Rival*> rival_ptrs;
    list<BattleArena*> arena_ptrs;
    
public:
    Model();
    ~Model();
    Pokemon* GetPokemonPtr(int id);
    PokemonCenter* GetPokemonCenterPtr(int id);
    PokemonGym* GetPokemonGymPtr(int id);
    Rival* GetRivalPtr(int id);
    BattleArena* GetBattleArenaPtr(int id);
    bool Update();
    void Display(View &view);
    void ShowStatus();
    void NewCommand(char type,int object_id, Point2D in_loc);
};


#endif
