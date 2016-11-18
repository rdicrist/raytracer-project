//
//  Object.h
//  RAYTRACER
//
//  Created by Brian Summa on 11/17/15.
//
//

#ifndef __RAYTRACER__Object__
#define __RAYTRACER__Object__

#include "Angel.h"
#include "ObjMesh.h"
#include <assert.h>

#define EPSILON  1e-3

class Object{
public:
  
  std::string name;
  
  friend class Sphere;
  friend class Square;
  
  typedef struct{
    vec4 color;
    vec4 Kd;
    float Ks;
    float Kn;
    float Kt;
    float Ka;
    float Kr;
  } ShadingValues;
  
  typedef struct{
    //t in object space
    double t_o;
    //t in world
    double t_w;
    //intersection point in object space
    vec4 P_o;
    //intersection point in world space
    vec4 P_w;
    //normal at intersection in object space
    vec3 N_o;
    //normal at intersection  in world space
    vec3 N_w;
    //The object hit
    Object *object;
  } IntersectionValues;
  
  
  Object(std::string name): name(name)  {};
  ~Object() {};
  
  Mesh mesh;
  ShadingValues shadingValues;
  
private:
  mat4 C;
  mat4 INVC;
  mat4 INVCStar;
  mat4 TRANINVC;
  
public:
  
  void setShadingValues(ShadingValues _shadingValues){shadingValues = _shadingValues;}
  
  void setModelView(mat4 modelview){
    C = modelview;
    INVC = invert(modelview);
    mat4 CStar = modelview;
    CStar[0][3] = 0;
    CStar[1][3] = 0;
    CStar[2][3] = 0;
    INVCStar = invert(CStar);
    TRANINVC = transpose(invert(modelview));
  }
  
  mat4 getModelView(){ return C; }
  
  virtual IntersectionValues intersect(vec4 p0, vec4 V)=0;
  
  
};

class Sphere : public Object{
public:
  
  Sphere(std::string name) : Object(name) { mesh.makeSubdivisionSphere(8); };
  
  /* ------------------------------------------------------------------------ */
  /* ------------------- Intersect Ray = R_w + t*dir_w  ---------------------- */
  virtual IntersectionValues intersect(vec4 R_w, vec4 dir_w){
    IntersectionValues result;
    result.object = this;
    //TODO FOR PROJECT
    return result;
  }
  
  /* ------------------------------------------------------------------------ */
  /* ----Ray = R_o + t*dir_o  sphere at origin O and radius r : Find t ------ */
  double sphereIntersect(vec4 R_o, vec4 dir_o, vec4 O=vec4(0.0, 0.0, 0.0, 1.0), double r=1.0){
    //TODO FOR PROJECT
    return std::numeric_limits< double >::infinity();
  }
  
  
};

class Square : public Object{
public:
  Square(std::string name) : Object(name) {
    
    mesh.vertices.resize(6);
    mesh.uvs.resize(6);
    mesh.normals.resize(6);
    
    mesh.vertices[0]=vec4(-1.0, -1.0, 0.0, 1.0);
    mesh.uvs[0] = vec2(0.0,0.0);
    mesh.vertices[1]=vec4(1.0, 1.0, 0.0, 1.0);
    mesh.uvs[1] = vec2(1.0,1.0);
    mesh.vertices[2]=vec4(1.0, -1.0, 0.0, 1.0);
    mesh.uvs[2] = vec2(1.0,0.0);
    
    mesh.vertices[3]=vec4(-1.0, -1.0, 0.0, 1.0);
    mesh.uvs[3] = vec2(0.0,0.0);
    mesh.vertices[4]=vec4(1.0, 1.0, 0.0, 1.0);
    mesh.uvs[4] = vec2(1.0,1.0);
    mesh.vertices[5]=vec4(-1.0, 1.0, 0.0, 1.0);
    mesh.uvs[5] = vec2(0.0,1.0);
    
    mesh.normals[0]= vec3(0, 0, 1.0);
    mesh.normals[1]= vec3(0, 0, 1.0);
    mesh.normals[2]= vec3(0, 0, 1.0);
    mesh.normals[3]= vec3(0, 0, 1.0);
    mesh.normals[4]= vec3(0, 0, 1.0);
    mesh.normals[5]= vec3(0, 0, 1.0);
    
  };
  
  /* ------------------------------------------------------------------------ */
  /* -------------------- Ray = R_w + t_w*dir_w  with square ---------------- */
  virtual IntersectionValues intersect(vec4 R_w, vec4 dir_w){
    IntersectionValues result;
    result.object = this;
    //TODO FOR PROJECT
    return result;
  }
  
  /* ------------------------------------------------------------------------ */
  /* ----------------- Ray = R_o + t_o*dir_o with square: Find t ------------ */
  double squareIntersect(vec4 R_o, vec4 dir_o){
    //TODO FOR PROJECT
    return std::numeric_limits< double >::infinity();
  }
  
};
#endif /* defined(__RAYTRACER__Objects__) */
