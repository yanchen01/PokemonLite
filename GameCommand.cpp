#include "GameCommand.h"
#include "Input_Handling.h"
#include <iostream>


void DoMoveCommand(Model& model, int pokemon_id, Point2D p1) {
    if (model.GetPokemonPtr(pokemon_id) != 0) {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to " << p1 << endl;
        model.GetPokemonPtr(pokemon_id)->StartMoving(p1);
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id) {
    if (model.GetPokemonPtr(pokemon_id) != 0 && model.GetPokemonCenterPtr(center_id) != 0) {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to center " << center_id << endl;
        model.GetPokemonPtr(pokemon_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id) {
    if (model.GetPokemonPtr(pokemon_id) != 0 && model.GetPokemonGymPtr(gym_id) != 0) {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to gym " << gym_id << endl;
        model.GetPokemonPtr(pokemon_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoMoveToArenaCommand(Model& model, int pokemon_id, int arena_id) {
    if (model.GetPokemonPtr(pokemon_id) != 0 && model.GetBattleArenaPtr(arena_id) != 0) {
        cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName()
             << " to arena " << arena_id << endl;
        model.GetPokemonPtr(pokemon_id)->StartMovingToArena(model.GetBattleArenaPtr(arena_id));
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoStopCommand(Model& model, int pokemon_id) {
    if (model.GetPokemonPtr(pokemon_id) != 0) {
        cout << "Stopping " << model.GetPokemonPtr(pokemon_id)->GetName() << endl;
        model.GetPokemonPtr(pokemon_id)->Stop();
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units) {
    if (model.GetPokemonPtr(pokemon_id) != 0) {
        cout << "Training " << model.GetPokemonPtr(pokemon_id)->GetName() << endl;
        model.GetPokemonPtr(pokemon_id)->StartTraining(training_units);
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points) {
    if (model.GetPokemonPtr(pokemon_id) != 0) {
        cout << "Recovering " << model.GetPokemonPtr(pokemon_id)->GetName() << "'s stamina" << endl;
        model.GetPokemonPtr(pokemon_id)->StartRecoveringStamina(stamina_points);
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

void DoStartBattleCommand(Model& model, int pokemon_id, int rival_id) {
    if (model.GetPokemonPtr(pokemon_id) != 0 && model.GetRivalPtr(rival_id) != 0) {
        cout << "Battling " << model.GetPokemonPtr(pokemon_id)->GetName() << " with " << model.GetRivalPtr(rival_id)->GetName() << endl;
        model.GetPokemonPtr(pokemon_id)->ReadyBattle(model.GetRivalPtr(rival_id));
    } else
        cout << "ERROR: Please enter a valid command!" << endl;
}

// creates a new object dynamically
void DoCreateNewObject(Model& model, char type,int object_id, Point2D in_loc)
{
    switch(type){
        case 'g':
            // if no replicate gym with same id
            if (model.GetPokemonGymPtr(object_id) == 0)
            {
                // call NewCommand to dynamically create new gym
                model.NewCommand(type, object_id, in_loc);
            }
            else
            {
                throw Invalid_Input("Gym with this ID already exists!");
            }
            
            break;
        case 'c':
            // if no replicate center with same id
            if (model.GetPokemonCenterPtr(object_id) == 0)
            {
                // call NewCommand to dynamically create new gym
                model.NewCommand(type, object_id, in_loc);
            }
            else
            {
                throw Invalid_Input("Center with this ID already exists!");
            }
            
            break;
        case 'p':
            // if no replicate center with same id
            if (model.GetPokemonPtr(object_id) == 0)
            {
                // call NewCommand to dynamically create new gym
                model.NewCommand(type, object_id, in_loc);
            }
            else
            {
                throw Invalid_Input("Pokemon with this ID already exists!");
            }
            
            break;
        case 'r':
            // if no replicate center with same id
            if (model.GetRivalPtr(object_id) == 0)
            {
                // call NewCommand to dynamically create new gym
                model.NewCommand(type, object_id, in_loc);
            }
            else
            {
                throw Invalid_Input("Rival with this ID already exists!");
            }
            
            break;
        default:
            throw Invalid_Input("Unrecognized TYPE code!");
    }
}

void DoGoCommand(Model& model, View& view) {
    cout << "Advancing one tick." << endl;
    model.Update();
    model.ShowStatus();
    cout << "Hi" << endl;
    model.Display(view);
}

void DoRunCommand(Model& model, View& view) {
    cout << "Advancing to next event." << endl;
    int count = 0;
    bool event = false;
    while (count < 5 && !event) {
        event = model.Update();
        count++;
    }
    model.ShowStatus();
    model.Display(view);
}



