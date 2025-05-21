#ifndef UTILS_H
#define UTILS_H

static inline int
max_int(int a, int b)
{
  return (a > b) ? a : b;
}

static inline int
min_int(int a, int b)
{
  return (a < b) ? a : b;
}

static inline float
max_float(float a, float b)
{
  return (a > b) ? a : b;
}

static inline float
min_float(float a, float b)
{
  return (a < b) ? a : b;
}

#endif // UTILS_H