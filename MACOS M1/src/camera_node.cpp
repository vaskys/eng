#include "engine.h"
#include "camera_node.h"
#include "first_person_camera.h"

CameraNode::CameraNode(string n) : Node(n)
{
  camera=new FirstPersonCamera(18.0f/9.0f,45.0f,0.1f,1000.0f); 
  can_modify=true;
  inherit_t=true;
}

CameraNode::~CameraNode()
{
  delete camera;
}

void CameraNode::update()
{
  Node::update();
  // camera->set_position(get_transform().get_position_global());
  // glm::vec3 euler=get_transform().get_euler();
  // camera->set_euler(get_transform().get_euler_global());
  //

  if(dirty) {
    Transform p = this->get_transform();
    glm::vec3 pt = p.get_position();
    glm::vec3 euler = p.get_euler();
    camera->set_position(pt);
    camera->set_euler(euler);
    dirty = false;
  }

  Transform t;
  glm::vec3 pos = camera->get_position();
  t.set_local_transform(pos,glm::vec3(1.0f),glm::vec3(0.0f));
  this->set_transform(t);


  
  gin_get_active_scene()->cameras.push_back(this);
}

Camera*CameraNode::get_camera()
{
  return camera;
}


void CameraNode::copy(Node *target)
{
  Node *nova=new CameraNode(get_name());
  nova->set_transform(get_transform());
  target->add_child(nova);

  for(int i=0;i<get_children().size();i++)
  {
    Node *decko=get_children().at(i);
    decko->copy(nova);
  }
}


