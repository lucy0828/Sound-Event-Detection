#include "MWMaxPoolingLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include <arm_neon.h>
#include <memory>
 class MWTargetNetworkImpl; 
MWMaxPoolingLayerImpl::MWMaxPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int GDRXdUDklKFEYEfifhIH,  int GFggoMvRWucDMqzlWzCl,  
int GIbahSoBBDrvvZduPEqU,  int GLovsOhUpzOJhKgXUAJY, int DGzdAcREJHGXjyRzNjJV, int 
DCdZnqpcBnvXVgEsLBnz,  int FpguQZSermqZCMRiUfML, int FshVHIJMRAhtQirYPlZd, 
bool GZGFVDrXwFLJleoTDywO, int , const char* ,  int etjQLJVQCaeAXRWYtqOl) : 
MWCNNLayerImpl(layer, ntwk_impl) , GDRXdUDklKFEYEfifhIH(GDRXdUDklKFEYEfifhIH) , 
GFggoMvRWucDMqzlWzCl(GFggoMvRWucDMqzlWzCl) , GIbahSoBBDrvvZduPEqU(GIbahSoBBDrvvZduPEqU) , 
GLovsOhUpzOJhKgXUAJY(GLovsOhUpzOJhKgXUAJY) , 
DGzdAcREJHGXjyRzNjJV(DGzdAcREJHGXjyRzNjJV) , 
DCdZnqpcBnvXVgEsLBnz(DCdZnqpcBnvXVgEsLBnz) , 
FpguQZSermqZCMRiUfML(FpguQZSermqZCMRiUfML) , 
FshVHIJMRAhtQirYPlZd(FshVHIJMRAhtQirYPlZd) { assert(etjQLJVQCaeAXRWYtqOl == 
1); assert(!GZGFVDrXwFLJleoTDywO); setupIpArmTensors(); 
setCurrentLayerOpArmTensor(std::make_shared<arm_compute::Tensor>()); } 
MWMaxPoolingLayerImpl::~MWMaxPoolingLayerImpl() { } float* 
MWMaxPoolingLayerImpl::getIndexData() { assert(false); } void 
MWMaxPoolingLayerImpl::propagateSize() { MWCNNLayer* maxPoolLayer = getLayer(); 
MWTensorBase* ipTensor = maxPoolLayer->getInputTensor(); MWTensorBase* opTensor 
= maxPoolLayer->getOutputTensor(); m_maxPoolLayer = 
std::unique_ptr<arm_compute::NEPoolingLayer>(new arm_compute::NEPoolingLayer); 
configureIpArmTensors(); arm_compute::Tensor* prevLayerarmTensor = 
getCurrentLayerIpArmTensor(); if ((GDRXdUDklKFEYEfifhIH == -1) && (GFggoMvRWucDMqzlWzCl 
== -1)) { GDRXdUDklKFEYEfifhIH = ipTensor->getHeight(); GFggoMvRWucDMqzlWzCl = 
ipTensor->getWidth(); } 
getCurrentLayerOpArmTensor()->allocator()->init(arm_compute::TensorInfo(arm_compute::TensorShape((long 
unsigned int)opTensor->getWidth(), (long unsigned int)opTensor->getHeight(), 
(long unsigned int)opTensor->getChannels(), (long unsigned 
int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32));
#if defined(USE_20_02_1_LIBRARY)
 m_maxPoolLayer->configure( prevLayerarmTensor, getCurrentLayerOpArmTensor(), 
arm_compute::PoolingLayerInfo( arm_compute::PoolingType::MAX, 
arm_compute::Size2D(GFggoMvRWucDMqzlWzCl, 
GDRXdUDklKFEYEfifhIH),arm_compute::DataLayout::NCHW, 
arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, GIbahSoBBDrvvZduPEqU, 
FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, DGzdAcREJHGXjyRzNjJV, 
DCdZnqpcBnvXVgEsLBnz, arm_compute::DimensionRoundingType::FLOOR)));
#else
 m_maxPoolLayer->configure( prevLayerarmTensor, getCurrentLayerOpArmTensor(), 
arm_compute::PoolingLayerInfo( arm_compute::PoolingType::MAX, 
arm_compute::Size2D(GFggoMvRWucDMqzlWzCl, GDRXdUDklKFEYEfifhIH), 
arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, GIbahSoBBDrvvZduPEqU, 
FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, DGzdAcREJHGXjyRzNjJV, 
DCdZnqpcBnvXVgEsLBnz, arm_compute::DimensionRoundingType::FLOOR)));
#endif
 return; } void MWMaxPoolingLayerImpl::predict() { 
prepareIpArmTensorsForPredict(); m_maxPoolLayer->run();
#if MW_POOL_TAP
 MWCNNLayer* maxPoolLayer = getLayer(); MWTensorBase* opTensorBase = 
maxPoolLayer->getOutputTensor(); mw_interm_tap(*getCurrentLayerOpArmTensor(), 
opTensorBase->getNumElements(), tap_count++);
#endif
 return; }