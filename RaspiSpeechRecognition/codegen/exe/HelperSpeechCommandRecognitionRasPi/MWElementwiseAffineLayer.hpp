/* Copyright 2017 The MathWorks, Inc. */

#ifndef __ELEMENTWISE_AFFINE_LAYER_HPP
#define __ELEMENTWISE_AFFINE_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

class MWElementwiseAffineLayer: public MWCNNLayer
{
  private:


  public:
    MWElementwiseAffineLayer();
    ~MWElementwiseAffineLayer();
    void createElementwiseAffineLayer(MWTargetNetworkImpl*, MWTensorBase*, int, int, int, int, int, int, bool, int, int, const char*, const char*, int);
    void propagateSize();
};
#endif

