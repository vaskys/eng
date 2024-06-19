#ifndef RENDERER_H
#define RENDERER_H

#include "FBOShader.h"
#include "blur_shader.h"
#include "config.h"
#include "framebuffer.h"
#include "god_rays_shader.h"
#include "mesh.h"
#include "model.h"
#include "oc_gr_shader.h"
#include "shader.h"
#include "mesh_node.h"
#include "animator.h"
#include "depth_shader.h"
#include "depth_map.h"
#include "up_scale_shader.h"
#include "volumetric_shader.h"
#include "down_scale_shader.h"

#include <map>

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void draw(Model *model,glm::mat4 transform);
  //        void draw(ModelNode *node);
  void draw(MeshNode *node);
  void end();
  void clear();


  void draw_shadows_spotlights();
  void draw_main();
  void draw_shadows();
  void draw_god_rays();
  void draw_output();
  void draw_output_gr();
  void draw_output_volumetric();

  void draw_output_combine();

  void draw_output_to_default_buffer();

  void draw_all();

  unsigned int get_ocluder_map();

  void reset();


  void clear_color(float r,float g,float b, float a);
  void swap_window();
  void bind_buffer(unsigned int buffer_id,int w,int h);
  void bind_buffer(DepthMap *buffer);
  void bind_buffer(FrameBuffer *buffer);

  FrameBuffer *get_output_buffer();
  void resize_buffers();
private:
  void begin(glm::mat4 VP);
  void begin();

  void begin_shadows();
  void end_shadows();

  void begin_ocluder_god_rays();
  void end_ocluder_god_rays();


  void push(MESH_T mesh,DefaultShader*shader);
  void filter();

  vector<MESH_T> meshe_to_draw;

  map<int,DefaultShader*> shadre;

  glm::mat4 camera_projection;
  glm::mat4 camera_view;
  glm::vec3 cam_pos;

  void search_nodes(glm::mat4 glob,Model *model,MeshNode *node);
  void search_node_for_meshes(glm::mat4 glob,Model *model,MeshNode *node);

  string default_shader_code_vertex;
  string default_shader_code_fragment;

  void load_shader_code();
  void generate_shader(int hodnota,string vertex_prefix,string fragment_prefix);


  void unload_unused_shaders();
  void draw_skybox();

  DepthShader *depth_shader;
  DepthShaderAnimated *depth_shader_animated;
  DepthMap *depth_map; //tiene

  FrameBuffer *ocluder_god_rays_buffer;
  OcGRShader *ocluder_god_rays_shader;
  GodRaysShader *god_rays_shader;

  FBOShader *fbo_shader;
  FrameBuffer *main_buffer;
  FrameBuffer *output_buffer;

  VolumetricShader *volumetric_shader;
  FrameBuffer *volumetric_fb;

  DepthMap *down_scale_depth_buffer;
  DownScaleShader *down_scale_depth_shader;

  FrameBuffer *up_scale_buffer;
  UpScaleShader *up_scale_shader;

  BlurShader *blur_shader;
  FrameBuffer *blur_buffer;


  OcGRShaderAnimated *ocluder_god_rays_shader_animated;



  ///voluemtric 
  void down_scale_depth();
  void up_scale();
  void blur(bool v);

  void draw_volumetric();


};

#endif
