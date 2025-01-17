#include "engine.h"
#include "abs_sdl.h"
#include "first_person_camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "skybox.h"

Scene *gin_active_scene;
Asset_manager *asset_manager;
Renderer *main_renderer;
Camera *main_camera;
Camera *default_cam;



Skybox *skybox;

FWorld *f_world;
bool draw_f=false;
bool update_f=true;
bool editor=false;


bool gin_get_editor_status() {
  return editor;
}

void gin_set_editor(bool v)
{
  editor=v;
  abs_sdl::set_gui(v);
}

void gin_init_default_camera()
{
  default_cam=new OrbitCamera(18.0f/9.0f,45.0f,0.1f,1000.0f);
  ((OrbitCamera*)default_cam)->look_at(glm::vec3(0.0f,0.0f,0.0f));
  default_cam->set_position(glm::vec3(0.0f,20.0f,-10.0f));
  gin_set_active_camera(default_cam);

}

void gin_set_fdraw(bool v)
{
  draw_f=v;
}

bool gin_get_fdraw()
{
  return draw_f;
}

void gin_update_active_camera()
{
  main_camera->update();
}

void gin_set_active_camera(Camera *camera)
{
  main_camera=camera;
}

Camera *gin_get_active_camera()
{
  return main_camera;
}

Camera *gin_get_default_camera()
{
  return default_cam;
}


void gin_init_renderer()
{
  main_renderer=new Renderer();
}
Renderer *gin_get_main_renderer()
{
  return main_renderer;
}

void gin_init_default_scene()
{
  gin_active_scene=new Scene("default scene");
}
void gin_set_active_scene(Scene *scene)
{
  gin_active_scene=scene;
}

Scene* gin_get_active_scene()
{
  return gin_active_scene;
}

void gin_clear_scene()
{
  gin_active_scene->clear();
}

void gin_run_active_scene()
{
  gin_active_scene->run();
}

void gin_init_asset_manager()
{
  asset_manager=new Asset_manager();
}

Asset_manager *gin_get_asset_manager()
{
  return asset_manager;
}

bool gin_init(int screenW,int screenH,string window_name,bool resize,bool fullscreen)
{

  abs_sdl::sdl_init(screenW,screenH,window_name,resize,fullscreen);
  gin_init_asset_manager();
  gin_init_renderer();

  f_world=new FWorld();

  skybox = new Skybox();
  gin_set_skybox("skybox/tri", ".png");

  gin_set_editor(false);

  gin_init_default_scene();
  gin_init_default_camera();

  return true;
}

bool gin_screen_resize()
{
  return abs_sdl::get_screen_resize();
}

int gin_get_screen_w()
{
  return abs_sdl::get_screenW();
}

int gin_get_screen_h()
{
  return abs_sdl::get_screenH();
}

void gin_clear()
{
  gin_clear_scene();
  asset_manager->clear();
  delete asset_manager;

  main_renderer->clear();
  delete main_renderer;

  //    delete main_camera;
  main_camera=nullptr;
  delete default_cam;
  delete f_world;
  delete skybox;
  abs_sdl::sdl_clear();
}



int gin_get_fps()
{
  return abs_sdl::get_fps();
}


void gin_set_vsync(bool i)
{
  abs_sdl::set_vsync(i);
}


float gin_get_delta_time()
{
  return abs_sdl::get_delta_time();
}

void gin_pool_events()
{
  abs_sdl::sdl_pool_events();
}

bool gin_is_window_close_event()
{
  return abs_sdl::sdl_is_window_close_event();
}

bool gin_is_key_pressed(int key)
{
  return abs_sdl::sdl_is_key_pressed_event(key);
}

bool gin_is_mouse_button_down(bool button)
{
  return abs_sdl::sdl_is_mouse_button_down(button);
}

bool gin_is_mouse_movement()
{
  return abs_sdl::sdl_is_mouse_movement();
}

int gin_get_mouse_x()
{
  return abs_sdl::sdl_get_mouse_x();
}

int gin_get_mouse_y()
{
  return abs_sdl::sdl_get_mouse_y();
}

int gin_get_mouse_vertical()
{
  return abs_sdl::get_mouse_vertical();
}

int gin_get_mouse_horizontal()
{
  return abs_sdl::get_mouse_horizontal();
}

void gin_update_physics() {
  if(update_f) {
    f_world->update();
  }
}

void gin_draw_physics() {
  if(draw_f) {
    f_world->draw();
  }
}

bool gin_mouse_scroll_down()
{
  return abs_sdl::mouse_scroll_down();
}

bool gin_mouse_scroll_up()
{
  return abs_sdl::mouse_scroll_up();
}

bool gin_mouse_scoll_left()
{
  return abs_sdl::mouse_scroll_left();
}

bool gin_mouse_scroll_right()
{
  return abs_sdl::mouse_scroll_right();
}


FWorld* gin_get_fworld()
{
  return f_world;
}

void gin_set_f_update(bool v)
{
  update_f=v;
  f_world->set_all_obj(v);
}

bool gin_get_f_update()
{
  return update_f;
}



bool gin_set_skybox(string path, string format) {
  return skybox->load_cubemap(path, format);
}

Skybox* gin_get_skybox() {
  return skybox;
}



void gin_trap_mouse(bool t) {
  abs_sdl::trap_mouse((SDL_bool)t);
}

float gin_get_xd() {
  return abs_sdl::get_xd();
}
