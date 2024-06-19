#include "gui.h"
#include "engine.h"
#include "imgui.h"
#include "lights.h"
#include "model_node.h"
#include "fnode.h"
#include <cstring>

#include "imfilebrowser.h"
#include <filesystem>
#include <string>

Node *selected_node=nullptr;
static bool can_select=true;
static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

static int s=-1;
static bool can_drop=true;
static bool open_model_load=false;
static bool open_file_load=false;
static bool open_file_save=false;
static bool load_model_browser = false;

static char model_path[255] = "";
static char node_name[255]="";
static char sl_path[255]="";

ImGui::FileBrowser *fileDialog;
bool style = false;

void gui_init(SDL_Window *window, SDL_GLContext &context)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io=ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForOpenGL(window,context);
  ImGui_ImplOpenGL3_Init();
  //    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  //    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly=true;
  //    ImGui::GetIO().ConfigWindowsResizeFromEdges=false;

  fileDialog = new ImGui::FileBrowser();
  fileDialog->SetTypeFilters({ ".txt", ".obj", ".fbx", ".dae" });

  //  ImGui::StyleColorsLight();
}

void gui_clear()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();

  delete fileDialog;
  ImGui::DestroyContext();

  selected_node=nullptr;
}

void gui_process_sdl_event(SDL_Event &event)
{
  ImGui_ImplSDL2_ProcessEvent(&event);
}

void gui_new_frame(SDL_Window *window)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
  ImGui::NewFrame();


  gui_test();

}
void gui_draw()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



void recursive_add_create_tree(Node *node,int c)
{
  ImGuiTreeNodeFlags node_flags = base_flags;
  if(selected_node != nullptr)
  {
    if(selected_node == node)
    {
      node_flags |=ImGuiTreeNodeFlags_Selected;
    }
  }

  if(ImGui::TreeNodeEx((void*)node,node_flags,node->get_name().c_str()))
  {
    for(int i=0;i<node->get_children().size();i++)
    {
      Node *child=node->get_children().at(i);
      recursive_add_create_tree(child,c+i+1);
    }
    ImGui::TreePop();
  }


  if (ImGui::IsItemClicked()  && !ImGui::IsItemToggledOpen() && can_select)
  {
    selected_node=node;
    can_select=false;
  }
  else if(ImGui::IsItemClicked(1) && can_select && !ImGui::IsItemToggledOpen())
  {
    can_select=false;
    selected_node=node;
    ImGui::OpenPopup("select_pop_up");
    s=c;
  }

  if(c == s && c!=0 )
  {
    if(ImGui::BeginPopup("select_pop_up"))
    {
      if (ImGui::Button("Delete"))
      {
        Node *parent=selected_node->get_parent();
        debug_print("PARENT "+parent->get_name());
        parent->delete_child_node(selected_node->get_name());
        selected_node=NULL;

        ImGui::CloseCurrentPopup();
      }
      if (ImGui::Button("Unparent"))
      {
        selected_node->unparent(gin_get_active_scene()); 
      }
      if(ImGui::Button("Copy"))
      {
        selected_node->copy(gin_get_active_scene());
      }
      ImGui::EndPopup();
    }
  }

  if(ImGui::BeginDragDropSource())
  {
    ImGui::SetDragDropPayload("xd",NULL,0);
    ImGui::Text(selected_node->get_name().c_str());
    ImGui::EndDragDropSource();
  }

  if(ImGui::BeginDragDropTarget())
  {
    if(ImGui::IsMouseReleased(0) && can_drop)
    {
      //            debug_print("DROP TARGET "+to_string(c)); 
      //            debug_print("DROP TARGET N :"+node->get_name());
      can_drop=false;
      selected_node->unparent(node);
    }
    ImGui::EndDragDropTarget();
  }

}

void gui_main_menu()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New")) 
      {
        open_model_load=false;
        selected_node=NULL;

        gin_get_active_scene()->reset();
        gin_get_asset_manager()->clear();
        gin_get_asset_manager()->init_default();
        gin_set_active_camera(gin_get_default_camera());
        debug_print("SCENE RESET");
      }
      if (ImGui::MenuItem("Save")) 
      {
        open_file_save=true;
        open_file_load=false;
        open_model_load=false;
        load_model_browser = false;
      }
      if (ImGui::MenuItem("Load")) 
      {
        open_model_load=false;
        open_file_load=true;
        open_file_save=false;

        selected_node=NULL;
        fileDialog->Open();


      }
      if (ImGui::MenuItem("Fyzika",NULL,gin_get_f_update()))
      {
        if(!gin_get_f_update())
          gin_set_f_update(true);
        else
          gin_set_f_update(false);
      }

      if(ImGui::MenuItem("DebugDraw",NULL,gin_get_fdraw()))
      {
        if(!gin_get_fdraw())
          gin_set_fdraw(true);
        else
          gin_set_fdraw(false);
      }
      if(ImGui::MenuItem("LightMode",NULL,style)) 
      {
        if(!style) {
          ImGui::StyleColorsLight();
          style = true;
        }
        else {
          ImGui::StyleColorsDark();
          style = false;
        }
      }

      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Add"))
    {
      if (ImGui::MenuItem("Point Light")) 
      {
        gin_get_active_scene()->add_light();
      }
      if (ImGui::MenuItem("SpotLIght")) 
      {
        gin_get_active_scene()->add_spot_light();
      }
      if (ImGui::MenuItem("Model")) 
      {
        open_model_load=true;
      }
      if (ImGui::MenuItem("Empty")) 
      {
        gin_get_active_scene()->add_empty();
      }
      if (ImGui::MenuItem("Camera")) 
      {
        gin_get_active_scene()->add_camera_node();
      }

      if(ImGui::MenuItem("FObj"))
      {
        gin_get_active_scene()->add_fobj();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
void gui_node_tree()
{
  can_select=true;
  can_drop=true;
  Scene *scene=gin_get_active_scene();

  ImGui::SetNextWindowPos(ImVec2((gin_get_screen_w() /100) * 80 ,19));
  ImGui::SetNextWindowSize(ImVec2((gin_get_screen_w() / 100) * 28,(gin_get_screen_h()/2)-19));

  if(ImGui::Begin("Scena",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus ))
  {
    recursive_add_create_tree(scene,0);
    ImGui::End();
  }
}

void gui_fbo_render()
{
  ImGui::SetNextWindowPos(ImVec2(0,19));
  ImGui::SetNextWindowSize(ImVec2((gin_get_screen_w() / 100) * 80,gin_get_screen_h()-19));
  if(ImGui::Begin("FBO_RENDER",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus  ))
  {
    if(ImGui::BeginTabBar("Main"))
    {
      if (ImGui::BeginTabItem("Editor Cam"))
      {
        gin_set_active_camera(gin_get_default_camera());
        string fps="FPS "+to_string(gin_get_fps());
        ImGui::Text(fps.c_str());
        ImGui::BeginChild("RENDER");
        ImVec2 size= ImGui::GetWindowSize();
        unsigned int t_id=gin_get_main_renderer()->get_output_buffer()->texture;
        ImGui::Image((ImTextureID)t_id,size,ImVec2(0,1),ImVec2(1,0));
        ImGui::EndChild();

        ImGui::EndTabItem();
      }
      for(int i=0;i<gin_get_active_scene()->cameras.size();i++)
      {
        if (ImGui::BeginTabItem(gin_get_active_scene()->cameras.at(i)->get_name().c_str()))
        {
          Camera *camera=gin_get_active_scene()->cameras.at(i)->get_camera();
          gin_set_active_camera(camera);

          string fps="FPS "+to_string(gin_get_fps());
          ImGui::Text(fps.c_str());
          ImGui::BeginChild("RENDER");
          ImVec2 size= ImGui::GetWindowSize();
          // unsigned int t_id=gin_get_main_frame_buffer()->texture;
          unsigned int t_id=gin_get_main_renderer()->get_output_buffer()->texture;

          ImGui::Image((ImTextureID)t_id,size,ImVec2(0,1),ImVec2(1,0));
          ImGui::EndChild();
          ImGui::EndTabItem();
        }
      }
      ImGui::EndTabBar();
    }
  }
  ImGui::End();
}

void gui_selected_node()
{
  ImGui::SetNextWindowPos(ImVec2((gin_get_screen_w() /100) * 80 ,(gin_get_screen_h()/2)));
  ImGui::SetNextWindowSize(ImVec2((gin_get_screen_w() / 100) * 28,(gin_get_screen_h()/2)));

  if(ImGui::Begin("SELECTED NODE",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus ))
  {
    if(selected_node != nullptr)
    {
      strcpy(node_name,selected_node->get_name().c_str());
      if(ImGui::InputText("",node_name,IM_ARRAYSIZE(node_name),ImGuiInputTextFlags_EnterReturnsTrue))
      {
        selected_node->set_name(node_name);
      }

      if(dynamic_cast<Scene*>(selected_node))
      {


        glm::vec3 color=gin_get_active_scene()->env.get_global_light_color();
        glm::vec3 dir=gin_get_active_scene()->env.get_global_light_dir();
        bool status=gin_get_active_scene()->env.get_global_light_status();
        float ambient = gin_get_active_scene()->env.get_global_light_ambient();


        ImGui::Checkbox("GLOBAL LIGHT",&status);

        ImGui::SliderFloat("dir x",&dir.x,-1.0f,1.0f);
        ImGui::SliderFloat("dir y",&dir.y,-1.0f,1.0f);
        ImGui::SliderFloat("dir z",&dir.z,-1.0f,1.0f);





        // ImGui::DragFloat("pos X", &dir.x,1.1f * gin_get_delta_time());
        // ImGui::DragFloat("pos Y", &dir.y,1.1f * gin_get_delta_time());
        // ImGui::DragFloat("pos Z", &dir.z,1.1f * gin_get_delta_time());

        //                ImGui::SliderFloat("dir x",&dir.x,-100.0f,100.0f);
        //                ImGui::SliderFloat("dir y",&dir.y,-100.0f,100.0f);
        //                ImGui::SliderFloat("dir z",&dir.z,-100.0f,100.0f);

        ImGui::SliderFloat("AMBIENT", &ambient, 0.0f,1.0f);
        ImVec4 imgui_farba=ImVec4(color.x,color.y,color.z,0.0f);
        ImGui::ColorEdit3("FARBA",(float*)&imgui_farba,0);

        gin_get_active_scene()->env.set_global_light_color(glm::vec3(imgui_farba.x,imgui_farba.y,imgui_farba.z));
        gin_get_active_scene()->env.set_global_light_dir(dir);
        gin_get_active_scene()->env.set_global_light_status(status);
        gin_get_active_scene()->env.set_global_light_ambient(ambient);


        ImGui::Separator();

        bool volumetric_status = gin_get_active_scene()->env.get_volumetric_light_status();
        int volumetric_fog_status = gin_get_active_scene()->env.get_volumetric_fog_status();

        ImGui::Checkbox("Volumetric Light",&volumetric_status);

        string fog_type_name_v;
        if(volumetric_fog_status == 0 )
          fog_type_name_v = "full fog";
        else if(volumetric_fog_status == 1) {
          fog_type_name_v = "ray + fog";
        }
        else {
          fog_type_name_v = "ray";
        }
        if(ImGui::BeginCombo("V",fog_type_name_v.c_str()))
        {
          if(ImGui::Selectable("RAY"))
          {
            volumetric_fog_status = 2;
          }
          else if(ImGui::Selectable("RAY + FOG"))
          {
            volumetric_fog_status = 1;
          }
          else if(ImGui::Selectable("FULL FOG"))
          {
            volumetric_fog_status = 0;
          }
          ImGui::EndCombo();
        }
        ImGui::DragFloat("Scatter Value", &gin_get_active_scene()->env.scatter_value,1.1f * gin_get_delta_time());

        ImGui::DragFloat("FOG NOISE", &gin_get_active_scene()->env.volumetric_fog_density,1.1f * gin_get_delta_time());
        gin_get_active_scene()->env.set_volumetric_light_status(volumetric_status);
        gin_get_active_scene()->env.set_volumetric_fog_status(volumetric_fog_status);

        ImGui::Separator();
        bool gd_status = gin_get_active_scene()->env.get_gr_status();
        ImGui::Checkbox("GOD RAYS",&gd_status);

        float gd_decay = gin_get_active_scene()->env.get_gr_decay();
        float gd_exposure = gin_get_active_scene()->env.get_gr_exposure();
        float gd_density = gin_get_active_scene()->env.get_gr_density();
        float gd_weight = gin_get_active_scene()->env.get_gr_weight();


        ImGui::DragFloat("decay", &gd_decay,1.1f * gin_get_delta_time());
        ImGui::DragFloat("exposure", &gd_exposure,1.1f * gin_get_delta_time());
        ImGui::DragFloat("density", &gd_density,1.1f * gin_get_delta_time());
        ImGui::DragFloat("weight", &gd_weight,1.1f * gin_get_delta_time());

        gin_get_active_scene()->env.set_gr_density(gd_density);
        gin_get_active_scene()->env.set_gr_weight(gd_weight);
        gin_get_active_scene()->env.set_gr_exposure(gd_exposure);
        gin_get_active_scene()->env.set_gr_decay(gd_decay);
        gin_get_active_scene()->env.set_gr_status(gd_status);

        ImGui::Separator();

        int fog_type = gin_get_active_scene()->env.get_fog_type();
        bool fog_status = gin_get_active_scene()->env.get_fog_status();
        glm::vec3 fog_color = gin_get_active_scene()->env.get_fog_color();
        float fog_end = gin_get_active_scene()->env.get_fog_end();
        float fog_start = gin_get_active_scene()->env.get_fog_start();
        float fog_density = gin_get_active_scene()->env.get_fog_density();

        string fog_type_name = (fog_type == 0) ? "linear" : "exponencial";
        ImGui::Checkbox("FOG",&fog_status);
        if(ImGui::BeginCombo("TYPE",fog_type_name.c_str()))
        {
          if(ImGui::Selectable("LINEAR"))
          {
            gin_get_active_scene()->env.set_fog_type(0);
          }
          else if(ImGui::Selectable("EXPONENCIAL"))
          {
            gin_get_active_scene()->env.set_fog_type(1);
          }
          ImGui::EndCombo();
        }



        if(fog_type == 0) {
          ImGui::DragFloat("start", &fog_start,1.1f * gin_get_delta_time());
          ImGui::DragFloat("end", &fog_end,1.1f * gin_get_delta_time());
        }
        else {
          ImGui::DragFloat("end", &fog_end,1.1f * gin_get_delta_time());
          ImGui::DragFloat("F density", &fog_density,1.1f * gin_get_delta_time());
        }

        ImVec4 imgui_fog_colro =ImVec4(fog_color.x,fog_color.y,fog_color.z,0.0f);
        ImGui::ColorEdit3("FOG COLOR",(float*)&imgui_fog_colro,0);


        gin_get_active_scene()->env.set_fog_status(fog_status);
        gin_get_active_scene()->env.set_fog_color(glm::vec3(imgui_fog_colro.x,imgui_fog_colro.y,imgui_fog_colro.z));
        gin_get_active_scene()->env.set_fog_start(fog_start);
        gin_get_active_scene()->env.set_fog_end(fog_end);
        gin_get_active_scene()->env.set_fog_density(fog_density);


        ImGui::Separator();
        bool f_status=gin_get_f_update();
        ImGui::Checkbox("Fyzika ",&f_status);
        ImGui::Text("GRAVITACIA");
        glm::vec3 gravity=gin_get_fworld()->get_gravity();
        ImGui::InputFloat("G X",&gravity.x);
        ImGui::InputFloat("G Y",&gravity.y);
        ImGui::InputFloat("G Z",&gravity.z);
        gin_get_fworld()->set_gravity(gravity);
        gin_set_f_update(f_status);
      }
      else
    {

        Transform transform;
        transform=selected_node->get_transform();

        glm::vec3 pos=transform.get_position();
        glm::vec3 scale=transform.get_scale();
        glm::vec3 euler=transform.get_euler();

        ImGui::DragFloat("pos X", &pos.x,1.1f * gin_get_delta_time());
        ImGui::DragFloat("pos Y", &pos.y,1.1f * gin_get_delta_time());
        ImGui::DragFloat("pos Z", &pos.z,1.1f * gin_get_delta_time());
        ImGui::Separator();

        if (!dynamic_cast<LightNode*>(selected_node) && !dynamic_cast<SpotLightNode*>(selected_node)) 
        {
          ImGui::DragFloat("ROT X", &euler.x,15.0f * gin_get_delta_time());
          ImGui::DragFloat("ROT Y", &euler.y,15.0f * gin_get_delta_time());
          ImGui::DragFloat("ROT Z", &euler.z,15.0f * gin_get_delta_time());
          ImGui::Separator();

          if(!dynamic_cast<FNode*>(selected_node))
          {

            ImGui::DragFloat("scale X", &scale.x,1.1f * gin_get_delta_time());
            ImGui::DragFloat("scale Y", &scale.y,1.1f * gin_get_delta_time());
            ImGui::DragFloat("scale Z", &scale.z,1.1f * gin_get_delta_time());

            if(dynamic_cast<ModelNode*>(selected_node))
            {
              if(ImGui::Button("MODEL COLLIDER"))
              {
                gin_get_active_scene()->add_mesh_fobj((ModelNode*)selected_node);
              }
            }

          }
          else
        {
            //                        if(ImGui::Button("TEST"))
            //                        {
            //                            ((FNode*)selected_node)->test();
            //                        }
            float mass=((FNode*)selected_node)->get_mass();
            if(ImGui::InputFloat("mass",&mass))
            {
              ((FNode*)selected_node)->set_mass(mass);
            }
            string shape_type=((FNode*)selected_node)->get_shape_type();
            if(ImGui::BeginCombo("SHAPE",shape_type.c_str()))
            {
              if(ImGui::Selectable("box"))
              {
                ((FNode*)selected_node)->set_shape("box");
              }
              else if(ImGui::Selectable("sphere"))
              {
                ((FNode*)selected_node)->set_shape("sphere");
              }
              else if(ImGui::Selectable("capsule"))
              {
                ((FNode*)selected_node)->set_shape("capsule");
              }
              ImGui::EndCombo();
            }
            if(shape_type == "box")
            {
              glm::vec3 s_size=((FNode*)selected_node)->get_size();
              //ugly af
              if(ImGui::DragFloat("X",&s_size.x,1.1f * gin_get_delta_time()))
              {
                ((FNode*)selected_node)->set_size(s_size);
                ((FNode*)selected_node)->set_shape("box");

              }
              if(ImGui::DragFloat("Y",&s_size.y,1.1f * gin_get_delta_time()))
              {
                ((FNode*)selected_node)->set_size(s_size);
                ((FNode*)selected_node)->set_shape("box");
              }
              if(ImGui::DragFloat("Z",&s_size.z,1.1f*gin_get_delta_time()))
              {
                ((FNode*)selected_node)->set_size(s_size);
                ((FNode*)selected_node)->set_shape("box");
              }

            }
            else if(shape_type == "sphere")
            {
              float radius=((FNode*)selected_node)->get_radius();
              if(ImGui::DragFloat("radius",&radius,1.1f * gin_get_delta_time()))
              {
                ((FNode*)selected_node)->set_radius(radius);
                ((FNode*)selected_node)->set_shape("sphere");
              }
            }
            else if(shape_type == "capsule")
            {
              float radius=((FNode*)selected_node)->get_radius();
              float height=((FNode*)selected_node)->get_height();

              if(ImGui::DragFloat("radius",&radius,1.1f * gin_get_delta_time()))
              {
                ((FNode*)selected_node)->set_radius(radius);
                ((FNode*)selected_node)->set_shape("capsule");
              }
              if(ImGui::DragFloat("height",&height,1.1f * gin_get_delta_time()))
              {
                ((FNode*)selected_node)->set_height(height);
                ((FNode*)selected_node)->set_shape("capsule");
              }

            }

          }

        }
        else
      {
          if(dynamic_cast<LightNode*>(selected_node)) {
            float sila=((LightNode*)selected_node)->get_sila();
            float ambient =((LightNode*)selected_node)->get_ambient();
            glm::vec3 farba=((LightNode*)selected_node)->get_diff_farba();
            ImVec4 imgui_farba=ImVec4(farba.x,farba.y,farba.z,0.0f);
            ImGui::DragFloat("SILA", &sila,1.1f * gin_get_delta_time());
            ImGui::SliderFloat("AMBIENT", &ambient, 0.0f,1.0f);
            ImGui::ColorEdit3("FARBA",(float*)&imgui_farba,0);

            ((LightNode*)selected_node)->set_color(glm::vec3(imgui_farba.x,imgui_farba.y,imgui_farba.z));
            ((LightNode*)selected_node)->set_sila(sila);
            ((LightNode*)selected_node)->set_ambient(ambient);
          }
          else if(dynamic_cast<SpotLightNode*>(selected_node)) {

            glm::vec3 dir = ((SpotLightNode*)selected_node)->get_direction();
            float cut_off = ((SpotLightNode*)selected_node)->get_cut_off();
            // float bias = ((SpotLightNode*)selected_node)->get_bias();

            // ImGui::DragFloat("DIR X", &dir.x,1.1f * gin_get_delta_time());
            // ImGui::DragFloat("DIR Y", &dir.y,1.1f * gin_get_delta_time());
            // ImGui::DragFloat("DIR Z", &dir.z,1.1f * gin_get_delta_time());

            ImGui::SliderFloat("dir x",&dir.x,-1.0f,1.0f);
            ImGui::SliderFloat("dir y",&dir.y,-1.0f,1.0f);
            ImGui::SliderFloat("dir z",&dir.z,-1.0f,1.0f);

            ImGui::Separator();
            ImGui::DragFloat("RADIUS", &cut_off,1.1f * gin_get_delta_time());
            ImGui::Separator();

            float sila=((SpotLightNode*)selected_node)->get_sila();
            float ambient =((SpotLightNode*)selected_node)->get_ambient();

            glm::vec3 farba=((SpotLightNode*)selected_node)->get_diff_farba();
            ImVec4 imgui_farba=ImVec4(farba.x,farba.y,farba.z,0.0f);
            ImGui::DragFloat("SILA", &sila,1.1f * gin_get_delta_time());
            ImGui::SliderFloat("AMBIENT", &ambient, 0.0f,1.0f);
            ImGui::ColorEdit3("FARBA",(float*)&imgui_farba,0);

            // ImGui::Separator();
            // ImGui::DragFloat("BIAS", &bias,0.1f * gin_get_delta_time());

            ((SpotLightNode*)selected_node)->set_color(glm::vec3(imgui_farba.x,imgui_farba.y,imgui_farba.z));
            ((SpotLightNode*)selected_node)->set_sila(sila);
            ((SpotLightNode*)selected_node)->set_direction(dir);
            ((SpotLightNode*)selected_node)->set_cut_off(cut_off);
            ((SpotLightNode*)selected_node)->set_ambient(ambient);
            // ((SpotLightNode*)selected_node)->set_bias(bias);
          }
        }
        transform.set_local_transform(pos,scale,euler);
        selected_node->set_transform(transform);
      }
    }
  }
  ImGui::End();
}


void gui_add_model()
{
  if(open_model_load)
  {
    ImGui::SetNextWindowPos(ImVec2((gin_get_screen_w() /100) * 20 ,(gin_get_screen_h()/100)*35));
    ImGui::SetNextWindowSize(ImVec2((gin_get_screen_w() / 100) * 40,(gin_get_screen_h()/100)*30));

    if(ImGui::Begin("ADD MODEL",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
      //ImGui::InputText("",model_path,IM_ARRAYSIZE(model_path));
      //      ImGui::SameLine();
      if(ImGui::Button("BROWSER"))
      {
        //        gin_get_active_scene()->add_model_node(model_path);
        //        gin_get_asset_manager()->load_model(model_path);
        // open_model_load=false;
        open_model_load = true;
        load_model_browser = true;
        fileDialog->Open();
        //return;
      }
      ImGui::SameLine();
      if(ImGui::Button("CANCEL"))
      {
        open_model_load=false;
        load_model_browser = false;
      }
      set<string> p=gin_get_asset_manager()->get_list_of_models();

      for(auto meno : p)
      {
        if(ImGui::Button(meno.c_str()))
        {
          gin_get_active_scene()->add_model_node(meno);
          open_model_load=false;
          return ;
        }
      }
      ImGui::Separator();

      ImGui::End();
    }
  }
}

void gui_save_file()
{
  if(open_file_save)
  {
    ImGui::SetNextWindowPos(ImVec2((gin_get_screen_w() /100) * 20 ,(gin_get_screen_h()/100)*35));
    ImGui::SetNextWindowSize(ImVec2((gin_get_screen_w() / 100) * 40,(gin_get_screen_h()/100)*10));
    if(ImGui::Begin("SAVE",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
      ImGui::InputText("",sl_path,IM_ARRAYSIZE(sl_path));
      ImGui::SameLine();
      if(ImGui::Button("SAVE"))
      {
        gin_get_active_scene()->save(sl_path);
        open_file_save=false;
        return;
      }
      ImGui::SameLine();
      if(ImGui::Button("CANCEL"))
      {
        open_file_save=false;
      }

      ImGui::End();
    }

  }
}

void gui_load_file()
{
  if(open_file_load)
  {
    if(fileDialog->HasSelected()) {
      string xd = fileDialog->GetSelected().string();
      gin_set_f_update(false);
      gin_set_fdraw(true);

      gin_get_asset_manager()->clear();
      gin_get_asset_manager()->init_default();
      gin_get_active_scene()->load(xd);
      gin_set_active_camera(gin_get_default_camera());

      open_file_load = false;
      fileDialog->ClearSelected();
    } 
  }
  //   ImGui::SetNextWindowPos(ImVec2((gin_get_screen_w() /100) * 20 ,(gin_get_screen_h()/100)*35));
  //   ImGui::SetNextWindowSize(ImVec2((gin_get_screen_w() / 100) * 40,(gin_get_screen_h()/100)*10));
  //   if(ImGui::Begin("LOAD",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
  //   {
  //     ImGui::InputText("",sl_path,IM_ARRAYSIZE(sl_path));
  //     ImGui::SameLine();
  //     if(ImGui::Button("LOAD"))
  //     {
  //
  //       gin_set_f_update(false);
  //       gin_set_fdraw(true);
  //
  //       gin_get_asset_manager()->clear();
  //       gin_get_asset_manager()->init_default();
  //       gin_get_active_scene()->load(sl_path);
  //       gin_set_active_camera(gin_get_default_camera());
  //
  //       open_file_load=false;
  //       return;
  //     }
  //     ImGui::SameLine();
  //     if(ImGui::Button("CANCEL"))
  //     {
  //       open_file_load=false;
  //     }
  //
  //     ImGui::End();
  //   }
  //
  // }

}

void gui_test()
{
  gui_main_menu();
  {
    gui_node_tree();
    gui_fbo_render();
    gui_selected_node();
    gui_add_model();
    gui_save_file();
    gui_load_file();

    if(load_model_browser) {
      if(fileDialog->HasSelected()) {
        string xd = fileDialog->GetSelected().string();
        gin_get_asset_manager()->load_model(xd);
        fileDialog->ClearSelected();
        load_model_browser = false;
      }
    }

    fileDialog->Display();
  }
}



void gui_rescale()
{

}
