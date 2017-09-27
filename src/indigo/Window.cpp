#include "Window.h"

#include "RenderManager.h"

using namespace Indigo;

Window::Window(std::string _name, int _w, int _h)
{
  name = _name;
  winWidth = _w;
  winHeight = _h;

  RenderManager::RegisterWindow(this);
}
Window::~Window()
{
  RenderManager::UnregisterWindow(this);
}

void Window::Reshape(int _w, int _h)
{
  winWidth = _w; winHeight = _h;
  printf("%i\t%i\n", winWidth, winHeight);
}