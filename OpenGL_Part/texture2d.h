#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <gl/glew.h>

class Texture2D {
public:
  Texture2D();
  void generate(GLuint wid, GLuint hei, unsigned char* data);
  void bind() const;

  GLuint ID;
  GLuint width, height;
  GLuint internal_format; //Format of texture object
  GLuint image_format;   //Format of loaded Image
  GLuint wrap_s;
  GLuint wrap_t;
  GLuint filter_min;
  GLuint filter_max;
};


#endif // ! TEXTURE2D_H
