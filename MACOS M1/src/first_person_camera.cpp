#include "first_person_camera.h"
#include "SDL_mouse.h"
#include "SDL_stdinc.h"
#include "abs_sdl.h"
#include "engine.h"


FirstPersonCamera::FirstPersonCamera(float aspect_ratio,float fov,float z_near,float z_far) : Camera(aspect_ratio,fov,z_near,z_far)
{
  yaw   = -90.0f;
  pitch =  0.0f;
  lastX =  gin_get_screen_w() / 2.0;
  lastY =  gin_get_screen_h() / 2.0;
  fov   =  45.0f;
  c_lock = false;

  float lastX = 0;
  float lastY = 0;
}


FirstPersonCamera::~FirstPersonCamera()
{
}


void FirstPersonCamera::update()
{
  Camera::update();
  controls();
}

void FirstPersonCamera::controls()
{
  c_lock = true;
  if(abs_sdl::sdl_is_key_pressed_event(119))
  {
    set_position(get_position()+get_direction()*5.1f * gin_get_delta_time());
  }
  else if(abs_sdl::sdl_is_key_pressed_event(97))
  {
    set_position(get_position()-glm::normalize(glm::cross(get_direction(),get_up()))*5.1f * gin_get_delta_time());
  }
  else if(abs_sdl::sdl_is_key_pressed_event(100))
  {
    set_position(get_position()+glm::normalize(glm::cross(get_direction(),get_up()))*5.1f * gin_get_delta_time());
  }
  else if(abs_sdl::sdl_is_key_pressed_event(115))
  {
    set_position(get_position()-get_direction()*5.1f * gin_get_delta_time());
  }


  if(abs_sdl::sdl_is_key_pressed_event(121))
   c_lock = false;

  SDL_ShowCursor(true);
  if(!c_lock) {
    float xoffset = abs_sdl::sdl_get_mouse_x()- lastX;
    float yoffset = lastY - abs_sdl::sdl_get_mouse_y(); 
    lastX = abs_sdl::sdl_get_mouse_x();
    lastY = abs_sdl::sdl_get_mouse_y();

    float sensitivity = 0.4f;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    SDL_ShowCursor(false);
  }
  else{
    lastX = abs_sdl::sdl_get_mouse_x();
    lastY = abs_sdl::sdl_get_mouse_y();
  }

  if(pitch > 89.0f)
    pitch = 89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 smer;
  smer.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  smer.y = sin(glm::radians(pitch));
  smer.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  set_direction(glm::normalize(smer));
}

