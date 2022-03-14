#pragma once

#include "ofAppRunner.h"
#include "ofMain.h"

class Spherical {
 public:
  float r, theta, phi;
  Spherical(float r_, float theta_, float phi_) : r{r_}, theta{theta_}, phi{phi_} {}
};
