#include "MWSoftmaxLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include <arm_neon.h>
#include <memory>
 class MWTargetNetworkImpl; MWSoftmaxLayerImpl::MWSoftmaxLayerImpl(MWCNNLayer* 
layer, MWTargetNetworkImpl* ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) , 
m_doesChannelwiseSoftmax(false) { setupIpArmTensors(); 
setCurrentLayerOpArmTensor(std::make_shared<arm_compute::Tensor>()); } 
MWSoftmaxLayerImpl::~MWSoftmaxLayerImpl() { } void 
MWSoftmaxLayerImpl::propagateSize() { MWCNNLayer* sfmxLayer = getLayer(); 
MWTensorBase* ipTensor = sfmxLayer->getInputTensor(); MWTensorBase* opTensor = 
sfmxLayer->getOutputTensor(); m_softmaxLayer = 
std::unique_ptr<arm_compute::NESoftmaxLayer>(new arm_compute::NESoftmaxLayer); 
configureIpArmTensors(); arm_compute::Tensor* prevLayerarmTensor = 
getCurrentLayerIpArmTensor(); bool doesPrevLayerHas2DArmTensor = 
prevLayerarmTensor->info()->num_dimensions() <= 2 && ipTensor->getHeight() == 1 
&& ipTensor->getWidth() == 1; if (doesPrevLayerHas2DArmTensor) { 
getCurrentLayerOpArmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape( (long unsigned int)opTensor->getChannels(), (long 
unsigned int)(opTensor->getBatchSize() * opTensor->getSequenceLength())), 1, 
arm_compute::DataType::F32)); } else { m_doesChannelwiseSoftmax = true; 
getCurrentLayerOpArmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape( (long unsigned int)opTensor->getWidth(), (long 
unsigned int)opTensor->getHeight(), (long unsigned int)opTensor->getChannels(), 
(long unsigned int)(opTensor->getBatchSize() * opTensor->getSequenceLength())), 
1, arm_compute::DataType::F32)); } if (!m_doesChannelwiseSoftmax) { 
m_softmaxLayer->configure(prevLayerarmTensor, getCurrentLayerOpArmTensor()); } 
else { permuteToNHWC = std::unique_ptr<arm_compute::NEPermute>(new 
arm_compute::NEPermute); permuteToNCHW = 
std::unique_ptr<arm_compute::NEPermute>(new arm_compute::NEPermute); 
arm_compute::PermutationVector nhwcPermuteDims(2, 0, 1), nchwPermuteDims(1, 2, 
0); inputNHWCArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)ipTensor->getChannels(), (long 
unsigned int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), 
(long unsigned int)ipTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
permuteToNHWC->configure(prevLayerarmTensor, &inputNHWCArmTensor, 
nhwcPermuteDims); 
tmpSfmaxNHWCArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)ipTensor->getChannels(), (long 
unsigned int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), 
(long unsigned int)ipTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_softmaxLayer->configure(&inputNHWCArmTensor, &tmpSfmaxNHWCArmTensor); 
permuteToNCHW->configure(&tmpSfmaxNHWCArmTensor, getCurrentLayerOpArmTensor(), 
nchwPermuteDims); } return; } void MWSoftmaxLayerImpl::allocate() { if 
(m_doesChannelwiseSoftmax) { inputNHWCArmTensor.allocator()->allocate(); 
tmpSfmaxNHWCArmTensor.allocator()->allocate(); } return; } void 
MWSoftmaxLayerImpl::predict() { prepareIpArmTensorsForPredict(); if 
(!m_doesChannelwiseSoftmax) { m_softmaxLayer->run(); } else {  
permuteToNHWC->run(); m_softmaxLayer->run(); permuteToNCHW->run(); }
#if MW_SFMX_TAP
 MWCNNLayer* sfmxLayer = getLayer(); MWTensorBase* opTensorBase = 
sfmxLayer->getOutputTensor(); mw_interm_tap(*getCurrentLayerOpArmTensor(), 
opTensorBase->getNumElements(), tap_count++);
#endif
 return; } void MWSoftmaxLayerImpl::deallocate() { if 
(m_doesChannelwiseSoftmax) { inputNHWCArmTensor.allocator()->free(); 
tmpSfmaxNHWCArmTensor.allocator()->free(); } return; }