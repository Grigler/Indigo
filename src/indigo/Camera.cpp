#include "Camera.h"

#include "RenderManager.h"

#include "Texture.h"
#include "Window.h"

using namespace Indigo;

Camera::Camera(GameObj *_parent) : Component(_parent)
{
  isActive = false;
  RenderManager::RegisterCamera(this);
}
Camera::~Camera()
{
  RenderManager::UnregisterCamera(this);
}

void Camera::SetRenderToTexture(Texture *_text)
{
  renderTexture = _text;
}
void Camera::SetRenderToWindow(Window *_window)
{
  //Nulling the current reference, but not destroying memory
  renderTexture = nullptr;
}