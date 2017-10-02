#include "Camera.h"

#include "RenderManager.h"
#include "RendererTypeComp.h"

#include "Texture.h"
#include "Window.h"
#include "GameObj.h"

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
//Assumes that the list passed in is as optimal as is required
void Camera::Render(std::list<GameObj*> _toDraw)
{
  for (std::list<GameObj*>::iterator obj = _toDraw.begin();
    obj != _toDraw.end(); obj++)
  {
    (*obj)->rtc->Draw(this, (*obj)->trans);
  }
}