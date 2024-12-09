#pragma once 

#include "cuda_fp16.h"
#include "cuda_bf16.h"
#include <cstdint>

namespace SimpleNet {

enum SNDataType_t {
  SN_TYPE_INVALID = 0,
  SN_TYPE_FLOAT = 1,
  SN_TYPE_DOUBLE = 2,
  SN_TYPE_HALF = 3,
  SN_TYPE_BHALF = 4,
  SN_TYPE_INT32 = 5,
  SN_TYPE_INT64 = 6
};

}
