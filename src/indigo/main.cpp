#include <indigo/indigo.h>

//Entry point for engine, this is where the engine will load all
//necessary game data and begin warming any of the necessary
//sub-systems for the game

int main(int argc, char *argv[])
{
  //Indigo::Environment env;
  Indigo::RenderManager::StartUp(argc, argv, 640, 480, false);

  //Load + parse config file
  //boot engine with config settings
  //Read some kind of serialized data for scenes/levels/game
  //run necessary assets

  while (true) 
  {
    Indigo::Environment::Update();
  }

  return 0;
}