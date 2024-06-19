#include "orbit_camera.h"
#include "abs_sdl.h"
#include "engine.h"
#include <cstdlib>

OrbitCamera::OrbitCamera(float aspect_ratio,float fov,float z_near,float z_far) : Camera(aspect_ratio,fov,z_near,z_far)
{
    rotation=glm::vec3(1.0f);
    v=0;
    h=0;
    radius=10.0f;

    float lastX = 0;
    float lastY = 0;
}

OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::look_at(glm::vec3 t)
{
    target=t;
}

void OrbitCamera::update()
{
    controls();

    rotation.x= sin(h) *radius;
    rotation.z= cos(h) *radius;
    rotation.y= sin(v)*radius;

    glm::vec3 p=glm::vec3(rotation.x,-rotation.y,rotation.z)+target;
    set_position(p);

    glm::vec3 smer=target-get_position();
    smer=glm::normalize(smer);

    set_direction(smer);
    Camera::update();
}

void OrbitCamera::controls()
{
    if(abs_sdl::sdl_is_key_pressed_event(102))
    {
        if(abs_sdl::mouse_scroll_down())
        {
            radius-=10.0f * gin_get_delta_time();
        }
        else if(abs_sdl::mouse_scroll_up())
        {
            radius+=10.0f * gin_get_delta_time();
        }
    }
    else
    {
        if(abs_sdl::sdl_is_mouse_button_down(0)) {
            float m_h = abs_sdl::get_mouse_horizontal();
            float m_v = abs_sdl::get_mouse_vertical();
            h-=m_h * gin_get_delta_time();
            v-=m_v * gin_get_delta_time();
        }
        if(abs_sdl::mouse_scroll_right())
            h+=8.1f * gin_get_delta_time();
        else if(abs_sdl::mouse_scroll_left())
            h-=8.1f * gin_get_delta_time();
        if(abs_sdl::mouse_scroll_up())
            v+=8.1f * gin_get_delta_time();
        else if(abs_sdl::mouse_scroll_down())
            v-=8.1f * gin_get_delta_time();
    }

    if(abs_sdl::sdl_is_key_pressed_event(106))
    {
        target+= get_direction() * abs_sdl::get_delta_time() * 2.0f;
    }
    else if(abs_sdl::sdl_is_key_pressed_event(107))
        target-= get_direction() * abs_sdl::get_delta_time() * 2.0f;

    
}

void OrbitCamera::null_v() {
  v = 0;
}



void OrbitCamera::set_radius(float r) {
  radius = r;
}

float OrbitCamera::get_radius() {
  return radius;
}
