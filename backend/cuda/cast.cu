


template <int nt, int vt, typename T1, typename T2>
__global__ void Cast(T1* input, T2* output, int numel) {
  int tid = threadIdx.x;
  int idx = nt * vt * blockIdx.x + tid;

  for (int v = 0; v < vt; ++v) {
    if (idx >= numel) return;

    output[idx] = scalar_cast<T2>(input[idx]);

    idx += nt;
  }
}


