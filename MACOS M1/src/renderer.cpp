#include "renderer.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "FBOShader.h"
#include "SDL_opengl.h"
#include "SDL_timer.h"
#include "abs_sdl.h"
#include "depth_map.h"
#include "depth_shader.h"
#include "down_scale_shader.h"
#include "engine.h"
#include <string>
#include <vector>
#include "config.h"
#include "framebuffer.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "god_rays_shader.h"
#include "imgui.h"
#include "lights.h"
#include "oc_gr_shader.h"
#include "shader.h"
#include "skybox.h"
#include "up_scale_shader.h"
#include "volumetric_shader.h"

Renderer::Renderer()
{
  //   primary_shader=shader;
  meshe_to_draw.clear();
  load_shader_code();
  shadre.clear();

  main_buffer = new FrameBuffer(gin_get_screen_w(),gin_get_screen_h(),true);
  output_buffer = new FrameBuffer(gin_get_screen_w(),gin_get_screen_h(),true);
  fbo_shader = new FBOShader("shaders/fbo_vertex.glsl","shaders/fbo_fragment.glsl");

  depth_shader = new DepthShader("shaders/depth_vertex.glsl","shaders/depth_fragment.glsl");

  ocluder_god_rays_buffer = new FrameBuffer(gin_get_screen_w(),gin_get_screen_h(),false);
  ocluder_god_rays_shader = new OcGRShader("shaders/ocluder_gr_shader_vertex.glsl","shaders/ocluder_gr_shader_fragment.glsl");

  god_rays_shader = new GodRaysShader("shaders/god_rays_vertex.glsl","shaders/god_rays_fragment.glsl");
  depth_map = new DepthMap(get_global_light_shadow_res(),get_global_light_shadow_res());

  volumetric_shader = new VolumetricShader("shaders/volumetric_vertex.glsl","shaders/volumetric_fragment.glsl");
  volumetric_fb = new FrameBuffer(gin_get_screen_w() / 2,gin_get_screen_h() /2 ,false);

  down_scale_depth_buffer = new DepthMap(gin_get_screen_w() / 2, gin_get_screen_h() / 2);
  down_scale_depth_shader = new DownScaleShader("shaders/down_scale_vertex.glsl","shaders/down_scale_fragment.glsl");

  up_scale_buffer = new FrameBuffer(gin_get_screen_w(),gin_get_screen_h(),false);
  up_scale_shader = new UpScaleShader("shaders/up_scale_vertex.glsl","shaders/up_scale_fragment.glsl");

  blur_shader = new BlurShader("shaders/blur_vertex.glsl","shaders/blur_fragment.glsl");
  blur_buffer = new FrameBuffer(gin_get_screen_w() /2 , gin_get_screen_h() / 2, false);


  depth_shader_animated = new DepthShaderAnimated("shaders/depth_a_vertex.glsl","shaders/depth_fragment.glsl");

  ocluder_god_rays_shader_animated = new OcGRShaderAnimated("shaders/ocluder_vertex_animated.glsl","shaders/ocluder_gr_shader_fragment.glsl");


}

Renderer::~Renderer()
{
  delete depth_shader;

  delete ocluder_god_rays_buffer;
  delete ocluder_god_rays_shader;

  delete god_rays_shader;

  delete main_buffer;
  delete fbo_shader;
  delete output_buffer;

  delete volumetric_shader;
  delete volumetric_fb;

  delete depth_map;

  delete down_scale_depth_buffer;
  delete down_scale_depth_shader;

  delete up_scale_shader;
  delete up_scale_buffer;

  delete blur_shader;
  delete blur_buffer;

  delete depth_shader_animated;
  delete ocluder_god_rays_shader_animated;

}


void Renderer::reset() {
  meshe_to_draw.clear();
}

void Renderer::begin()
{
  // meshe_to_draw.clear();
  camera_projection=gin_get_active_camera()->get_projection_matrix();
  camera_view=gin_get_active_camera()->get_view_matrix();
  cam_pos=gin_get_active_camera()->get_position();
}


void Renderer::search_node_for_meshes(glm::mat4 glob,Model *model,MeshNode *node)
{

  for(int j=0;j<node->mesh_indices.size();j++)
  {
    MESH_T t;
    t.mesh=model->get_mesh_at_index(node->mesh_indices[j]);
    t.global_transform=glob*node->get_parent()->get_transform().get_local_tranform()*node->get_transform().get_local_tranform();
    t.has_bones=false;
    meshe_to_draw.push_back(t);
  }
}

void Renderer::search_nodes(glm::mat4 glob,Model *model,MeshNode*node)
{
  search_node_for_meshes(glob,model,node);
  for(int i=0;i<node->get_children().size();i++)
  {
    MeshNode *child=(MeshNode*)node->get_children().at(i);
    search_nodes(glob,model,child);
  }
}

void Renderer::draw(Model *model,glm::mat4 transform)
{
  Node *main=model->get_root_node();
  for(int i=0;i<main->get_children().size();i++)
  {
    search_nodes(transform,model,(MeshNode*)main->get_children().at(i));
  }
}

void Renderer::draw(MeshNode *node)
{
  Model *model=node->model_node->model;

  for(int i=0;i<node->mesh_indices.size();i++)
  {
    MESH_T t;
    t.mesh=model->get_mesh_at_index(node->mesh_indices[i]);
    t.global_transform=node->get_transform().get_global_transform();
    t.has_bones=node->model_node->has_bones();
    t.animator=node->model_node->get_animator();
    meshe_to_draw.push_back(t);
  }
}

void find_closes_lights(Scene *scene,DefaultShader*shader,glm::mat4 transform)
{
  glm::vec3 pos=transform[3];
  glm::vec3 global_light_pos;

  Env env=scene->env;
  vector<pair<float,int>> v_s;

  for(int i=0;i<env.get_lights().size();i++)
  {
    global_light_pos=env.get_lights().at(i)->get_transform().get_global_transform()[3];
    float d=glm::distance(pos,global_light_pos);
    v_s.push_back(make_pair(d,i));
  }
  sort(v_s.begin(),v_s.end());

  int size=v_s.size();
  if(size > 4)
    size=4;

  shader->send_global_light_color(env.get_global_light_color());
  shader->send_global_light_dir(env.get_global_light_dir());
  shader->send_global_light_status(env.get_global_light_status());

  shader->send_lights_pocet(size);
  for(int i=0;i<size;i++)
  {

    int index=v_s[i].second;
    global_light_pos=env.get_lights().at(index)->get_transform().get_global_transform()[3]; 

    shader->send_light_pos(global_light_pos,i);
    shader->send_light_color(env.get_lights().at(index)->get_diff_farba(),i);
    shader->send_light_sila(env.get_lights().at(index)->get_sila(),i);
    shader->send_light_ambient(env.get_lights().at(index)->get_ambient(),i);
  }


  vector<pair<float,int>> spot_s;
  for(int i=0;i<env.get_spot_lights().size();i++)
  {
    global_light_pos=env.get_spot_lights().at(i)->get_transform().get_global_transform()[3];
    float d=glm::distance(pos,global_light_pos);
    spot_s.push_back(make_pair(d,i));
  }

  sort(spot_s.begin(),spot_s.end());

  size=spot_s.size();
  if(size > 4)
    size=4;

  shader->send_spot_lights_pocet(size);
  for(int i=0;i<size;i++)
  {

    int index=spot_s[i].second;
    global_light_pos=env.get_spot_lights().at(index)->get_transform().get_position();

    shader->send_spot_light_pos(global_light_pos,i);
    shader->send_spot_light_color(env.get_spot_lights().at(index)->get_diff_farba(),i);
    shader->send_spot_light_sila(env.get_spot_lights().at(index)->get_sila(),i);
    shader->send_spot_lights_cut_off(env.get_spot_lights().at(index)->get_cut_off(),i);
    shader->send_spot_lights_dir(env.get_spot_lights().at(index)->get_direction(),i);
    shader->send_spot_lights_ambient(env.get_spot_lights().at(index)->get_ambient(), i);
    shader->send_spot_lights_bias(env.get_spot_lights().at(index)->get_bias(), i);

    shader->send_spot_lights_shadow_map(env.get_spot_lights().at(index)->get_depth_map()->get_texture_id(), i);
    shader->send_spot_lights_light_space_matrix(env.get_spot_lights().at(index)->get_light_space(), i);
  }

}


void Renderer::end()
{
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 


  filter();
  Scene *scene=gin_get_active_scene();

  for(auto s : shadre)
  {
    s.second->use();
    s.second->send_projection_uniform(camera_projection);
    s.second->send_view_uniform(camera_view);
    s.second->send_camera_pos_uniform(cam_pos);


    s.second->send_global_light_space_matrix_uniform(scene->env.get_global_light_space_matrix());
    s.second->send_global_depth_map(depth_map->get_texture_id());
    s.second->send_global_light_ambient(scene->env.get_global_light_ambient());

    s.second->send_fog_type(scene->env.get_fog_type());
    s.second->send_fog_status(scene->env.get_fog_status());
    s.second->send_fog_color(scene->env.get_fog_color());
    s.second->send_fog_start(scene->env.get_fog_start());
    s.second->send_fog_end(scene->env.get_fog_end());
    s.second->send_fog_density(scene->env.get_fog_density());

    for(int i=0;i<s.second->get_meshe().size();i++)
    {
      if(s.first == 3 || s.first == 2 || s.first== 5 || s.first==6)
        find_closes_lights(scene,s.second,s.second->get_meshe().at(i)->global_transform);
      if(s.first == 1 || s.first == 3)
      {
        //textury
      }
      push(*s.second->get_meshe().at(i),s.second);
    }

    //debug_print(to_string(s.second->get_meshe().size()));

  }

  draw_skybox();
}

void Renderer::filter()
{
  for(auto s : shadre)
  s.second->clear_meshe();

  for(int i=0;i<meshe_to_draw.size();i++)
  {
    int shader_hodnota=meshe_to_draw.at(i).mesh->get_material()->get_shader_hodnota();
    bool has_bones=meshe_to_draw.at(i).has_bones;
    string vertex_prefix="#version 330 core \n";
    if(has_bones)
    {
      if(shader_hodnota == 1)
        shader_hodnota=4;
      else if(shader_hodnota  == 2)
        shader_hodnota = 5;
      else if(shader_hodnota == 3 )
        shader_hodnota=6;
      vertex_prefix+="#define ma_kosti \n";
    }

    if(!shadre.count(shader_hodnota))
    {
      string fragment_prefix=meshe_to_draw.at(i).mesh->get_material()->get_shader_prefix_fragment();
      generate_shader(shader_hodnota,vertex_prefix,fragment_prefix);
    }

    DefaultShader*shader=shadre.at(shader_hodnota);
    shader->add_mesh(&meshe_to_draw.at(i));
  }
}

void Renderer::push(MESH_T t,DefaultShader*shader)
{
  if(t.has_bones)
  {
    for(int i=0;i<t.animator->get_final_bones_transform().size();i++)
    {
      shader->send_bone_transform(t.animator->get_final_bones_transform().at(i),i);
    }
  }

  shader->send_model_uniform(t.global_transform);
  shader->send_diffuse_color_uniform(t.mesh->get_material()->get_color_diffuse());
  shader->send_diffuse_texutre_uniform(t.mesh->get_material()->get_texture_diffuse());

  shader->send_specular_color_uniform(t.mesh->get_material()->get_color_specular());
  shader->send_specular_color_power_uniform(t.mesh->get_material()->get_color_specular_power());

  glBindVertexArray(t.mesh->get_VAO());
  glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
  t.mesh=nullptr;
  t.animator=nullptr;
  t.has_bones=false;
}

void Renderer::generate_shader(int hodnota,string vertex_prefix,string fragment_prefix)
{
  debug_print("GENERUJEM SHADER "+to_string(hodnota));
  DefaultShader*shader=new DefaultShader(vertex_prefix+default_shader_code_vertex,fragment_prefix+default_shader_code_fragment,true);
  //    debug_print("VERTEX KOD :"+vertex_prefix+default_shader_code_vertex);
  //    debug_print("FRAGMENT KOD"+fragment_prefix+default_shader_code_fragment);
  shadre.insert({hodnota,shader});
}


void Renderer::clear()
{
  meshe_to_draw.clear();
  for(auto s : shadre)
  delete s.second;

  shadre.clear();
}

void Renderer::load_shader_code()
{
  //temp xD
  string vertex_path="shaders/vertex.glsl";
  string fragment_path="shaders/fragment.glsl";

  fstream vertex_subor;
  fstream fragment_subor;

  vertex_subor.open(vertex_path);
  fragment_subor.open(fragment_path);

  stringstream vertex_stream;
  stringstream fragment_stream;

  vertex_stream<<vertex_subor.rdbuf();
  fragment_stream<<fragment_subor.rdbuf();

  default_shader_code_vertex=vertex_stream.str();
  default_shader_code_fragment=fragment_stream.str();

  vertex_subor.close();
  fragment_subor.close();
}


void Renderer::draw_skybox() {
  Skybox *skybox = gin_get_skybox();

  glm::mat4 view_skybox = glm::mat4(glm::mat3(camera_view));
  glDepthFunc(GL_LEQUAL);

  skybox->get_shader()->use();
  skybox->get_shader()->send_projection_uniform(camera_projection);
  skybox->get_shader()->send_view_uniform(view_skybox);
  skybox->get_shader()->send_skybox_texture(skybox->get_id());

  glBindVertexArray(skybox->get_VAO());
  glDrawArrays(GL_TRIANGLES,0,36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
}


void Renderer::begin_shadows() {
  //meshe_to_draw.clear();

  bind_buffer(depth_map);
  glClear(GL_DEPTH_BUFFER_BIT); 
}


void Renderer::end_shadows() {

  glCullFace(GL_FRONT);

  Scene * scene = gin_get_active_scene();
  scene->env.cal_global_light_matrix();


  for(int i = 0; i < meshe_to_draw.size(); i++) {
    MESH_T t = meshe_to_draw.at(i);

    if(t.has_bones) {
      depth_shader_animated->use();
      depth_shader_animated->send_light_space_uniform(scene->env.get_global_light_space_matrix());
      depth_shader_animated->send_model_uniform(t.global_transform);

      for(int i=0;i<t.animator->get_final_bones_transform().size();i++)
      {
        depth_shader_animated->send_bone_transform(t.animator->get_final_bones_transform().at(i),i);
      }

      glBindVertexArray(t.mesh->get_VAO());
      glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
    }
    else {
      depth_shader->use();
      depth_shader->send_light_space_uniform(scene->env.get_global_light_space_matrix());
      depth_shader->send_model_uniform(t.global_transform);
      glBindVertexArray(t.mesh->get_VAO());
      glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
    }
  }

  glCullFace(GL_BACK);
}

unsigned int Renderer::get_ocluder_map() {
  return ocluder_god_rays_buffer->texture;
}

void Renderer::begin_ocluder_god_rays() {
  camera_projection=gin_get_active_camera()->get_projection_matrix();
  camera_view=gin_get_active_camera()->get_view_matrix();

  //meshe_to_draw.clear();
  
  bind_buffer(ocluder_god_rays_buffer);

  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void Renderer::end_ocluder_god_rays() {
  Scene * scene = gin_get_active_scene();

  ocluder_god_rays_shader->use();
  ocluder_god_rays_shader->send_color_uniform(gin_get_active_scene()->env.get_global_light_color());
  ocluder_god_rays_shader->send_projection_uniform(camera_projection);

  glm::mat4 view= glm::mat4(glm::mat3(camera_view));
  ocluder_god_rays_shader->send_view_uniform(view);

  ocluder_god_rays_shader->send_model_uniform(gin_get_active_scene()->env.get_gr_decal_model());

  Model *model = gin_get_asset_manager()->get_model("gin_circle");
  Mesh *mesh = model->get_mesh_at_index(0);

  glBindVertexArray(mesh->get_VAO());
  glDrawElements(GL_TRIANGLES, mesh->get_num_indices(), GL_UNSIGNED_INT, 0);

  // ocluder_god_rays_shader->send_view_uniform(camera_view);

  // ocluder_god_rays_shader->send_color_uniform(glm::vec3(0.0f));

  for(int i = 0; i < meshe_to_draw.size(); i++) {
    MESH_T t = meshe_to_draw.at(i);
    if(t.has_bones) {
      ocluder_god_rays_shader_animated->use();
      ocluder_god_rays_shader_animated->send_projection_uniform(camera_projection);
      ocluder_god_rays_shader_animated->send_view_uniform(camera_view);
      ocluder_god_rays_shader_animated->send_color_uniform(glm::vec3(0.0f));
      ocluder_god_rays_shader_animated->send_model_uniform(t.global_transform);
      for(int i=0;i<t.animator->get_final_bones_transform().size();i++)
      {
        depth_shader_animated->send_bone_transform(t.animator->get_final_bones_transform().at(i),i);
      }
      glBindVertexArray(t.mesh->get_VAO());
      glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
    }
    else {
      ocluder_god_rays_shader->use();
      ocluder_god_rays_shader->send_projection_uniform(camera_projection);
      ocluder_god_rays_shader->send_view_uniform(camera_view);
      ocluder_god_rays_shader->send_color_uniform(glm::vec3(0.0f));
      ocluder_god_rays_shader->send_model_uniform(t.global_transform);
      glBindVertexArray(t.mesh->get_VAO());
      glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
    }
  }
}


void Renderer::draw_main() {
  bind_buffer(main_buffer);
  clear_color(0,0,0,1);
  glEnable(GL_DEPTH_TEST);

  begin();
  end();

  gin_draw_physics();
}

void Renderer::draw_shadows() {
  if(gin_get_active_scene()->env.redraw_shadow && gin_get_active_scene()->env.get_global_light_status()) {
    begin_shadows();
    end_shadows();
    //gin_get_active_scene()->env.redraw_shadow = false;
  }
}

void Renderer::draw_god_rays() {
  begin_ocluder_god_rays();
  end_ocluder_god_rays();
}


void Renderer::draw_output_volumetric() {
  bind_buffer(output_buffer);
  clear_color(0,0,0,1);

  fbo_shader->use();
  fbo_shader->send_texture_uniform(up_scale_buffer->texture);
  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::draw_output() {
  bind_buffer(output_buffer);
  clear_color(0,0,0,1);

  fbo_shader->use();
  fbo_shader->send_texture_uniform(main_buffer->texture);
  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
}

void Renderer::draw_output_gr() {
  bind_buffer(output_buffer);
  clear_color(0,0,0,1);

  god_rays_shader->use();

  if(gin_get_active_scene()->env.get_volumetric_light_status())
    god_rays_shader->send_color_texture(up_scale_buffer->texture);
  else
    god_rays_shader->send_color_texture(main_buffer->texture);
  god_rays_shader->send_ocluder_texture(ocluder_god_rays_buffer->texture);

  god_rays_shader->send_decay_uniform(gin_get_active_scene()->env.get_gr_decay());
  god_rays_shader->send_exposure_uniform(gin_get_active_scene()->env.get_gr_exposure());
  god_rays_shader->send_density_uniform(gin_get_active_scene()->env.get_gr_density());
  god_rays_shader->send_weight_uniform(gin_get_active_scene()->env.get_gr_weight());
  god_rays_shader->send_sun_pos_uniform(gin_get_active_scene()->env.get_gr_sun_pos());

  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::draw_output_to_default_buffer() {
  bind_buffer(0,gin_get_screen_w(),gin_get_screen_h());
  clear_color(0,0,0,1);

  fbo_shader->use();
  fbo_shader->send_texture_uniform(output_buffer->texture);
  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Renderer::draw_all() {
  if(gin_get_active_scene()->env.get_gr_status()) 
    draw_god_rays();

  draw_shadows();
  draw_shadows_spotlights();
  draw_main();

  if(gin_get_active_scene()->env.get_volumetric_light_status())
    draw_volumetric();

  if(gin_get_active_scene()->env.get_gr_status()) 
    draw_output_gr();
  else if(gin_get_active_scene()->env.get_volumetric_light_status())
    draw_output_volumetric();
  else
    draw_output();

}

FrameBuffer* Renderer::get_output_buffer() {
  return output_buffer;
}

void Renderer::resize_buffers() {
  if(gin_screen_resize()) {
    // main_buffer->clear();
    // main_buffer = new FrameBuffer(gin_get_screen_w(),gin_get_screen_h(),true);
    //
    // ocluder_god_rays_buffer->clear();
    // ocluder_god_rays_buffer = new FrameBuffer(gin_get_screen_w(),gin_get_screen_h(),false);

  }
}

void Renderer::bind_buffer(unsigned int buffer_id,int w, int h) {
  glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);
  glViewport(0,0,w,h);
}

void Renderer::bind_buffer(FrameBuffer *buffer) {
  glBindFramebuffer(GL_FRAMEBUFFER, buffer->get_id());
  glViewport(0, 0, buffer->get_w(), buffer->get_h());
}

void Renderer::bind_buffer(DepthMap *buffer) {
  glBindFramebuffer(GL_FRAMEBUFFER, buffer->get_id());
  glViewport(0, 0, buffer->get_w(), buffer->get_h());
}

void Renderer::swap_window() {
  abs_sdl::opengl_swap_buffer();

  resize_buffers();
}

void Renderer::clear_color(float r, float g, float b, float a) {
  abs_sdl::opengl_clear_color(r,g,b,a);
}


void Renderer::draw_shadows_spotlights() {
  Env env = gin_get_active_scene()->env;
  vector<pair<float,int>> spot_s;
  for(int i = 0; i < env.get_spot_lights().size();i++) {
    glm::vec3 l_pos = env.get_spot_lights().at(i)->get_transform().get_global_transform()[3];
    float d = glm::distance(cam_pos, l_pos);
    spot_s.push_back(make_pair(d,i));
  }
  sort(spot_s.begin(),spot_s.end());
  int size=spot_s.size();
  if(size > 4)
    size=4;
  for(int i = 0; i < size ;i++) {
    int index=spot_s[i].second;

    SpotLightNode * node = env.get_spot_lights().at(index);
    if(node->draw_shadow) 
    {
      bind_buffer(node->get_depth_map());

      glClear(GL_DEPTH_BUFFER_BIT); 
      glCullFace(GL_FRONT);

      // depth_shader->use();
      // depth_shader->send_light_space_uniform(node->get_light_space());

      for(int i = 0; i < meshe_to_draw.size(); i++) {
        MESH_T t = meshe_to_draw.at(i);
        if(t.has_bones) {
          depth_shader_animated->use();
          depth_shader_animated->send_light_space_uniform(node->get_light_space());
          depth_shader_animated->send_model_uniform(t.global_transform);

          for(int i=0;i<t.animator->get_final_bones_transform().size();i++)
          {
            depth_shader_animated->send_bone_transform(t.animator->get_final_bones_transform().at(i),i);
          }
          glBindVertexArray(t.mesh->get_VAO());
          glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
        }
        else {
          depth_shader->use();
          depth_shader->send_light_space_uniform(node->get_light_space());
          depth_shader->send_model_uniform(t.global_transform);
          glBindVertexArray(t.mesh->get_VAO());
          glDrawElements(GL_TRIANGLES, t.mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
        }
      }
      glCullFace(GL_BACK);
      //node->draw_shadow = false;
    }
  }
  spot_s.clear();
}


void Renderer::down_scale_depth() {
  bind_buffer(down_scale_depth_buffer);
  clear_color(0, 0, 0, 1);

  down_scale_depth_shader->use();
  down_scale_depth_shader->send_depth_texture(main_buffer->depth_texture);
  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::up_scale() {
  bind_buffer(up_scale_buffer);
  clear_color(0, 0, 0, 1);

  up_scale_shader->use();
  up_scale_shader->send_color_texture(main_buffer->texture);
  up_scale_shader->send_volumetric_texture(blur_buffer->texture);

  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::blur(bool v) {
  bind_buffer(blur_buffer);
  clear_color(0, 0, 0, 1);

  blur_shader->use();
  blur_shader->send_color_texture(volumetric_fb->texture);
  blur_shader->send_dir(v);

  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::draw_volumetric() {
  down_scale_depth();

  bind_buffer(volumetric_fb);
  clear_color(0, 0, 0, 1);

  Env env = gin_get_active_scene()->env;
  vector<pair<float,int>> spot_s;
  for(int i = 0; i < env.get_spot_lights().size();i++) {
    glm::vec3 l_pos = env.get_spot_lights().at(i)->get_transform().get_global_transform()[3];
    float d = glm::distance(cam_pos, l_pos);
    spot_s.push_back(make_pair(d,i));
  }
  sort(spot_s.begin(),spot_s.end());
  int size=spot_s.size();
  if(size > 4)
    size=4;

  volumetric_shader->use();
  //volumetric_shader->send_color_texture(main_buffer->texture);
  volumetric_shader->send_depth_texture(down_scale_depth_buffer->get_texture_id());
  
  volumetric_shader->send_projection_inv(gin_get_active_camera()->get_projection_matrix());
  volumetric_shader->send_view_inv(gin_get_active_camera()->get_view_matrix());
  volumetric_shader->send_camera_pos(gin_get_active_camera()->get_position());

  volumetric_shader->send_global_light_projection(env.get_global_light_projection());
  volumetric_shader->send_global_light_view(env.get_global_light_view());


  volumetric_shader->send_global_light_dir(env.get_global_light_dir());
  volumetric_shader->send_global_light_color(env.get_global_light_color());
  volumetric_shader->send_global_depth_map(depth_map->get_texture_id());
  volumetric_shader->send_global_light_status(env.get_global_light_status());


  volumetric_shader->send_volumetric_fog_status(env.get_volumetric_fog_status());
  volumetric_shader->send_volumetric_fog_denstiy(env.volumetric_fog_density);

  volumetric_shader->send_spot_lights_pocet(size);
  for(int i=0; i< size; i++) {
    int index=spot_s[i].second;

    volumetric_shader->send_spot_light_pos(env.get_spot_lights().at(index)->get_transform().get_position(), i);
    volumetric_shader->send_spot_lights_dir(env.get_spot_lights().at(index)->get_direction(), i);
    volumetric_shader->send_spot_light_color(env.get_spot_lights().at(index)->get_diff_farba(),i);
    volumetric_shader->send_spot_light_sila(env.get_spot_lights().at(index)->get_sila(),i);
    volumetric_shader->send_spot_lights_cut_off(env.get_spot_lights().at(index)->get_cut_off(),i);
    volumetric_shader->send_spot_lights_shadow_map(env.get_spot_lights().at(index)->get_depth_map()->get_texture_id(), i);
    volumetric_shader->send_spot_lights_projection(env.get_spot_lights().at(index)->get_projection(), i);
    volumetric_shader->send_spot_lights_view(env.get_spot_lights().at(index)->get_view(), i);
  }

  volumetric_shader->send_scatter_value(gin_get_active_scene()->env.scatter_value);
  float time = (float)SDL_GetTicks() / 1000.0f;
  volumetric_shader->send_time(time);

  glBindVertexArray(gin_get_asset_manager()->get_model("gin_quad")->get_mesh_at_index(0)->get_VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);

  blur(true);
  blur(false);

  up_scale();
}
