#include <indigo/indigo.h>

//Entry point for engine, this is where the engine will load all
//necessary game data and begin warming any of the necessary
//sub-systems for the game

int main(int argc, char *argv[])
{
  //Starting the Environment first - will be done first in every game
  Indigo::Environment::StartUp();
  //Initialising RenderingManager of startup
  Indigo::RenderManager::StartUp(argc, argv);

  Indigo::RenderManager::SpawnWindow("Window Test", 640, 480);
  //Load + parse config file
  //boot engine with config settings
  //Read some kind of serialized data for scenes/levels/game
  //run necessary assets
  Indigo::Environment::Run();

  return 0;
}