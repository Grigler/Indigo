#ifndef __IND_SHADER__
#define __IND_SHADER__

#include "GL/glew.h"

#include <string>

namespace Indigo
{
  class Shader
  {
  public:
    void Init();
    void Activate();

    bool LoadShader(GLenum _type, std::string _path);
    bool Link();

  protected:
    GLuint programID;

    GLuint vertID;
    GLuint geomID;
    GLuint fragID;

    static bool CheckCompile(GLuint _programID);
  };
}

#endif