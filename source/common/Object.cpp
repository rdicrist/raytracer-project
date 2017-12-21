//////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////


#include "common.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

//p0 is ray origin and v is direction (both in world space)
Object::IntersectionValues Sphere::intersect(vec4 p0_w, vec4 V_w){
  IntersectionValues result;
  //TODO: Ray-sphere setup
    
    //transform ray origin and direction into objectcoordinates
    //c is modelview
    vec4 p0_o = INVC * p0_w;
    vec4 V_o = INVCStar * V_w;
    double magnitude = length(V_o);
    
    V_o = normalize(V_o);
    //intersect them in object space
    
    //will give back tvalue and other things that come from that back into world space
    result.t_o = raySphereIntersection(p0_o, V_o);
    
    result.t_w = result.t_o/magnitude;
    
    //the intersection point in world coordinates
    result.P_w =p0_w + result.t_w * V_w; result.P_w /= result.P_w.w;
    
    //the normal in object space
    result.P_o = p0_o + result.t_o * V_o;   result.P_o /= result.P_o.w;
    result.N_o = result.P_o - vec4(0,0,0,1);
    //result.N_o =vec4(0,0,1,0);
    
    //the normal in world coordinates
    //Nws = (C-1)T Nos
    
    result.N_w = TRANINVC * result.N_o;
    result.N_w.w = 0;
    result.N_w = normalize(result.N_w);
    return result;
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin O and radius r    : Find t ------- */
double Sphere::raySphereIntersection(vec4 p0, vec4 V, vec4 O, double r){
  //TODO: Ray-sphere intersection;
    double a = 1.0;
    double b = dot(2.0*V, p0-O);
    double c = length(p0-O)*length(p0-O) - r*r;
    
    double in_sqrt = b*b - 4.0*a*c;
    
    if (in_sqrt < 0.0){
        return std::numeric_limits< double >::infinity();
    }
    
    double t_plus = (-b + sqrt(in_sqrt)) / 2.0*a;
    double t_minus = (-b - sqrt(in_sqrt)) / 2.0*a;
    
    //if very small, it doesnt hit at all
    if (t_plus < 1e-3){
        t_plus = std::numeric_limits< double >::infinity();
    }
    if (t_minus < 1e-3){
        t_minus = std::numeric_limits< double >::infinity();
    }
    
  return fmin(t_plus, t_minus);
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0_w, vec4 V_w){
  IntersectionValues result;
  //TODO: Ray-square setup
    //transform ray origin and direction into objectcoordinates
    //c is modelview
    vec4 p0_o = INVC * p0_w;
    vec4 V_o = INVCStar * V_w;
    double magnitude = length(V_o);
    V_o = normalize(V_o);
    //intersect them in object space
    
    //will give back tvalue and other things that come from that back into world space
    result.t_o = raySquareIntersection(p0_o, V_o);
    
    result.t_w = (result.t_o/magnitude);
    
    //the intersection point in world coordinates
    result.P_o = p0_o + result.t_o * V_o;
    result.P_w =p0_w + result.t_w * V_w; //result.P_w /= result.P_w.w;
    
    //the normal in object space
      //result.P_o /= result.P_o.w;
    //result.N_o = result.P_o  - vec4(0,0,0,1);
    result.N_o =vec4(0,0,1,0);
    
    //the normal in world coordinates
    //Nws = (C-1)T Nos
    
    result.N_w = TRANINVC * result.N_o;
    result.N_w.w = 0;
    result.N_w = normalize(result.N_w);
    return result;
    
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
//p0 is the start of the ray, V is the direction of the ray
double Square::raySquareIntersection(vec4 p0, vec4 V){
  //TODO: Ray-square intersection;
    //t = Normal ·(S – P1) / (N ·(V))-> when 0, its not intersecting
    vec4 s = vec4(0,0,0,1);
    vec4 normal = vec4(0,0,1,0);

//    if(!(p.x >= (-1 - EPSILON) && p.x <= (1 + EPSILON) && p.y >= (-1 - EPSILON) && p.y <= (1 + EPSILON))) {
//        t = std::numeric_limits< double >::infinity();


    double check = dot(normal, V);
    if (check == 0) {
        return std::numeric_limits< double >::infinity();
    }
    //when i get to final part, -1 + some epsilon, 1 plus some epsilon etc
    else {
        double t = dot(normal, (s-p0)) / check;
        vec4 checkPoint = p0 + t * V;
        //test if in
        if (t < EPSILON){
            return std::numeric_limits< double >::infinity();
        }
        if (checkPoint.x > (-1 - EPSILON) && checkPoint.x < (1 + EPSILON) && checkPoint.y > (-1 - EPSILON) && checkPoint.y < (1 + EPSILON)){
            return t;
        }
    }


  return std::numeric_limits< double >::infinity();
}
