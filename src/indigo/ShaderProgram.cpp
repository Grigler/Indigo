#include "ShaderProgram.h"

#include <fstream>

using namespace Indigo;

ShaderProgram::ShaderProgram()
{
  programID = glCreateProgram();
  vertID = 0; geomID = 0; fragID = 0;
}
ShaderProgram::~ShaderProgram()
{
  //Detatching and deleting valid shaders
  //Manual detatch isn't necessary, but deletion flag is
  if (vertID != 0)
  {
    glDetachShader(programID, vertID); glDeleteShader(vertID);    
  }
  if (geomID)
  {
    glDetachShader(programID, geomID); glDeleteShader(geomID);
  }
  if (fragID)
  {
    glDetachShader(programID, fragID); glDeleteShader(fragID);
  }

  glDeleteProgram(programID);
}

void ShaderProgram::MakeActive()
{
  glUseProgram(programID);
}
GLuint ShaderProgram::GetID()
{
  return programID;
}
void ShaderProgram::LoadShader(GLenum _type, std::string _path)
{
  GLchar *src;
  std::ifstream file(_path);
  if (file.is_open())
  {
    file.seekg(0, file.end);
    int len = (int)file.tellg();
    file.seekg(0, file.beg);
    src = new char[len];
    file.read(src, len);
    if (file.eof())
    {
      file.close();
    }
    else
    {
      //No EOF in file, manually set
      len = (int)file.gcount();
      src[len] = 0;
      file.close();
    }
  }
  else
  {
    throw std::exception();
  }

  GLuint *id;

  switch (_type)
  {
  case GL_VERTEX_SHADER:
    id = &vertID;
    break;
  case GL_GEOMETRY_SHADER:
    id = &geomID;
    break;
  case GL_FRAGMENT_SHADER:
    id = &fragID;
    break;
  default:
    throw std::exception();
    break;
  }

  (*id) = glCreateShader(_type);
  glShaderSource((*id), 1, &src, NULL);
  glCompileShader((*id));
  if (CheckCompile((*id)))
  {
    glAttachShader(programID, (*id));
  }
  else
  {
    throw std::exception();
  }

  delete[] src;
}
void ShaderProgram::Link()
{
  glLinkProgram(programID);

  //TODO - PUT IN IND_DEBUG FLAG
  GLint linked;
  glGetShaderiv(programID, GL_LINK_STATUS, &linked);
  if (!linked)
  {
    GLsizei len;
    glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &len);
    GLchar* log = new GLchar[len + 1];
    glGetShaderInfoLog(programID, len, &len, log);
    fprintf(stderr, "\nShader Compile Failed:\n%s\n", log);
    delete[] log;
  }
  //END IND_DEBUG FLAG
}

bool ShaderProgram::CheckCompile(GLuint _shaderID)
{
  GLint compiled;
  glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
  {
    // TODO - put in an IND_DEBUG preprocessor flag
    GLsizei len;
    glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &len);
    GLchar* log = new GLchar[len + 1];
    glGetShaderInfoLog(_shaderID, len, &len, log);
    fprintf(stderr, "\nShader Compile Failed:\n%s\n", log);
    delete[] log;
    //END IND_DEBUG FLAG
    return false;
  }
  return true;
}