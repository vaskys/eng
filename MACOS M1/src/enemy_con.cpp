#include "enemy_con.h"
#include "LinearMath/btVector3.h"
#include "config.h"
#include "engine.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "player_con.h"
#include <__fwd/get.h>
#include <string>

EnemyCon::EnemyCon() {
  attack = false;
  pohyb = glm::vec3(0.0f);
  speed = 100.0f;
  dir = glm::vec3(0,3.1f,1.0f);
  status = 0;
  random_idle = rand()%3;
  random_attack = rand()%2;
  hp = 3;
  a= 0.0f;
}

EnemyCon::~EnemyCon() {
  Controler::clear();
}

void EnemyCon::init() {
  main = (FNode*)master;

  main->get_obj()->setAngularFactor(btVector3(0,0,0));

  m_node = (ModelNode*)main->get_children().at(0);

  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/idle.fbx"),"idle");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/growl.fbx"),"idle_dva");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/run.fbx"),"run");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/attack_jedna.fbx"),"attack_jedna");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/attack_dva.fbx"),"attack_dva");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/idle_tri.fbx"),"idle_tri");
  m_node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/enemy/death.fbx"),"death");


  target = (FNode*)gin_get_active_scene()->get_child("player");
  target_con = (PlayerCon*)target->get_controler();



}

void EnemyCon::update() {
  main->get_obj()->activate(true);
  pohyb=glm::vec3(0,0,0);

  btQuaternion o=main->get_obj()->getOrientation();
  glm::quat rot=glm::quat(); 
  rot.x=o.getX();
  rot.y=o.getY();
  rot.z=o.getZ();
  rot.w=o.getW();

  float distance = glm::distance(target->get_transform().get_position() , main->get_transform().get_position());
  if(distance <= 1.0f && status == 0) {
    status = 1;
  }

  if(!gin_get_editor_status()) {
    if(status == 0) {
      if(!m_node->get_animator()->is_playing()) {
        random_idle = rand()%3;
        if(random_idle == 0)
          m_node->get_animator()->play("idle", false);
        else if(random_idle == 1)
          m_node->get_animator()->play("idle_dva", false);
        else
          m_node->get_animator()->play("idle_tri", false);
      }
    }

    if(status == 1) {
      if(hp <= 0) {
        status = 2;
        attack = false;
      }

      pohyb = glm::normalize( target->get_transform().get_position() -  main->get_transform().get_position() );
      if(!attack)
      {
        m_node->get_animator()->play("run", true);
        btTransform t = main->get_obj()->getWorldTransform();
        btVector3 currentForward =t.getBasis().getColumn(2).normalized();
        currentForward = btVector3(currentForward.x(),0,currentForward.z());

        btVector3 direction = btVector3(pohyb.x,0,pohyb.z);
        btQuaternion rotationQuat;
        rotationQuat.setRotation(currentForward.cross(direction), currentForward.angle(direction));
        a = rotationQuat.getAngle();


        btVector3 v = main->get_obj()->getLinearVelocity();
        main->get_obj()->setAngularVelocity(btVector3(0,a,0));
        pohyb *=speed * gin_get_delta_time();
        main->get_obj()->setLinearVelocity(btVector3(pohyb.x,v.y(),pohyb.z));
      }
      if(distance <= 1.5f) {
        attack = true;
        if(target_con->attack_status == 3) {
          btQuaternion q = ((FNode*)target)->get_obj()->getOrientation();
          btMatrix3x3 rotationMatrix(q);
          btVector3 dir = rotationMatrix.getColumn(2).normalized();
          float angle = 180 - glm::degrees(dir.angle(btVector3(pohyb.x,0,pohyb.z)));
          if(angle < 90.0f) {
            hp -=1;
          }
        }
      }
      if(attack) {
        main->get_obj()->setAngularVelocity(btVector3(0,0,0));
        if(random_attack == 0)
          m_node->get_animator()->play("attack_jedna", false);
        else
          m_node->get_animator()->play("attack_dva", false);

        if(!m_node->get_animator()->is_playing()) {
          random_attack = rand()%2;
          attack = false;
        }
      }

    }
    if(status == 2) {
      m_node->get_animator()->play("death", false);
      main->get_obj()->activate(false);
      gin_get_fworld()->get_bt_world()->removeRigidBody(main->get_obj());
    }
  }
}

void EnemyCon::clear() {
  main=nullptr;
  m_node=nullptr;
  target = nullptr;
  target_con = nullptr;
}
