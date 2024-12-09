#pragma once

#include "data_type.h"

namespace SimpleNet {

template <SNDataType_t TYPE>
struct SN2CppDataType;

template <>
struct SN2CppDataType<SN_TYPE_FLOAT> {
  using type = float;
  static type t;
};

template <>
struct SN2CppDataType<SN_TYPE_DOUBLE> {
  using type = double;
  static type t;
};


template <>
struct SN2CppDataType<SN_TYPE_HALF> {
  using type = half;
  static type t;
};

template <>
struct SN2CppDataType<SN_TYPE_BHALF> {
  using type = __nv_bfloat16;
  static type t;
};

template <>
struct SN2CppDataType<SN_TYPE_INT32> {
  using type = int32_t;
  static type t;
};

template <>
struct SN2CppDataType<SN_TYPE_INT64> {
  using type = int64_t;
  static type t;
};


#define DISPATCH_TYPE_CASE(TYPE, ...)             \
  case TYPE:                                      \
    using scalar_t = SNDataType<TYPE>::type;      \
    return __VA_ARGS__();


#define DISPATH_TYPE_ALL(TYPE, ...)                 \
  switch (TYPE)                                     \
    DISPATCH_TYPE_CASE(SN_TYPE_FLOAT, __VA_ARGS__)  \
    DISPATCH_TYPE_CASE(SN_TYPE_DOUBLE, __VA_ARGS__) \
    DISPATCH_TYPE_CASE(SN_TYPE_HALF, __VA_ARGS__)   \
    DISPATCH_TYPE_CASE(SN_TYPE_BHALF, __VA_ARGS__)  \
    DISPATCH_TYPE_CASE(SN_TYPE_INT32, __VA_ARGS__)  \
    DISPATCH_TYPE_CASE(SN_TYPE_INT64, __VA_ARGS__)  \
    default:                                        \
      printf("invalid type\n");

#define DISPATH_TYPE_FLOAT(TYPE, ...)               \
  switch (TYPE)                                     \
    DISPATCH_TYPE_CASE(SN_TYPE_FLOAT, __VA_ARGS__)  \
    DISPATCH_TYPE_CASE(SN_TYPE_DOUBLE, __VA_ARGS__) \
    DISPATCH_TYPE_CASE(SN_TYPE_HALF, __VA_ARGS__)   \
    DISPATCH_TYPE_CASE(SN_TYPE_BHALF, __VA_ARGS__)  \
    default:                                        \
      printf("invalid type\n");


} // namespace SimpleNet
