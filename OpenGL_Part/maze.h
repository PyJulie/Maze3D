#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

#include "texture2d.h"
#include "object_renderer.h"
#include "lamp.h"

//enum objectType {
//  WALL,
//  ROAD
//};

struct Object {
  Object(Texture2D imag, Texture2D imagShader, glm::vec3 pos, glm::vec3 siz, glm::vec4 col): 
    image(imag), imageShader(imagShader), position(pos), size(siz), color(col){}
  Object(){}
  void draw(ObjectRenderer *renderer) {
    renderer->drawObject(image, imageShader, position, size, color);
  }

  Texture2D image;
  Texture2D imageShader;
  glm::vec3 position;
  glm::vec3 size;
  glm::vec4 color;
};

class Maze {
public:
  Maze();

  void loadMazeFromFile(const char* file);
  void loadPathFromFile(const char* file);
  void draw(ObjectRenderer *renderer);
  void animation(ObjectRenderer *renderer, GLfloat dt);

  Lamp firstLamp;
  GLuint mazeWidth;
  GLuint mazeHeight;
private:
  std::vector<Object> objects;
  std::vector<glm::vec2> path;
  void initData(std::vector<std::vector<GLuint>> data);

  ///*temp*/
  //Object start, end;
  ////
};

#endif // !MAZE_H