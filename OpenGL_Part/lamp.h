#ifndef LAMP_H
#define LAMP_H

#include "object_renderer.h"
#include <glm/glm.hpp>


class Lamp {
public:
  Lamp(glm::vec3 pos, glm::vec3 siz = glm::vec3(1.0f), glm::vec4 col = glm::vec4(1.0f));
  Lamp() {};
  void draw(ObjectRenderer *renderer);
  glm::vec3 position;
  glm::vec3 size;
  glm::vec4 color;

};

#endif // !LAMP_J