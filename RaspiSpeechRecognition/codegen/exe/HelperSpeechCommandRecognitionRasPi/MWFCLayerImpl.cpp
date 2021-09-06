#include "MWFCLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWACLUtils.hpp"
#include <arm_neon.h>
#include <memory>
 MWFCLayerImpl::MWFCLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int m_NumInputFeatures, int m_NumOutputFeatures, const char* 
m_weights_file,  const char* m_bias_file) : MWCNNLayerImpl(layer, ntwk_impl) { 
setupIpArmTensors(); 
setCurrentLayerOpArmTensor(std::make_shared<arm_compute::Tensor>()); int 
dkLDkRwCBjeybwDHbKiE = m_NumInputFeatures * m_NumOutputFeatures;  uznbYLhhKtdvhPWaHJnR = 
CREATE_BUFFER(dkLDkRwCBjeybwDHbKiE); JxwPQNPACGfmGpNncpCY = 
CREATE_BUFFER(m_NumOutputFeatures); m_fcLayerWgtTensor.allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)(m_NumInputFeatures), (long unsigned int)(m_NumOutputFeatures)), 1, 
arm_compute::DataType::F32)); m_fcLayerBiasTensor.allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)(m_NumOutputFeatures)), 1, arm_compute::DataType::F32)); 
loadWeights(m_weights_file, dkLDkRwCBjeybwDHbKiE); loadBias(m_bias_file, 
m_NumOutputFeatures); } MWFCLayerImpl::~MWFCLayerImpl() { } void 
MWFCLayerImpl::propagateSize(){ MWCNNLayer* fcLayer = getLayer(); MWTensorBase* 
opTensor = fcLayer->getOutputTensor(); configureIpArmTensors(); 
arm_compute::Tensor* prevLayerarmTensor = getCurrentLayerIpArmTensor(); 
getCurrentLayerOpArmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(opTensor->getWidth()* 
opTensor->getHeight()*opTensor->getChannels()), (long unsigned 
int)(opTensor->getBatchSize()* opTensor->getSequenceLength())), 1, 
arm_compute::DataType::F32)); m_fcLayer = 
std::unique_ptr<arm_compute::NEFullyConnectedLayer>(new 
arm_compute::NEFullyConnectedLayer); m_fcLayer->configure(prevLayerarmTensor, 
&m_fcLayerWgtTensor, &m_fcLayerBiasTensor, getCurrentLayerOpArmTensor()); 
prepareWeights(); return; } void MWFCLayerImpl::allocate(){ MWCNNLayer* fcLayer 
= getLayer(); MWTensorBase* ipTensor = fcLayer->getInputTensor(); MWTensorBase* 
opTensor = fcLayer->getOutputTensor(); int CTCbzQMDaLxINPbODdng = 
ipTensor->getChannels(); int CqtPRJvHlGJFssiPzsOm = 
opTensor->getChannels(); 
MWACLUtils::allocateAndFillTensor<float>(m_fcLayerWgtTensor, uznbYLhhKtdvhPWaHJnR, 
CTCbzQMDaLxINPbODdng * CqtPRJvHlGJFssiPzsOm, isWgtsPadded); 
MWACLUtils::allocateAndFillTensor<float>(m_fcLayerBiasTensor, JxwPQNPACGfmGpNncpCY, 
CqtPRJvHlGJFssiPzsOm, isBiasPadded); return; } void 
MWFCLayerImpl::loadWeights(const char* QMNXyOvXaZDsCpiIJPsn, int dkLDkRwCBjeybwDHbKiE) 
{ float* vpXxoeEhdEosLSsYXkNG = GET_BUFFER(uznbYLhhKtdvhPWaHJnR); std::string fileString = 
getLinuxPath(QMNXyOvXaZDsCpiIJPsn); FILE* QhTWatiCfcWYsHdkcyhZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); 
MWCNNLayer::call_fread(vpXxoeEhdEosLSsYXkNG, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QhTWatiCfcWYsHdkcyhZ, QMNXyOvXaZDsCpiIJPsn); fclose(QhTWatiCfcWYsHdkcyhZ); } void 
MWFCLayerImpl::prepareWeights(){ float* wqggPBXZvtlxnxwngvAq = 
GET_BUFFER(uznbYLhhKtdvhPWaHJnR); MWCNNLayer* fcLayer = getLayer(); MWTensorBase* 
ipTensor = fcLayer->getInputTensor(); MWTensorBase* opTensor = 
fcLayer->getOutputTensor(); int CTCbzQMDaLxINPbODdng = 
ipTensor->getChannels() * ipTensor->getWidth() * ipTensor->getHeight(); int 
CqtPRJvHlGJFssiPzsOm = opTensor->getChannels(); int dkLDkRwCBjeybwDHbKiE = 
CTCbzQMDaLxINPbODdng * CqtPRJvHlGJFssiPzsOm;  if 
(ipTensor->getHeight() != 1 && ipTensor->getWidth() != 1) { float* 
vpXxoeEhdEosLSsYXkNG = (float*)malloc(sizeof(float) * ipTensor->getHeight() * 
ipTensor->getWidth()); for (int k = 0; k < dkLDkRwCBjeybwDHbKiE / 
ipTensor->getHeight() / ipTensor->getWidth(); k++) { for (int i = 0; i < 
ipTensor->getHeight() * ipTensor->getWidth(); i++) vpXxoeEhdEosLSsYXkNG[i] = 
wqggPBXZvtlxnxwngvAq[k * ipTensor->getHeight() * ipTensor->getWidth() + i]; for (int j 
= 0; j < ipTensor->getHeight(); j++) for (int i = 0; i < ipTensor->getWidth(); 
i++) wqggPBXZvtlxnxwngvAq[k * ipTensor->getHeight() * ipTensor->getWidth() + j * 
ipTensor->getWidth() + i] = vpXxoeEhdEosLSsYXkNG[j + i * ipTensor->getHeight()]; } 
free(vpXxoeEhdEosLSsYXkNG); } return; } void MWFCLayerImpl::loadBias(const char* 
QMNXyOvXaZDsCpiIJPsn, int CqtPRJvHlGJFssiPzsOm) { float* KHjdvykTFbUxdfZTFbqy = 
GET_BUFFER(JxwPQNPACGfmGpNncpCY); std::string fileString = 
getLinuxPath(QMNXyOvXaZDsCpiIJPsn); FILE* QhTWatiCfcWYsHdkcyhZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); 
MWCNNLayer::call_fread(KHjdvykTFbUxdfZTFbqy, sizeof(float), 
CqtPRJvHlGJFssiPzsOm, QhTWatiCfcWYsHdkcyhZ, QMNXyOvXaZDsCpiIJPsn); 
fclose(QhTWatiCfcWYsHdkcyhZ); return; } void MWFCLayerImpl::predict() { 
prepareIpArmTensorsForPredict(); m_fcLayer->run();
#if MW_FC_TAP
 MWTensorBase* opTensorBase = getLayer()->getOutputTensor(); 
mw_interm_tap(*getCurrentLayerOpArmTensor(), opTensorBase->getNumElements(), tap_count++);
#endif
 return; } void MWFCLayerImpl::deallocate() { if (isWgtsPadded){ 
m_fcLayerWgtTensor.allocator()->free(); isWgtsPadded = false; } if 
(isBiasPadded){ m_fcLayerBiasTensor.allocator()->free(); isWgtsPadded = false; 
} return; } void MWFCLayerImpl::cleanup() { FREE_BUFFER_MEMORY(uznbYLhhKtdvhPWaHJnR); 
FREE_BUFFER_MEMORY(JxwPQNPACGfmGpNncpCY); return; }