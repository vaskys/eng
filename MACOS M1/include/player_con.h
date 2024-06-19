#ifndef PLAYER_CON_H
#define PLAYER_CON_H

#include "controler.h"
#include "fnode.h"
#include "model_node.h"

class PlayerCon : public Controler
{
public:
  PlayerCon();
  virtual ~PlayerCon();


  void init();
  void update();
  void clear();


  FNode *main;
  ModelNode *m_node;

  bool attack;
  int attack_type;
  int random_idle;

  glm::vec3 pohyb;
  glm::vec3 dir;
  float speed;

  bool sprint;

  float radius;

  float y_rot;

  int attack_status;


  void camera_controls();

};

#endif
