#include "RenderBuffer.h"

#include "Shader.h"

#include "Application.h"


using namespace Indigo;

void RenderBuffer::GenBuffers(GLsizei _x, GLsizei _y)
{
  x = _x;
  y = _y;

  //Gen and bind framebuffrer
  glGenFramebuffers(1, &frameBufferID);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

  //Gen, bind texutre and define parameters
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, _x, _y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  //Gen, binding and defining depthbuffer
  glGenRenderbuffers(1, &depthBufferID);
  glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _x, _y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);
  
  //Linking texture to framebuffer as GL_COLOR_ATTACHMENT0
  //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

  //Giving the framebuffer the list of buffers to draw to - only the bound texture
  const GLenum buf[] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers(1, buf);

  genSuccessfully = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
  if (!genSuccessfully)
  {
    //Framebuffer capabilities not there
    Application::ErrPrint("Frame Buffer did not generate - will not bind for drawing");
  }
  else
  {
    GenQuadVAO();
  }
}
void RenderBuffer::GenQuadVAO()
{
  static const GLfloat quadVerts[] =
  {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
  };
  static const GLfloat quadUVs[] =
  {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
  };

  //Gen VAO
  glGenVertexArrays(1, &quadVAO);
  glBindVertexArray(quadVAO);

  //Gen VBO locally - stored in VAO anyway
  GLuint quadVBO;
  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadUVs), quadUVs, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
}
//TODO
void RenderBuffer::ReSize(GLsizei _x, GLsizei _y)
{

}
void RenderBuffer::Bind()
{
  //Only binds if it was generated successfully
  //meaning it will just draw to default if there is no framebuffer
  //capability
  if (genSuccessfully)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, x, y);
  }
}

void RenderBuffer::AttachShader(std::shared_ptr<Shader> _shader)
{
  shader = _shader;
}
//Draws the rendered scene to the screen using the attatched shader for a post-process
void RenderBuffer::DrawToQuad(GLsizei _x, GLsizei _y)
{
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (genSuccessfully && (shader.get() != NULL))
  {
    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //Rendering to the screen now
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, _x, _y);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    shader->Activate();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(shader->programID, "texColour"), 0);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, depthBufferID);
    glUniform1i(glGetUniformLocation(shader->programID, "texDepth"), 1);

    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
}