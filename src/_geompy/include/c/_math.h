#ifndef _MATH_H
#define _MATH_H
#ifdef __cplusplus
extern "C" {
#endif

#define PSEUDO_SCALAR_PRODUCT(v1, v2, x, y) (*v2 - *v1) * (y - *(v1 + 1)) - (x - *v1) * (*(v2 + 1) - *(v1 + 1))

#ifdef __cplusplus
}
#endif
#endif /* !_MATH_H */