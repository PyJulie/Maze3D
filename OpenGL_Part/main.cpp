#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"

const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;

Game findPath(WINDOW_WIDTH, WINDOW_HEIGHT);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_buttoncallback(GLFWwindow *window, int button, int action, int mode);

int main(int argc, char *argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FindPath", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();
  glGetError();//catch the errors from glewInit();

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_buttoncallback);

  GLfloat deltaTime = 0.0f;
  GLfloat lastTime = 0.0f;
  
  findPath.init();

  while (!glfwWindowShouldClose(window)) {
    GLfloat currentTime = glfwGetTime();
    //std::cout << currentTime << std::endl;
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    findPath.processInput(deltaTime);
    findPath.update();
    findPath.draw(deltaTime);

    glfwSwapBuffers(window);
  }

  ResourceManager::clear();

  glfwTerminate();
  return 0;
}        

GLboolean isPolymode = GL_FALSE;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      findPath.keys[key] = GL_TRUE;
    else if (action == GLFW_RELEASE)
      findPath.keys[key] = GL_FALSE;
  }
  
  if (key == GLFW_KEY_O && action == GLFW_PRESS) {
    if (isPolymode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    isPolymode = !isPolymode;
  }

}

GLboolean isMousePress = GL_FALSE;
GLboolean isFirstMouse = GL_TRUE;
GLfloat lastX = WINDOW_WIDTH / 2.0f;
GLfloat lastY = WINDOW_HEIGHT / 2.0f;

void mouse_buttoncallback(GLFWwindow *window, int button, int action, int mode) {
  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
      isMousePress = GL_TRUE;
  }
  if (action == GLFW_RELEASE) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
      isMousePress = GL_FALSE;
  }
  

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
  if (isFirstMouse){
    lastX = xpos;
    lastY = ypos;
    isFirstMouse = GL_FALSE;
  }

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  if (isMousePress)
    findPath.camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  findPath.camera->ProcessMouseScroll(yoffset);
}
