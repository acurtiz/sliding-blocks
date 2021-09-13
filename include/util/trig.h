#ifndef SLIDINGBLOCKS_INCLUDE_UTIL_TRIG_H_
#define SLIDINGBLOCKS_INCLUDE_UTIL_TRIG_H_

namespace sliding_blocks {

class Trig {
 public:
  static double ConvertRadiansToDegrees(double radians);
  static double ConvertDegreesToRadians(double degrees);
  static double NormalizeDegrees(double degrees);
  static double NormalizeRadiansBetweenZeroAndTwoPi(double radians);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_UTIL_TRIG_H_
