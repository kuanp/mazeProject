#ifndef UTIL_H
#define UTIL_H

#include "SimpleImage.h"
#include <cmath>

// a 2D Point with coordinates (x, y)
struct Point2f {
  float x, y;

  Point2f() { x = 0. ;  y = 0. ; }
  Point2f(float _x, float _y) { x = _x; y = _y; }

  Point2f operator*(float s) { return Point2f(x * s, y * s); }
  Point2f operator-() { return Point2f(-x, -y); }
  Point2f operator-(Point2f const o) { return Point2f(x - o.x, y - o.y); }
  Point2f operator+(Point2f const o) { return Point2f(x + o.x, y + o.y); }

};

// a 3D Point with coordinates (x, y, z)
struct Point3f {
  float x, y, z;

  Point3f() { x = 0. ;  y = 0. ; z = 0.; }
  Point3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z;}

  Point3f normal() {
      return Point3f(x/sqrt(pow(x, 2) + pow(y, 2) + pow(z,2)),
		y/sqrt(pow(x, 2) + pow(y, 2) + pow(z,2)),
		z/sqrt(pow(x, 2) + pow(y, 2) + pow(z,2))); }
  Point3f operator*(float s) { return Point3f(x * s, y * s, z * s); }
  Point3f operator-() { return Point3f(-x, -y, -z); }
  Point3f operator-(Point3f const o) { return Point3f(x - o.x, y - o.y, z-o.z); }
  Point3f operator+(Point3f const o) { return Point3f(x + o.x, y + o.y, z+o.z); }
 };


// x = width; y = length;
struct Rect3f {
    Point3f a,b,c,d;

    Rect3f() {a = Point3f(); b = Point3f(); c = Point3f(); d = Point3f();}
    Rect3f(Point3f _a,  Point3f _b,  Point3f _c, Point3f _d) { a = _a; b = _b;  c = _c; d = _d;}
};

// A 2D line from point a to point b.
struct Line2f {
  Point2f a, b;

  Line2f() { a = Point2f(); b = Point2f(); }
  Line2f(Point2f _a, Point2f _b) { a = _a; b = _b; }
};

// A planar triangle, consisting of three points a, b, c with colors a_color, b_color, c_color
struct Triangle2f {
  Point2f a, b, c;
  RGBColor a_color, b_color, c_color;

  Triangle2f() {a = Point2f(); b = Point2f(); c = Point2f(); }
  Triangle2f(Point2f _a, Point2f _b, Point2f _c) { a = _a; b = _b; c = _c; }
  void color_verts(RGBColor _a, RGBColor _b, RGBColor _c) { a_color = _a; b_color = _b; c_color = _c;}
};

struct Triangle3f {
  Point3f a, b, c;
  Point3f a_normal, b_normal, c_normal;
  Point2f a_texture, b_texture, c_texture;
  RGBColor a_color, b_color, c_color;

  Triangle3f() {a = Point3f(); b = Point3f(); c = Point3f(); }
  Triangle3f(Point3f _a, Point3f _b, Point3f _c) { a = _a; b = _b; c = _c; }

  void color_verts(RGBColor _a, RGBColor _b, RGBColor _c) { a_color = _a; b_color = _b; c_color = _c;}
  void normal_verts(Point3f _a, Point3f _b, Point3f _c) { a_normal = _a; b_normal = _b; c_normal = _c;}
  void texture_verts(Point2f _a, Point2f _b, Point2f _c) { a_texture = _a; b_texture = _b; c_texture = _c;}
};


// [ m11 m12 m13 ]
// [ m21 m22 m23 ]
// [ m31 m32 m33 ]
struct Matrix {
    float m11, m12, m13, m21, m22, m23, m31, m32, m33;
};

struct Vector {
    float v1, v2, v3;
};

Matrix rotate(float degrees) {
    float rad = degrees*M_PI/180;
    Matrix result;
    result.m11 = cos(rad);
    result.m12 = -1*sin(rad);
    result.m13 = 0;
    result.m21 = sin(rad);
    result.m22 = cos(rad);
    result.m23 = 0;
    result.m31 = 0;
    result.m32 = 0;
    result.m33 = 1;
    return result;
}

Matrix translate(float tx, float ty) {
    Matrix result;
    result.m11 = 1;
    result.m12 = 0;
    result.m13 = tx;
    result.m21 = 0;
    result.m22 = 1;
    result.m23 = ty;
    result.m31 = 0;
    result.m32 = 0;
    result.m33 = 1;
    return result;
}

Matrix scale(float xfactor, float yfactor) {
    Matrix result;
    result.m11 = xfactor;
    result.m12 = 0;
    result.m13 = 0;
    result.m21 = 0;
    result.m22 = yfactor;
    result.m23 = 0;
    result.m31 = 0;
    result.m32 = 0;
    result.m33 = 1;
    return result;
}

Matrix multMatrix(Matrix a, Matrix b) {
    Matrix result;
    result.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;
    result.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
    result.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;
    result.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
    result.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
    result.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;
    result.m31 = a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
    result.m32 = a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
    result.m33 = a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;

    return result;
}

Vector multMatrixVector(Matrix a, Vector v) {
    Vector result;
    result.v1 = a.m11*v.v1 + a.m12*v.v2 + a.m13*v.v3;
    result.v2 = a.m21*v.v1 + a.m22*v.v2 + a.m23*v.v3;
    result.v3 = a.m31*v.v1 + a.m32*v.v2 + a.m33*v.v3;
    return result;
}

Vector toVector(Point2f p) {
    Vector result;
    result.v1 = p.x;
    result.v2 = p.y;
    result.v3 = 1;
    return result;
}

Point2f toPoint(Vector v) {
  Point2f r;
  r.x = v.v1;
  r.y = v.v2;
  return r;
}

//subtracts v2 from v1;
Vector subtractV(Vector v1, Vector v2) {
    Vector result;
    result.v1 = v1.v1-v2.v1;
    result.v2 = v1.v2-v2.v2;
    result.v3 = v1.v3-v2.v3;
    return result;
}


#endif
