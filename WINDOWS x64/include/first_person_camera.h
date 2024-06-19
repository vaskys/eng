#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include "camera.h"

class FirstPersonCamera : public Camera
{
    public:
        FirstPersonCamera(float aspect_ratio,float fov,float z_near,float z_far);
        ~FirstPersonCamera();

        void update();
        void controls();

        // float yaw  ;
        // float pitch;
        float lastX;
        float lastY ;
        float fov   ;
        bool c_lock ;

        void set_look(glm::vec3 e);
};

#endif
