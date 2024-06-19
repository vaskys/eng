#include "player_con.h"
#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"
#include "SDL_scancode.h"
#include "config.h"
#include "engine.h"
#include "glm/geometric.hpp"
#include "orbit_camera.h"
#include <cstdlib>
#include <string>


float distance_test = 0;
btVector3 hit = btVector3(0,0,0);

bool ray_cast(btDynamicsWorld* world, const btVector3& start, const btVector3& end,btCollisionObject *target) {
  btCollisionWorld::ClosestRayResultCallback ray_call_back(start,end);
  world->rayTest(start, end,ray_call_back);

  if(ray_call_back.hasHit()) {
    hit = ray_call_back.m_hitPointWorld;
    distance_test = start.distance(hit);


    return true;
  }

  return false;
}


PlayerCon::PlayerCon()
{
  attack=false;
  pohyb=glm::vec3(0,0,0);
  speed=200.0f;
  dir=glm::vec3(0,3.1f,1);

  sprint = false;
  radius = 5.0f;

  random_idle = 0;
  attack_type = 0;
  y_rot = 0;

  attack_status = 0;
}

PlayerCon::~PlayerCon()
{
  Controler::clear();
}

void PlayerCon::init()
{
  main=(FNode*)gin_get_active_scene()->get_child("player");    
  main->get_obj()->setAngularFactor(btVector3(0,0,0));
  m_node=(ModelNode*)main->get_children().at(0);

  gin_get_asset_manager()->load_animation("models/knight/idle.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/walk.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/cuvaj.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/run.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/idle_dva.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/idle_tri.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/test.fbx","models/knight/knight.fbx");
  gin_get_asset_manager()->load_animation("models/knight/heavy.fbx","models/knight/knight.fbx");

  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/idle.fbx"),"idle");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/walk.fbx"),"walk");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/cuvaj.fbx"),"back");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/run.fbx"),"run");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/idle_dva.fbx"),"idle_dva");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/idle_tri.fbx"),"idle_tri");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/test.fbx"),"attack_jedna");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/heavy.fbx"),"attack_dva");
}


void PlayerCon::update()
{


  main->get_obj()->activate(true);
  main->get_obj()->setAngularVelocity(btVector3(0,0,0));            

  pohyb=glm::vec3(0,0,0);

  btQuaternion o=main->get_obj()->getOrientation();
  glm::quat rot=glm::quat(); 
  rot.x=o.getX();
  rot.y=o.getY();
  rot.z=o.getZ();
  rot.w=o.getW();

  y_rot = rot.y;

  if(!gin_get_editor_status() && !attack)
  {
    if(attack_status == 3)
      attack_status = 0;
    sprint = false;
    speed = 200.0f;
    if(gin_is_key_pressed(32)) {
      sprint = true;
    }
    if(gin_is_key_pressed(119))
    {

      if(sprint) {
        speed = 400.0f;
        m_node->get_animator()->play("run",true);
      }
      else
        m_node->get_animator()->play("walk",true);
      pohyb=rot*dir * speed * gin_get_delta_time();
    }
    else if(gin_is_key_pressed(115))
    {
      m_node->get_animator()->play("back",true);
      pohyb=rot*(-dir) * speed * gin_get_delta_time();
    }
    else
    {

      if(random_idle == 0)
        m_node->get_animator()->play("idle",false);
      else if(random_idle == 1)
        m_node->get_animator()->play("idle_dva",false);
      else
        m_node->get_animator()->play("idle_tri",false);
      if(!m_node->get_animator()->is_playing()) {
        random_idle = rand()%3;
      }
    }

    if(gin_is_key_pressed(97))
    {
      main->get_obj()->setAngularVelocity(btVector3(0,1,0) * speed * gin_get_delta_time());            
    }
    else if(gin_is_key_pressed(100))
    {
      main->get_obj()->setAngularVelocity(btVector3(0,-1,0) * speed * gin_get_delta_time());            
    }

    if(gin_is_mouse_button_down(1)) {
      attack = true;
    }
  }
  if(attack) {
    attack_status = 1;
    if(attack_type < 7) {
      m_node->get_animator()->play("attack_jedna", false);
    }
    else if(attack_type >= 7){
      m_node->get_animator()->play("attack_dva", false);
    }
    if(!m_node->get_animator()->is_playing()) {
      attack_type = rand()%10;
      attack = false;
      attack_status = 3;
    }
  }
  btVector3 v = main->get_obj()->getLinearVelocity();
  main->get_obj()->setLinearVelocity(btVector3(pohyb.x,v.y(),pohyb.z));

  camera_controls();
}

void PlayerCon::clear()
{
  main=nullptr;
  m_node=nullptr;
}

void PlayerCon::camera_controls() {

  radius = ((OrbitCamera*)gin_get_default_camera())->get_radius();
  if(radius > 5) radius = 5.0f;

  gin_get_default_camera()->look_at(main->get_transform().get_position_global());

  glm::vec3 cam_pos = gin_get_default_camera()->get_position() - glm::normalize(gin_get_default_camera()->get_direction() * glm::vec3(2.0f));
  glm::vec3 player_pos = main->get_transform().get_position();
  btVector3 end(cam_pos.x,cam_pos.y,cam_pos.z);
  btVector3 start(player_pos.x,player_pos.y,player_pos.z);


  if(ray_cast(gin_get_fworld()->get_bt_world(),start,end,main->get_obj())) {
    if(distance_test <= 5.0f)
      radius = distance_test - 0.4f;

  //  cout<<distance_test<<" "<<radius<<endl;
  }
  else {
    if(radius < 5.0f) {
      radius +=1.0 * gin_get_delta_time();
    }
  }
  ((OrbitCamera*)gin_get_default_camera())->set_radius(radius);
}
