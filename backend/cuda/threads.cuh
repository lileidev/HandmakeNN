#pragma once

namespace SimpleNet {
  
const int threads_per_block = 256;
const int thread_work_size = 4;


const int BlockWorkSize() {
  return thread_work_size * threads_per_block;
}


} // namespace SimpleNet
