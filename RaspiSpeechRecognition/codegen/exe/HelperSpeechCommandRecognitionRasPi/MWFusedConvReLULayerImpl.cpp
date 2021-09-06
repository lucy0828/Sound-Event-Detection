#include "MWFusedConvReLULayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWACLUtils.hpp"
#include <arm_neon.h>
#include <memory>
#include <cassert>
#include <cstring>
#include <cstdio>
#if MW_CONV_TAP
 extern void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int 
count); extern void mw_interm_tap(float* memBuf, int size, int count); extern 
int tap_count;
#endif
 MWFusedConvReLULayerImpl::MWFusedConvReLULayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int filt_H, int filt_W, int numGrps, int 
numChnls, int numFilts, int GIbahSoBBDrvvZduPEqU, int GLovsOhUpzOJhKgXUAJY, int 
DGzdAcREJHGXjyRzNjJV, int DCdZnqpcBnvXVgEsLBnz, int FpguQZSermqZCMRiUfML, 
int FshVHIJMRAhtQirYPlZd, int AuqaQHxmPQSyYRemQvyX, int 
BHuHNDGoRwGRouCxeMbw, int , const char* zFaEOIBQYqPoaerpaixN, const 
char* MgAiRWiTutoTMxKXjmHQ) : MWCNNLayerImpl(layer, ntwk_impl) , 
BdqURaHPmdnfzvtUvocl(filt_H) , BkwhtPQUCQKchmmimoXs(filt_W) , 
CCKWXUFWgrbBMjwfpOBN(numGrps) , GIbahSoBBDrvvZduPEqU(GIbahSoBBDrvvZduPEqU) , 
GLovsOhUpzOJhKgXUAJY(GLovsOhUpzOJhKgXUAJY) , 
DGzdAcREJHGXjyRzNjJV(DGzdAcREJHGXjyRzNjJV) , 
DCdZnqpcBnvXVgEsLBnz(DCdZnqpcBnvXVgEsLBnz) , 
FpguQZSermqZCMRiUfML(FpguQZSermqZCMRiUfML) , 
FshVHIJMRAhtQirYPlZd(FshVHIJMRAhtQirYPlZd) , 
AuqaQHxmPQSyYRemQvyX(AuqaQHxmPQSyYRemQvyX) , 
BHuHNDGoRwGRouCxeMbw(BHuHNDGoRwGRouCxeMbw) { setupIpArmTensors(); 
setCurrentLayerOpArmTensor(std::make_shared<arm_compute::Tensor>()); int 
dkLDkRwCBjeybwDHbKiE = numChnls * CCKWXUFWgrbBMjwfpOBN * numFilts * 
BdqURaHPmdnfzvtUvocl * BkwhtPQUCQKchmmimoXs; if (CCKWXUFWgrbBMjwfpOBN != 1 
&& numChnls == 1 && numFilts == 1) { 
m_fusedConvLayerWgtTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)BkwhtPQUCQKchmmimoXs, (long 
unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned int)CCKWXUFWgrbBMjwfpOBN), 
1, arm_compute::DataType::F32)); } else { 
m_fusedConvLayerWgtTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)BkwhtPQUCQKchmmimoXs, (long 
unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned int)numChnls, (long 
unsigned int)numFilts * CCKWXUFWgrbBMjwfpOBN), 1, arm_compute::DataType::F32)); 
} m_fusedConvLayerBiasTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)numFilts * CCKWXUFWgrbBMjwfpOBN), 
1, arm_compute::DataType::F32)); uznbYLhhKtdvhPWaHJnR = CREATE_BUFFER(dkLDkRwCBjeybwDHbKiE); 
JxwPQNPACGfmGpNncpCY = CREATE_BUFFER(CCKWXUFWgrbBMjwfpOBN * numFilts); 
loadWeights(zFaEOIBQYqPoaerpaixN, dkLDkRwCBjeybwDHbKiE); 
loadBias(MgAiRWiTutoTMxKXjmHQ, CCKWXUFWgrbBMjwfpOBN * numFilts); } 
MWFusedConvReLULayerImpl::~MWFusedConvReLULayerImpl() { } void 
MWFusedConvReLULayerImpl::propagateSize() { MWCNNLayer* FusedconvLayer = 
getLayer(); MWTensorBase* ipTensor = FusedconvLayer->getInputTensor(0); 
MWTensorBase* opTensor = FusedconvLayer->getOutputTensor(0); 
configureIpArmTensors(); arm_compute::Tensor* prevLayerarmTensor = 
getCurrentLayerIpArmTensor(); 
getCurrentLayerOpArmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)opTensor->getWidth(), (long 
unsigned int)opTensor->getHeight(), (long unsigned int)opTensor->getChannels(), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
if (CCKWXUFWgrbBMjwfpOBN != 1) { if (CCKWXUFWgrbBMjwfpOBN == 
ipTensor->getChannels()) { configureDepthWiseConvolution(); } else { 
configureGroupedConvolution(); } } else { m_fusedConvLayer = 
std::unique_ptr<arm_compute::NEConvolutionLayer>(new 
arm_compute::NEConvolutionLayer); m_fusedConvLayer->configure( 
prevLayerarmTensor, &m_fusedConvLayerWgtTensor, &m_fusedConvLayerBiasTensor, 
getCurrentLayerOpArmTensor(), arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, 
GIbahSoBBDrvvZduPEqU, FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, 
DGzdAcREJHGXjyRzNjJV, DCdZnqpcBnvXVgEsLBnz, 
arm_compute::DimensionRoundingType::FLOOR), arm_compute::WeightsInfo(false, 
(long unsigned int)BkwhtPQUCQKchmmimoXs, (long unsigned 
int)BdqURaHPmdnfzvtUvocl, (long unsigned int)opTensor->getChannels()), 
arm_compute::Size2D((size_t)(BHuHNDGoRwGRouCxeMbw), 
(size_t)(AuqaQHxmPQSyYRemQvyX)), arm_compute::ActivationLayerInfo( 
arm_compute::ActivationLayerInfo::ActivationFunction::RELU)); } return; } void 
MWFusedConvReLULayerImpl::configureDepthWiseConvolution() { 
arm_compute::Tensor* prevLayerarmTensor = getCurrentLayerIpArmTensor(); 
m_fusedDepthwiseconvLayer = 
std::unique_ptr<arm_compute::NEDepthwiseConvolutionLayer>( new 
arm_compute::NEDepthwiseConvolutionLayer); 
m_fusedDepthwiseconvLayer->configure( prevLayerarmTensor, 
&m_fusedConvLayerWgtTensor, &m_fusedConvLayerBiasTensor, 
getCurrentLayerOpArmTensor(), arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, 
GIbahSoBBDrvvZduPEqU, FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, 
DGzdAcREJHGXjyRzNjJV, DCdZnqpcBnvXVgEsLBnz, 
arm_compute::DimensionRoundingType::FLOOR), 1, 
arm_compute::ActivationLayerInfo( 
arm_compute::ActivationLayerInfo::ActivationFunction::RELU)); return; } void 
MWFusedConvReLULayerImpl::configureGroupedConvolution() { MWCNNLayer* 
FusedconvLayer = getLayer(); MWTensorBase* ipTensor = 
FusedconvLayer->getInputTensor(0); MWTensorBase* opTensor = 
FusedconvLayer->getOutputTensor(0); arm_compute::Tensor* prevLayerarmTensor = 
getCurrentLayerIpArmTensor(); m_fusedConvLayer = 
std::unique_ptr<arm_compute::NEConvolutionLayer>(new 
arm_compute::NEConvolutionLayer); m_fusedConvLayerSecondGroup = 
std::unique_ptr<arm_compute::NEConvolutionLayer>(new 
arm_compute::NEConvolutionLayer); m_prevLayer1 = new arm_compute::SubTensor( 
prevLayerarmTensor, arm_compute::TensorShape( (long unsigned 
int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), (long 
unsigned int)(ipTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN), (long unsigned 
int)ipTensor->getBatchSize()), arm_compute::Coordinates()); m_prevLayer2 = new 
arm_compute::SubTensor( prevLayerarmTensor, arm_compute::TensorShape( (long 
unsigned int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), 
(long unsigned int)(ipTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN), (long 
unsigned int)ipTensor->getBatchSize()), arm_compute::Coordinates(0, 0, 
ipTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN)); m_curLayer1 = new 
arm_compute::SubTensor( getCurrentLayerOpArmTensor(), arm_compute::TensorShape( 
(long unsigned int)opTensor->getWidth(), (long unsigned 
int)opTensor->getHeight(), (long unsigned int)(opTensor->getChannels() / 
CCKWXUFWgrbBMjwfpOBN), (long unsigned int)opTensor->getBatchSize()), 
arm_compute::Coordinates()); m_curLayer2 = new arm_compute::SubTensor( 
getCurrentLayerOpArmTensor(), arm_compute::TensorShape( (long unsigned 
int)opTensor->getWidth(), (long unsigned int)opTensor->getHeight(), (long 
unsigned int)(opTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN), (long unsigned 
int)opTensor->getBatchSize()), arm_compute::Coordinates(0, 0, 
opTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN)); m_fusedConvLayerWgtMWTensor = 
new arm_compute::SubTensor( &m_fusedConvLayerWgtTensor, 
arm_compute::TensorShape( (long unsigned int)BdqURaHPmdnfzvtUvocl, (long 
unsigned int)BkwhtPQUCQKchmmimoXs, (long unsigned 
int)(ipTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN), (long unsigned 
int)(opTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN)), 
arm_compute::Coordinates()); m_fusedConvLayerWgtTensor2 = new 
arm_compute::SubTensor( &m_fusedConvLayerWgtTensor, arm_compute::TensorShape( 
(long unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned 
int)BkwhtPQUCQKchmmimoXs, (long unsigned int)(ipTensor->getChannels() / 
CCKWXUFWgrbBMjwfpOBN), (long unsigned int)(opTensor->getChannels() / 
CCKWXUFWgrbBMjwfpOBN)), arm_compute::Coordinates(0, 0, 0, 
opTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN)); m_fusedConvLayerBiasMWTensor 
= new arm_compute::SubTensor( &m_fusedConvLayerBiasTensor, 
arm_compute::TensorShape( (long unsigned int)(opTensor->getChannels() / 
CCKWXUFWgrbBMjwfpOBN)), arm_compute::Coordinates()); 
m_fusedConvLayerBiasTensor2 = new arm_compute::SubTensor( 
&m_fusedConvLayerBiasTensor, arm_compute::TensorShape( (long unsigned 
int)(opTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN)), 
arm_compute::Coordinates(opTensor->getChannels() / CCKWXUFWgrbBMjwfpOBN)); if 
(opTensor->getBatchSize() > 1) { m_fusedConvLayer->configure( m_prevLayer1, 
m_fusedConvLayerWgtMWTensor, m_fusedConvLayerBiasMWTensor, m_curLayer1, 
arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, GIbahSoBBDrvvZduPEqU, 
FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, DGzdAcREJHGXjyRzNjJV, 
DCdZnqpcBnvXVgEsLBnz, arm_compute::DimensionRoundingType::FLOOR), 
arm_compute::WeightsInfo(false, (long unsigned int)BkwhtPQUCQKchmmimoXs, 
(long unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned 
int)opTensor->getChannels()), 
arm_compute::Size2D((size_t)(BHuHNDGoRwGRouCxeMbw), 
(size_t)(AuqaQHxmPQSyYRemQvyX))); m_fusedConvLayerSecondGroup->configure( 
m_prevLayer2, m_fusedConvLayerWgtTensor2, m_fusedConvLayerBiasTensor2, 
m_curLayer2, arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, GIbahSoBBDrvvZduPEqU, 
FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, DGzdAcREJHGXjyRzNjJV, 
DCdZnqpcBnvXVgEsLBnz, arm_compute::DimensionRoundingType::FLOOR), 
arm_compute::WeightsInfo(false, (long unsigned int)BkwhtPQUCQKchmmimoXs, 
(long unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned 
int)opTensor->getChannels()), 
arm_compute::Size2D((size_t)(BHuHNDGoRwGRouCxeMbw), 
(size_t)(AuqaQHxmPQSyYRemQvyX))); m_actLayer = 
std::unique_ptr<arm_compute::NEActivationLayer>(new 
arm_compute::NEActivationLayer); 
m_actLayer->configure(getCurrentLayerOpArmTensor(), nullptr, 
arm_compute::ActivationLayerInfo( 
arm_compute::ActivationLayerInfo::ActivationFunction::RELU)); } else { 
m_fusedConvLayer->configure( m_prevLayer1, m_fusedConvLayerWgtMWTensor, 
m_fusedConvLayerBiasMWTensor, m_curLayer1, 
arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, GIbahSoBBDrvvZduPEqU, 
FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, DGzdAcREJHGXjyRzNjJV, 
DCdZnqpcBnvXVgEsLBnz, arm_compute::DimensionRoundingType::FLOOR), 
arm_compute::WeightsInfo(false, (long unsigned int)BkwhtPQUCQKchmmimoXs, 
(long unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned 
int)opTensor->getChannels()), 
arm_compute::Size2D((size_t)(BHuHNDGoRwGRouCxeMbw), 
(size_t)(AuqaQHxmPQSyYRemQvyX)), arm_compute::ActivationLayerInfo( 
arm_compute::ActivationLayerInfo::ActivationFunction::RELU)); 
m_fusedConvLayerSecondGroup->configure( m_prevLayer2, 
m_fusedConvLayerWgtTensor2, m_fusedConvLayerBiasTensor2, m_curLayer2, 
arm_compute::PadStrideInfo(GLovsOhUpzOJhKgXUAJY, GIbahSoBBDrvvZduPEqU, 
FpguQZSermqZCMRiUfML, FshVHIJMRAhtQirYPlZd, DGzdAcREJHGXjyRzNjJV, 
DCdZnqpcBnvXVgEsLBnz, arm_compute::DimensionRoundingType::FLOOR), 
arm_compute::WeightsInfo(false, (long unsigned int)BkwhtPQUCQKchmmimoXs, 
(long unsigned int)BdqURaHPmdnfzvtUvocl, (long unsigned 
int)opTensor->getChannels()), 
arm_compute::Size2D((size_t)(BHuHNDGoRwGRouCxeMbw), 
(size_t)(AuqaQHxmPQSyYRemQvyX)), arm_compute::ActivationLayerInfo( 
arm_compute::ActivationLayerInfo::ActivationFunction::RELU)); } return; } void 
MWFusedConvReLULayerImpl::predict() { MWCNNLayer* FusedconvLayer = getLayer(); 
MWTensorBase* opTensorBase = FusedconvLayer->getOutputTensor(0); MWTensorBase* 
ipTensorBase = FusedconvLayer->getInputTensor(0); 
prepareIpArmTensorsForPredict(); if (CCKWXUFWgrbBMjwfpOBN == 1) { 
m_fusedConvLayer->run(); } else { if (CCKWXUFWgrbBMjwfpOBN == 
ipTensorBase->getChannels()) { m_fusedDepthwiseconvLayer->run(); } else { 
m_fusedConvLayer->run(); m_fusedConvLayerSecondGroup->run(); if 
(opTensorBase->getBatchSize() > 1) { m_actLayer->run(); } } }
#if MW_CONV_TAP
 mw_interm_tap(*getCurrentLayerOpArmTensor(), opTensorBase->getNumElements(), tap_count++);
#endif
 return; } void MWFusedConvReLULayerImpl::allocate() { MWCNNLayer* 
FusedconvLayer = getLayer(); MWTensorBase* opTensor = 
FusedconvLayer->getOutputTensor(0); MWTensorBase* ipTensor = 
FusedconvLayer->getInputTensor(0); int dkLDkRwCBjeybwDHbKiE = ipTensor->getChannels() 
/ CCKWXUFWgrbBMjwfpOBN * opTensor->getChannels() * BdqURaHPmdnfzvtUvocl * 
BkwhtPQUCQKchmmimoXs; 
MWACLUtils::allocateAndFillTensor<float>(m_fusedConvLayerWgtTensor, 
uznbYLhhKtdvhPWaHJnR, dkLDkRwCBjeybwDHbKiE, isWgtsPadding); 
MWACLUtils::allocateAndFillTensor<float>(m_fusedConvLayerBiasTensor, 
JxwPQNPACGfmGpNncpCY, opTensor->getChannels(), isBiasPadding); return; } void 
MWFusedConvReLULayerImpl::deallocate() { MWCNNLayer* FusedconvLayer = 
getLayer(); MWTensorBase* ipTensorBase = FusedconvLayer->getInputTensor(0); if 
(CCKWXUFWgrbBMjwfpOBN != 1 && CCKWXUFWgrbBMjwfpOBN != 
ipTensorBase->getChannels()) { delete m_prevLayer1; delete m_prevLayer2; delete 
m_curLayer1; delete m_curLayer2; delete m_fusedConvLayerWgtMWTensor; delete 
m_fusedConvLayerWgtTensor2; delete m_fusedConvLayerBiasMWTensor; delete 
m_fusedConvLayerBiasTensor2; } if (isWgtsPadding) { 
m_fusedConvLayerWgtTensor.allocator()->free(); isWgtsPadding = false; } if 
(isBiasPadding) { m_fusedConvLayerWgtTensor.allocator()->free(); isWgtsPadding 
= false; } return; } void MWFusedConvReLULayerImpl::cleanup() { 
FREE_BUFFER_MEMORY(uznbYLhhKtdvhPWaHJnR); FREE_BUFFER_MEMORY(JxwPQNPACGfmGpNncpCY); return; } 
void MWFusedConvReLULayerImpl::loadWeights(const char* QMNXyOvXaZDsCpiIJPsn, int 
dkLDkRwCBjeybwDHbKiE) { float* wqggPBXZvtlxnxwngvAq = GET_BUFFER(uznbYLhhKtdvhPWaHJnR); std::string 
fileString = getLinuxPath(QMNXyOvXaZDsCpiIJPsn); FILE* QhTWatiCfcWYsHdkcyhZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); 
MWCNNLayer::call_fread(wqggPBXZvtlxnxwngvAq, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QhTWatiCfcWYsHdkcyhZ, QMNXyOvXaZDsCpiIJPsn); fclose(QhTWatiCfcWYsHdkcyhZ); return; } void 
MWFusedConvReLULayerImpl::loadBias(const char* QMNXyOvXaZDsCpiIJPsn, int 
dkLDkRwCBjeybwDHbKiE) { float* KHjdvykTFbUxdfZTFbqy = GET_BUFFER(JxwPQNPACGfmGpNncpCY); std::string 
fileString = getLinuxPath(QMNXyOvXaZDsCpiIJPsn); FILE* QhTWatiCfcWYsHdkcyhZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); 
MWCNNLayer::call_fread(KHjdvykTFbUxdfZTFbqy, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QhTWatiCfcWYsHdkcyhZ, QMNXyOvXaZDsCpiIJPsn); fclose(QhTWatiCfcWYsHdkcyhZ); return; }