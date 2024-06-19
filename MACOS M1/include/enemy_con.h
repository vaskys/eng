#ifndef ENEMY_CON_H
#define ENEMY_CON_H

#include "Node.h"
#include "controler.h"
#include "fnode.h"
#include "model.h"
#include "player_con.h"

class EnemyCon : public Controler {
  public:
  EnemyCon();
  virtual ~EnemyCon();

  void init();
  void update();
  void clear();

  FNode *main;
  ModelNode *m_node;

  bool attack;
  int status;
  int random_idle;
  int random_attack;
  glm::vec3 pohyb;
  glm::vec3 dir;
  float speed;

  Node *target;
  PlayerCon *target_con;
  int hp;
  float a;
};

#endif // !ENEMY_CON_H
