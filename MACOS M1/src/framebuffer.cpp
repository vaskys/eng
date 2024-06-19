#include "framebuffer.h"
#include "SDL_opengl.h"
#include "engine.h"

FrameBuffer::FrameBuffer(int w_i,int h_i,bool depth)
{
  glGenFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER,id);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,w_i,h_i, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

  if(depth) {
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w_i, h_i, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,depth_texture, 0);
  }
  else {
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, gin_get_screen_w(),gin_get_screen_h());  
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  w = w_i;
  h = h_i;
}

FrameBuffer::~FrameBuffer()
{
  clear();
  debug_print("FBO KILL");
}


void FrameBuffer::clear()
{
  glDeleteFramebuffers(1, &id);
  glDeleteTextures(1,&texture);
  glDeleteRenderbuffers(1,&rbo);
}


int FrameBuffer::get_w() {
  return w;
}

int FrameBuffer::get_h() {
  return h;
}

int FrameBuffer::get_id() {
  return id;
}
