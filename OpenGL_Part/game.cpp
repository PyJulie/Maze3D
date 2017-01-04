#include "game.h"
#include "resource_manager.h"
#include "object_renderer.h"

/*temp*/
#include <iostream>
/*temp*/

ObjectRenderer *objectRenderer;
ObjectRenderer *lampRenderer;
Maze maze;
Lamp *lamp;
Model *shitai;

glm::vec3 LAMP_POS(10.0f, 1.0f, 10.0f);
glm::vec3 LAMP_AMBIENT(0.8f, 0.8f, 0.8f);
glm::vec3 LAMP_DIFFUSE(0.8f, 0.8f, 0.8f);
glm::vec3 LAMP_SPECULAR(1.0f, 1.0f, 1.0f);

GLfloat LAMP_CONSTANT = 1.0f;
GLfloat LAMP_LINEAR = 0.00025f;
GLfloat LAMP_QUADRATIC = 0.0015f;
GLfloat MATERIAL_SHININESS = 64.0f;

Game::Game(GLuint w, GLuint h): width(w), height(h), state(ANIMATION_END)
{
}

Game::~Game() 
{
  delete objectRenderer;
  delete lampRenderer;
  delete camera;
  delete lamp;
  delete shitai;
}

void Game::init()
{
  ResourceManager::loadShader("object", "shaders/object.vx", "shaders/object.frag");
  ResourceManager::loadShader("lamp", "shaders/lamp.vx", "shaders/lamp.frag");
  ResourceManager::loadShader("model", "shaders/model_loading.vx", "shaders/model_loading.frag");

  ResourceManager::loadTexture("particle", "textures/particle.png", GL_TRUE);
  ResourceManager::loadTexture("wall", "textures/wall.png");
  ResourceManager::loadTexture("wallShader", "textures/wallShader.png");  
  ResourceManager::loadTexture("road", "textures/road.png");
  
 

  ResourceManager::getShader("object").use().setInteger("material.diffuse", 0);    
  ResourceManager::getShader("object").use().setInteger("material.specular", 1);
  ResourceManager::getShader("object").use().setFloat("material.shininess", MATERIAL_SHININESS);
  ResourceManager::getShader("object").use().setVector3f("light.ambient", LAMP_AMBIENT);
  ResourceManager::getShader("object").use().setVector3f("light.diffuse", LAMP_DIFFUSE);
  ResourceManager::getShader("object").use().setVector3f("light.specular", LAMP_SPECULAR);
  ResourceManager::getShader("object").use().setFloat("light.constant", LAMP_CONSTANT);
  ResourceManager::getShader("object").use().setFloat("light.linear", LAMP_LINEAR);
  ResourceManager::getShader("object").use().setFloat("light.quadratic", LAMP_QUADRATIC);
  //ResourceManager::getShader("object").use().setVector3f("light.position", LAMP_POS);


  maze.loadMazeFromFile("maze/maze.mz");
  maze.loadPathFromFile("maze/path.pt");

  objectRenderer = new ObjectRenderer(ResourceManager::getShader("object"));
  lampRenderer = new ObjectRenderer(ResourceManager::getShader("lamp"));
  lamp = new Lamp(LAMP_POS);
  shitai = new Model("./objModel/shitai/shitai.obj");
  this->camera = new Camera(glm::vec3(7.0f, 0.0f, 30.0f));

  /*temp*/
  GLint w = maze.mazeWidth;
  GLint h = maze.mazeHeight;
  std::cout << w << " " << h << std::endl;
  glm::mat4 model;
  model = glm::translate(model, glm::vec3(w*0.4f, -w*0.2f, h*0.4f)); 
  model = glm::scale(model, glm::vec3(w*0.001f, w*0.001f, h*0.001f));
  ResourceManager::getShader("model").use().setMatrix4f("model", model);
  /*temp*/

}

void Game::processInput(GLfloat dt)
{
  ResourceManager::getShader("object").use().setVector3f("viewPos", camera->Position);
  ResourceManager::getShader("object").use().setMatrix4f("view", camera->getViewMatrix());
  ResourceManager::getShader("object").use().setMatrix4f("projection", glm::perspective(camera->Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f));
  ResourceManager::getShader("object").use().setVector3f("light.position", maze.firstLamp.position);
  ResourceManager::getShader("lamp").use().setMatrix4f("view", camera->getViewMatrix());
  ResourceManager::getShader("lamp").use().setMatrix4f("projection", glm::perspective(camera->Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f));
  ResourceManager::getShader("model").use().setMatrix4f("view", camera->getViewMatrix());
  ResourceManager::getShader("model").use().setMatrix4f("projection", glm::perspective(camera->Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f));



  if (keys[GLFW_KEY_W])
    camera->ProcessKeyboard(FORWARD, dt);
  if (keys[GLFW_KEY_S])
    camera->ProcessKeyboard(BACKWARD, dt);
  if (keys[GLFW_KEY_A])
    camera->ProcessKeyboard(LEFT, dt);
  if (keys[GLFW_KEY_D])
    camera->ProcessKeyboard(RIGHT, dt);
  if (keys[GLFW_KEY_E])
    camera->ProcessKeyboard(UP, dt);
  if (keys[GLFW_KEY_Q])
    camera->ProcessKeyboard(DOWN, dt);
  if (keys[GLFW_KEY_SPACE])
    state = ANIMATION_ACTIVE;

}

void Game::update()
{
}

void Game::draw(GLfloat dt)
{
  //lamp->draw(lampRenderer);

  maze.draw(objectRenderer);
  shitai->Draw(ResourceManager::getShader("model"));
  
  if (state == ANIMATION_ACTIVE)
    maze.animation(lampRenderer, dt);
  
}

