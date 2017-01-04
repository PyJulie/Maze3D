#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture2d.h"
#include "shader.h"

class ObjectRenderer {
public:
  ObjectRenderer(const Shader &shader);
  ~ObjectRenderer();
  void drawObject(Texture2D &texture, Texture2D & texShader, glm::vec3 position, glm::vec3 size = glm::vec3(10), glm::vec4 color = glm::vec4(1.0f));
  void drawLamp(glm::vec3 position, glm::vec3 size = glm::vec3(1.0f), glm::vec4 color = glm::vec4(1.0f));
private:
  Shader shader;
  GLuint cubeVAO;
  GLuint lampVAO;
  void initData();
};



#endif // !OBJECT_RENDER_H