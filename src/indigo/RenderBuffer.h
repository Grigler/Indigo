#ifndef __IND_RENDER_BUFFER__
#define __IND_RENDER_BUFFER__

#include <GL/glew.h>

#include <memory>

namespace Indigo
{
  class Shader;

  class RenderBuffer
  {
    //Can only be used by the camera component
    //avoids a dev from breaking the post-process shading
    friend class Camera;
  private:
    //Init func to generate buffers and bind
    void GenBuffers(GLsizei _x, GLsizei _y);
    void GenQuadVAO();

    //Generates a new drawing texture and alters view-port size
    void ReSize(GLsizei _x, GLsizei _y);
    void Bind();

    void AttachShader(std::shared_ptr<Shader> _shader);

    void DrawToQuad(GLsizei _x, GLsizei _y);

    GLuint frameBufferID;
    GLuint depthBufferID;
    GLuint textureID;
    GLuint quadVAO;

    std::shared_ptr<Shader> shader;

    GLsizei x, y;

    bool genSuccessfully;
  };

}

#endif