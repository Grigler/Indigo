#ifndef __IND_SHADER__
#define __IND_SHADER__

#include "GL/glew.h"

#include <string>

namespace Indigo
{
  class Shader
  {
  public:
    //Must be called before any other shader functions
    void Init();
    //Activates this shader for drawing
    void Activate();
    //Attatches Each shader to shader program after loading
    bool LoadShader(GLenum _type, std::string _path);
    //bool LoadShader(GLenum _type, GLchar *_src);
    //Links after loading all required shaders
    bool Link();

  protected:
    GLuint programID;

    GLuint vertID;
    GLuint geomID;
    GLuint fragID;

    static bool CheckCompile(GLuint _programID);

    virtual void LinkUniforms() {}
  };
}

#endif