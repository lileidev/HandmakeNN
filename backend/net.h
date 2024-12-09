#pragma once


class Conv2d {
 public:
  Conv2d(int N, int C, int H, int W, int size, int stride) : N_(N), C_(C), H_(H), W_(W), size_(size), stride_(stride) {}

  ~Conv2d() {}
  
  template <typename T>
  void forward(T* feature);

  template <typename T>
  T* inference_output_shape();

 private:
  int N_;
  int C_;
  int H_;
  int W_;

  int size_;
  int stride_;
  int pad_;

  void* weight_;
  void* bias_;
};
