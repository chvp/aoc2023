#include <math.h>

long get_interval(long time, long record) {
  double a = -1.0;
  double b = (double) time;
  double c = (double) -record;

  long low = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
  long high = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

  // If the high point is an exact integer solution, we don't want to count it
  if (-high * high + time * high == record) {
    high--;
  }

  return high - low;
}
