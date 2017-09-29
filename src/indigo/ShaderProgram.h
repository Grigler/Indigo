#ifndef __IND_SHADER_PROGRAM__
#define __IND_SHADER_PROGRAM__

#include "GL/glew.h"
#include <string>

namespace Indigo
{

  class ShaderProgram
  {
  public:
    ShaderProgram();
    ~ShaderProgram();
    
    void MakeActive();
    GLuint GetID();
    void LoadShader(GLenum _type, std::string _path);
    void Link();
  private:

    GLuint programID;

    GLuint vertID;
    GLuint geomID;
    GLuint fragID;

    bool CheckCompile(GLuint _shaderID);

  };

} //End of namespace

#endif