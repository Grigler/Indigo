#include <indigo/indigo.h>

int main(int argc, char *argv[])
{
  //Indigo::Environment env;
  Indigo::RenderManager::StartUp(argc, argv, glm::vec2(640, 480), false);

  while (true) {}

  return 0;
}