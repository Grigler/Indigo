#ifndef __IND_MESH_RENDERER__
#define __IND_MESH_RENDERER__

#include "RendererTypeComp.h"

#include "GL/glew.h"

namespace Indigo
{

  class Mesh;

  class MeshRenderer : public RendererTypeComp
  {
    friend class Camera;
  public:

  private:
    Mesh *mesh;
    void Draw(Camera *_c, Transform *_trans);

    GLuint vao;
  };

} //End of namespace

#endif