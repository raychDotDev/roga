#pragma once
#include <inttypes.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef struct {
    u32 x;
    u32 y;
} v2u;

typedef struct {
    i32 x;
    i32 y;
} v2i;

typedef struct {
    f32 x;
    f32 y;
} v2f;

typedef struct {
    v2u pos;
    v2u size;
} u32rect;

typedef struct {
    v2i pos;
    v2i size;
} i32rect;

typedef struct {
    v2f pos;
    v2f size;
} f32rect;

typedef enum { b_false = 0, b_true = 1 } bool_t;

