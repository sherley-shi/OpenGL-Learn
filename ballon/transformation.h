#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <vector>

//只需要初始化一个变换对象
struct point{
    float x, y, z, res;
};

class TransFormation{
public:
    TransFormation(std::vector<point>& ps);
    void E(); //单位矩阵
    void Translate(float, float, float); //平移变化
    void ReflectX(); //X轴的反射变化
    void Scale(float, float, float); //缩放变化
    void MultiMatrix(); //矩阵相乘
public:
    std::vector<point> ps;
    float matrix[4][4];
};

#endif
