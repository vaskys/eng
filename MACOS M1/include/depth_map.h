#ifndef DEPTH_MAP_H
#define DEPTH_MAP_H


class DepthMap {
public:
    DepthMap(int screenW,int screenH);
    ~DepthMap();

    unsigned int get_texture_id();
    unsigned int get_id();

    int get_w();
    int get_h();


    void clear();

private:
    unsigned int texture_id;
    unsigned int id;

    int w;
    int h;
};

#endif
