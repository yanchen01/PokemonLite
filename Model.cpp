#include "Model.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <cstdlib>
#include <iostream>
#include <string>

Model::Model() {
    time = 0;
    //Pikachu 1
    pokemon_ptrs.push_back(new Pokemon("Pikachu", 2.0, 23, 3, 6, 12, 1, 'P', Point2D(5, 1)));
    //Pikachu 2
    pokemon_ptrs.push_back(new Pokemon("Bulbasaur", 1.0, 26, 4, 3.7, 16, 2, 'P', Point2D(10, 1)));
    //PokemonCenter 1
    center_ptrs.push_back(new PokemonCenter(1, 1, 100, Point2D(1, 20)));
    //PokemonCenter 2
    center_ptrs.push_back(new PokemonCenter(2, 2, 200,  Point2D(10, 20)));
    //PokemonGym
    gym_ptrs.push_back(new PokemonGym(10, 1.0, 2.0, 3, 1, Point2D(0, 0)));
    gym_ptrs.push_back(new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5)));
    //Arena
    arena_ptrs.push_back(new BattleArena(3, 3, 2.5, 1, Point2D(15, 12)));
    //Rivals
    rival_ptrs.push_back(new Rival("burhack", 16, 3, 7.2, 20, 1, Point2D(15, 12)));
    rival_ptrs.push_back(new Rival("mark", 29, 4, 5.2, 12, 2, Point2D(15, 12)));

    list <Pokemon*> :: iterator pokemon_it;
    for (pokemon_it = pokemon_ptrs.begin(); pokemon_it != pokemon_ptrs.end(); pokemon_it++)
    {
        object_ptrs.push_back(*pokemon_it);    
        active_ptrs.push_back(*pokemon_it);
    }

    list <PokemonCenter*> :: iterator center_it;
    for (center_it = center_ptrs.begin(); center_it != center_ptrs.end(); center_it++)
    {
        object_ptrs.push_back(*center_it);    
        active_ptrs.push_back(*center_it);  
    }

    list <PokemonGym*> :: iterator gym_it;
    for (gym_it = gym_ptrs.begin(); gym_it != gym_ptrs.end(); gym_it++)
    {
        object_ptrs.push_back(*gym_it);    
        active_ptrs.push_back(*gym_it);  
    }

    list <Rival*> :: iterator rival_it;
    for (rival_it = rival_ptrs.begin(); rival_it != rival_ptrs.end(); rival_it++)
    {
        object_ptrs.push_back(*rival_it);    
        active_ptrs.push_back(*rival_it);  
    }

    list <BattleArena*> :: iterator arena_it;
    for (arena_it = arena_ptrs.begin(); arena_it != arena_ptrs.end(); arena_it++)
    {
        object_ptrs.push_back(*arena_it);    
        active_ptrs.push_back(*arena_it);
        // iterate through rival to check if rival is inside the specific arena
        for (rival_it = rival_ptrs.begin(); rival_it != rival_ptrs.end(); rival_it++)
        {
            // if rival belongs to the arena, set rival's arena to be the current arena 
            if ((*rival_it)->GetLocation() == (*arena_it)->GetLocation())
            {
                (*rival_it)->SetArena(*arena_it);
            }
        }
    }

    cout << "Model default constructed. " << endl;
}

Model::~Model() {
    list <GameObject*> :: iterator it;

    for (it = object_ptrs.begin(); it != object_ptrs.end(); it++) {
        delete (*it);
    }
    object_ptrs.clear();
    cout << "Model destructed. " << endl;
}

Pokemon *Model::GetPokemonPtr(int id) {

    list <Pokemon*> :: iterator itr;
    for (itr = pokemon_ptrs.begin(); itr != pokemon_ptrs.end(); itr++)
    {
        if (id == (*itr)->GetId()) {
            return *itr;
        }
    }
    return 0;
}

PokemonCenter *Model::GetPokemonCenterPtr(int id) {
    list <PokemonCenter*> :: iterator itr;
    for (itr = center_ptrs.begin(); itr != center_ptrs.end(); itr++)
    {
        if (id == (*itr)->GetId()) {
            return *itr;
        }
    }
    return 0;
}

PokemonGym *Model::GetPokemonGymPtr(int id) {
    list <PokemonGym*> :: iterator itr;
    for (itr = gym_ptrs.begin(); itr != gym_ptrs.end(); itr++)
    {
        if (id == (*itr)->GetId()) {
            return *itr;
        }
    }
    return 0;
}

Rival* Model::GetRivalPtr(int id)
{
    list <Rival*> :: iterator itr;
    for (itr = rival_ptrs.begin(); itr != rival_ptrs.end(); itr++)
    {
        if (id == (*itr)->GetId()) {
            return *itr;
        }
    }
    return 0;
}

BattleArena* Model::GetBattleArenaPtr(int id)
{
    list <BattleArena*> :: iterator itr;
    for (itr = arena_ptrs.begin(); itr != arena_ptrs.end(); itr++)
    {
        if (id == (*itr)->GetId()) {
            return *itr;
        }
    }
    return 0;
}

bool Model::Update() {
    time++;
    int gyms_beaten = 0;
    int pokemon_exhausted = 0;
    //Calculating number of gyms beaten
    if (gyms_beaten != gym_ptrs.size()) {
        
        for (list<PokemonGym*>::iterator itr = gym_ptrs.begin(); itr != gym_ptrs.end(); itr++) {
            if ((*itr)->GetState() == BEATEN)
                gyms_beaten++;
        }
    }

    // Calculating number of pokemon that are tired
    if (pokemon_exhausted != pokemon_ptrs.size()) {
        for (list<Pokemon*>::iterator itr = pokemon_ptrs.begin(); itr != pokemon_ptrs.end(); itr++) {
            if ((*itr)->IsExhausted())
                pokemon_exhausted++;
        }
    }
    bool event = false;
    // continue to update all
    if (gyms_beaten == gym_ptrs.size()) {
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(EXIT_SUCCESS);
    }
    if (pokemon_exhausted == pokemon_ptrs.size()) {
        cout << "GAME OVER: You lose! All of your Pokemon are exhausted!" << endl;
        exit(EXIT_SUCCESS);
    }
    list <GameObject*> :: iterator it;
    // update if winning condition is not met
    for (it = active_ptrs.begin(); it != active_ptrs.end(); it++) {
        bool temp = (*it)->Update();
        if (temp) {
            event = temp;
        }

        // if object dies, remove from active ptr
        if (!(*it)->IsAlive())
        {
            it = active_ptrs.erase(it);
        }
    }
    return event;
}

void Model::Display(View &view) {
    view.Clear();
    list <GameObject*> :: iterator it;
    for (it = active_ptrs.begin(); it != active_ptrs.end(); it++) {
        if ((*it)->ShouldBeVisible()) {
            view.Plot(*it);
        }
    }
    view.Draw();
}

void Model::ShowStatus() {
    cout << "Time: " << time << endl;

    list <GameObject*> :: iterator it;
    for (it = object_ptrs.begin(); it != object_ptrs.end(); it++) {
        (*it)->ShowStatus();
    }
}

void Model::NewCommand(char type,int object_id, Point2D in_loc)
{
    list <PokemonGym*> :: iterator gym_it;
    list <PokemonCenter*> :: iterator center_it_2;
    list <Pokemon*> :: iterator pokemon_it_2;
    list <Rival*> :: iterator rival_it;
    list <BattleArena*> :: iterator arena_it;
    switch (type)
    {
    case 'g':
        gym_ptrs.push_back(new PokemonGym(object_id, in_loc));
        // gym_it = gym_ptrs.back();
        object_ptrs.push_back(gym_ptrs.back());
        active_ptrs.push_back(gym_ptrs.back());
        break;
    case 'c':
        center_ptrs.push_back(new PokemonCenter(object_id, in_loc));

        // center_it_2 = center_ptrs.back();
        object_ptrs.push_back(center_ptrs.back());
        active_ptrs.push_back(center_ptrs.back());
        break;
    case 'p':
        pokemon_ptrs.push_back(new Pokemon(object_id, in_loc));
        // pokemon_it_2 = pokemon_ptrs.back();
        object_ptrs.push_back(pokemon_ptrs.back());
        active_ptrs.push_back(pokemon_ptrs.back());
        break;
    case 'r':
        rival_ptrs.push_back(new Rival(object_id, in_loc));

        // rival_it = rival_ptrs.back();
        // there's only 1 arena in the game throughout, so rivals will all be inside that arena
        
        // arena_it = arena_ptrs.back();
        // arena now contains 1 more rival
        (arena_ptrs.back())->AddOneRival();
        // rival's arena is set to the arena
        (*rival_it)->SetArena(arena_ptrs.back());
        object_ptrs.push_back(rival_ptrs.back());
        active_ptrs.push_back(rival_ptrs.back());
        break;
    default:
        break;
    }
}
