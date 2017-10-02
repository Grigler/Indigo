#include "MeshRenderer.h"

#include "Mesh.h"
#include "Camera.h"
#include "Transform.h"

#include "GL/freeglut.h"
#include "GL/glew.h"
#include "glm/glm.hpp"

using namespace Indigo;

void MeshRenderer::Draw(Camera *_c, Transform *_trans)
{
  if (mesh == nullptr)
  {
    throw std::exception();
  }

  glm::vec4 worldPos = _trans->GetPosition();
  glm::vec3 eulerRot = _trans->GetRotation();

  //TODO - remember how to draw using second year slides

  //Bind all buffers associated with vao
  glBindVertexArray(vao);
  //Activating buffers within vao (disabled by default)
  glEnableVertexAttribArray(vao);

  //enable material (contains shader and enables it)



  //drawing from buffers

  glDisableVertexAttribArray(vao);
  glBindVertexArray(0); //Unbinding vao
}