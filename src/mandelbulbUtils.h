#pragma once

#include <cmath>
#include "Spherical.h"
#include "ofAppRunner.h"
#include "ofMain.h"

namespace constants {

constexpr int dimension = 128;
constexpr int exponential = 8;
constexpr int maxIteration = 20;
constexpr int vectorScale = 50;
constexpr float pointRadius = 0.25f;
constexpr float pi = 3.1415926535f;

}  // namespace constants

namespace mandelbulbUtils {

inline auto spherical(float x, float y, float z) -> Spherical {
  auto r = sqrt(x * x + y * y + z * z);
  auto theta = atan2(sqrt(x * x + y * y), z);
  auto phi = atan2(y, x);

  Spherical spherical{r, theta, phi};
  return spherical;
}

}  // namespace mandelbulbUtils
