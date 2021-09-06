/* Copyright 2019-2020 The MathWorks, Inc. */

// ARMNEON specific header for Custom Layer Base Class
#ifndef CUSTOM_LAYER_ARMNEON_HPP
#define CUSTOM_LAYER_ARMNEON_HPP

#include "MWCNNLayer.hpp"
#include <map>

class MWTargetNetworkImpl;
class MWTensorBase;

class MWCustomLayerForARMNEON : public MWCNNLayer {

  public:
    MWCustomLayerForARMNEON();
    ~MWCustomLayerForARMNEON();

    MWTargetNetworkImpl* m_ntwkImpl;

    void allocate();
    void deallocate();
    void cleanup();

  protected:
    void setupLayer(MWTargetNetworkImpl*);

    // reorder data to between SNCHW <--> SNCWH or SNCHW <--> SNHWC
    void reorderData(MWTensorBase* aTensor, int bufIndex,
            MWTensorBase::DIMSLABEL sourceLayout[], MWTensorBase::DIMSLABEL targetLayout[], bool isInputReorder);

    void prepareUnpaddedIpData();

    virtual void cleanupLayer(){};

    void setUnpaddedIpData(MWTensorBase* aTensor, float* bufPtr);
    float* getUnpaddedIpData(MWTensorBase* aTensor);
    void allocateOutputData(int);
    void allocateInputData(int);

    bool isSharedIpArmTensorData(MWTensorBase* aTensor);

  private:
    std::map<MWTensorBase*, float*> MW_mangled_ipUnPaddedData;
};

#endif
