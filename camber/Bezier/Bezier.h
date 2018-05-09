//#pragma once
#ifndef  BERIZER_H
#define BERIZER_H

struct Point{
    double x, y, z;
    //实现三维点的加减法，乘
    friend Point operator -(const Point& p1, const Point& p2){
        return Point{p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
    }
    friend Point operator +(const Point& p1, const Point& p2){
        return Point{p1.x+p2.x, p1.y+p2.y, p1.z+p2.z};
    }
    friend Point operator *(const double multi, const Point p1){
        return Point{p1.x*multi, p1.y*multi, p1.z*multi};
    }
    friend Point operator *(const Point& p1, const double multi){
        return Point{p1.x*multi, p1.y*multi, p1.z*multi};
    }
};


class DoBezier{
private:
    Point p[4][4];
    void LeftMulti(double Matrix[][4], Point p[][4]);
    void RightMulti(Point p[][4], double Matrix[][4]);
    //矩阵的转至是同样的, 不做转职
public:

    DoBezier();
    ~DoBezier();
    void ReadControlPoint(Point ps[][4]);
    void DrawPatch();
    void DrawControlGrid();
    void DrawContorlPoint();
};

#endif
