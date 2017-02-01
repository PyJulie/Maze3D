#include "lamp.h"

Lamp::Lamp(glm::vec3 pos, glm::vec3 siz, glm::vec4 col):
  position(pos), size(siz), color(col){
}

void Lamp::draw(ObjectRenderer * renderer)
{
  renderer->drawLamp(position, size, color);
}
