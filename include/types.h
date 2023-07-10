#ifndef TYPES_H
#define TYPES_H

#ifdef SINGLE_PRECISION
#define REAL float
#else
#define REAL double
#endif

#define VOID int

#define PI 3.141592653589793238462643383279502884197169399375105820974944592308
#define radian(angle) (angle * PI / 180.0)

#define SUCCESSED 0
#define FAILED 1

#endif // TYPES_H
