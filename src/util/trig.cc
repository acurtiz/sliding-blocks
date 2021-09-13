#include <cmath>
#include "util/trig.h"

namespace sliding_blocks {

double Trig::ConvertRadiansToDegrees(double radians) {
  return radians * 180 / M_PI;
}

double Trig::ConvertDegreesToRadians(double degrees) {
  return degrees * M_PI / 180;
}

double Trig::NormalizeDegrees(double degrees) {
  return ((int) (degrees + 360)) % 360;
}

/**
 * Returns the equivalent radians between 0 and 2 PI
 * @param radians between [-pi, pi]
 * @return
 */
double Trig::NormalizeRadiansBetweenZeroAndTwoPi(double radians) {

  return radians < 0 ?
         radians + 2 * M_PI :
         radians;
}

}
