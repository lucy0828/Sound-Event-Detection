/* Copyright 2020 The MathWorks, Inc. */

#ifndef __MAX_POOLING_LAYER_IMPL_HPP
#define __MAX_POOLING_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"
#include <arm_neon.h>
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// maxpoolingLayer
class MWMaxPoolingLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NEPoolingLayer> m_maxPoolLayer;
    int GDRXdUDklKFEYEfifhIH;
    int GFggoMvRWucDMqzlWzCl;
    int GIbahSoBBDrvvZduPEqU;
    int GLovsOhUpzOJhKgXUAJY;
    int DGzdAcREJHGXjyRzNjJV;
    int DCdZnqpcBnvXVgEsLBnz;
    int FpguQZSermqZCMRiUfML;
    int FshVHIJMRAhtQirYPlZd;

    void propagateSize();
    void predict();

  public:
    MWMaxPoolingLayerImpl(MWCNNLayer*,
                          MWTargetNetworkImpl*,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          bool,
                          int,
                          const char*,
                          int);
    ~MWMaxPoolingLayerImpl();
    float* getIndexData();
};

#endif
