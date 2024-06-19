#include "config.h"
#include "depth_map.h"


DepthMap::DepthMap(int screenW,int screenH) {
  texture_id = 0;
  glGenFramebuffers(1, &id);  
  glGenTextures(1, &texture_id);

  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenW, screenH, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
  float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  


  glBindFramebuffer(GL_FRAMEBUFFER,id);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_id, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);  


  w = screenW;
  h = screenH;

}


DepthMap::~DepthMap() {
  clear();
}

int DepthMap::get_w() {
  return w;
}

int DepthMap::get_h() {
  return h;
}


void DepthMap::clear() {
  glDeleteFramebuffers(1, &id);
  glDeleteTextures(1, &texture_id);
}


unsigned int DepthMap::get_id() {
  return id;
}

unsigned int DepthMap::get_texture_id() {
  return texture_id;
}


