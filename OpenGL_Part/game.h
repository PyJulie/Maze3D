#ifndef  GAME_H
#define GAME_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>
    
#include "Camera.h"
#include "maze.h"
#include "lamp.h"
#include "Model.h"

enum ANIMATION_STATE {                                                                  
  ANIMATION_ACTIVE,
  ANIMATION_END
};

class Game {
public:
  Game(GLuint w, GLuint h);
  ~Game();

  void init();
  void processInput(GLfloat dt);
  void update();;
  void draw(GLfloat dt);

  GLuint width;
  GLuint height;
  GLboolean keys[1024];
  ANIMATION_STATE state;

  Camera *camera;
};

#endif // ! GAME_H