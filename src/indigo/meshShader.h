#ifndef __IND_MESH_SHADER__
#define __IND_MESH_SHADER__

#include "Shader.h"

//Single header Mesh Shader class with hard-coded shader source

namespace Indigo
{

  class MeshShader : public Shader
  {
  public:
    void LoadDefaultShaders();

    GLuint mvpHandle;
  private:
    void LinkUniforms();
  };

  void MeshShader::LoadDefaultShaders()
  {
    static bool isFirst = true;
    if (isFirst)
    {
      LoadShader(GL_VERTEX_SHADER,
        "C:/Users/i7465070/Indigo/data/Shaders/MeshRenderer/MeshRenderer.vert");

      LoadShader(GL_FRAGMENT_SHADER,
        "C:/Users/i7465070/Indigo/data/Shaders/MeshRenderer/MeshRenderer.frag");
    }
    isFirst = false;
  }

  void MeshShader::LinkUniforms()
  {
    glGetUniformLocation(programID, "MVP");
  }

}

#endif