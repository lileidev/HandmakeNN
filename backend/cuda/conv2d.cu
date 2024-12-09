
#include "threads.cuh"
#include "datatype_dispatch.h"

namespace SimpleNet {

// N = (w - size + 2p) / stride + 1
template <int nt, int vt, typename T>
__global__ void Conv2d(T* input, T* kernel, int i_h, int i_w,
                       T* output, int o_h, int o_w,
                       int size, int stride, int pad, int o_numel) {
  int tid = threadIdx.x;
  int idx = nt * vt * blockIdx.x + tid;

  for (int v = 0; v < vt; ++v) {
    if (idx >= o_numel) return;

    int o_row = idx / o_w;
    int o_col = idx - row * o_w;

    int i_start_row = o_row * stride;
    int i_start_col = o_col * stride;

    T sum = static_cast<T>(0);
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        int i_row = i_start_row + i;
        int i_col = i_start_col + j;
        // padding area
        if (i_row < pad || i_row > (i_h + p) || i_col < pad || i_col > (i_w + p)) {
          return;
        }
        int i_idx = (i_start_row + i) * o_w + j + i_start_col;
        int k_idx = i * size + j;
        sum += input[i_idx] * kernel[k_idx];
      }
    }

    output[idx] = sum;

    idx += nt;
  }
}

void LaunchConv2d(void* input, void* kernel, int i_h, int i_w,
                  void* output, int o_h, int o_w,
                  int size, int stride, int pad,
                  SNDataType_t data_type) {
  int o_numel = o_h * o_w;

  dim3 block(threads_per_block);
  dim3 grid((o_numel + BlockWorkSize() - 1) / BlockWorkSize());

  DISPATH_TYPE_FLOAT(data_type, [=]() {
    Conv2d<threads_per_block, thread_work_size, scalar_t><<<grid, block, 0, 0>>>(static_cast<scalar_t *>(input),
                                                                                 static_cast<scalar_t *>(kernel),
                                                                                 i_h, i_w,
                                                                                 static_cast<scalar_t *>(output),
                                                                                 o_h, o_w,
                                                                                 size, stride, pad, o_numel);
  });
};

}
