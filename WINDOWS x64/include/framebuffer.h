#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "config.h"

class FrameBuffer
{
public:
  FrameBuffer(int w_i,int h_i,bool depth);
  ~FrameBuffer();

  int w;
  int h;

  unsigned int id;
  unsigned int texture;
  unsigned int rbo;
  unsigned int depth_texture;

  void clear();

  int get_w();
  int get_h();
  int get_id();
};

#endif
