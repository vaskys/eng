#include "engine.h"
#include "glm/fwd.hpp"
#include "model_node.h"
#include "player_con.h"
#include "enemy_con.h"
void demo_gr()
{
    gin_init(1280, 720, "test", true, false);
    gin_set_editor(false);
    gin_set_f_update(false);
    gin_set_fdraw(false);

    gin_get_active_scene()->load("gr.txt");

    Camera* node = gin_get_active_scene()->cameras.at(0)->get_camera();
    gin_set_active_camera(node);

    gin_run_active_scene();
    gin_clear();
}

void demo_volume() {
    gin_init(1280, 720, "test", true, false);
    gin_set_editor(false);
    gin_set_f_update(false);
    gin_set_fdraw(false);

    gin_get_active_scene()->load("volume.txt");

    Camera* node = gin_get_active_scene()->cameras.at(0)->get_camera();
    gin_set_active_camera(node);

    gin_run_active_scene();
    gin_clear();
}


void editor()
{
    gin_init(1280, 720, "test", true, false);
    gin_set_editor(true);
    gin_set_f_update(false);
    gin_set_fdraw(false);


    gin_get_asset_manager()->load_model("models/rock/rock.obj");

    // gin_get_asset_manager()->load_model("models/char/main.fbx");
    // gin_get_asset_manager()->load_model("models/knight/knight.fbx");
    //
    // gin_get_asset_manager()->load_animation("models/char/idle.fbx", "models/char/main.fbx");
    // gin_get_asset_manager()->load_animation("models/knight/test.fbx", "models/knight/knight.fbx");
    //
    // gin_get_active_scene()->add_model_node("models/char/main.fbx");
    // gin_get_active_scene()->add_model_node("models/knight/knight.fbx");
    //
    // ModelNode *node = (ModelNode*)gin_get_active_scene()->get_child("models/char/main.fbx");
    // node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/char/idle.fbx"), "idle");
    //
    // node->get_animator()->play("idle", true);
    // 
    //
    // node = (ModelNode*)gin_get_active_scene()->get_child("models/knight/knight.fbx");
    // node->get_animator()->add_animation(gin_get_asset_manager()->get_animation("models/knight/test.fbx"), "idle");
    //
    // node->get_animator()->play("idle", true);


    gin_get_active_scene()->add_model_node("models/kocka/neviem.fbx");
    gin_get_active_scene()->add_camera_node();


    gin_get_active_scene()->env.set_global_light_status(true);
    gin_get_active_scene()->add_empty();
    gin_get_active_scene()->add_empty();
    gin_get_active_scene()->add_empty();


    gin_run_active_scene();
    gin_clear();

}

void demo() {
    gin_init(1280, 720, "test", true, false);
    gin_set_editor(false);
    gin_set_f_update(true);
    gin_set_fdraw(false);

    gin_get_active_scene()->load("demo.txt");


    gin_get_asset_manager()->load_animation("models/enemy/idle.fbx", "models/enemy/enemy.fbx");
    gin_get_asset_manager()->load_animation("models/enemy/growl.fbx", "models/enemy/enemy.fbx");
    gin_get_asset_manager()->load_animation("models/enemy/run.fbx", "models/enemy/enemy.fbx");
    gin_get_asset_manager()->load_animation("models/enemy/attack_jedna.fbx", "models/enemy/enemy.fbx");
    gin_get_asset_manager()->load_animation("models/enemy/attack_dva.fbx", "models/enemy/enemy.fbx");
    gin_get_asset_manager()->load_animation("models/enemy/idle_tri.fbx", "models/enemy/enemy.fbx");
    gin_get_asset_manager()->load_animation("models/enemy/death.fbx", "models/enemy/enemy.fbx");

    gin_get_active_scene()->get_child("player")->set_controler(new PlayerCon());

    Node* n = gin_get_active_scene()->get_child("enemies");
    for (int i = 0; i < n->get_children().size(); i++) {
        Node* child = n->get_children().at(i);
        child->set_controler(new EnemyCon());
    }

    gin_get_active_scene()->init_con();

    gin_run_active_scene();
    gin_clear();
}

int wmain()
{
    editor();
    // demo_gr();
    // demo_volume();
    // demo();
    return 0;
}





