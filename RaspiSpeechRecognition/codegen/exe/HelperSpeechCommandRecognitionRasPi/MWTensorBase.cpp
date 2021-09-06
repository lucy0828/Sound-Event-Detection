/* Copyright 2020 The MathWorks, Inc. */

#include "MWTensorBase.hpp"

MWTensorBase::MWTensorBase(int height,
                           int width,
                           int channels,
                           int batchsize,
                           int sequencelength,
                           MWCNNLayer* owner,
                           int srcport)
    : m_owner(owner)
    , m_srcport(srcport)
    , opBufIndex(-1)
    , m_size(5) {
    m_shape[H] = height;
    m_shape[W] = width;
    m_shape[C] = channels;
    m_shape[N] = batchsize;
    m_shape[S] = sequencelength;

    m_dimsLayout[0] = S;
    m_dimsLayout[1] = N;
    m_dimsLayout[2] = C;
    m_dimsLayout[3] = H;
    m_dimsLayout[4] = W;
}


void MWTensorBase::getShape(int tensorShape[5]) const {
    tensorShape[H] = m_shape[H];
    tensorShape[W] = m_shape[W];
    tensorShape[C] = m_shape[C];
    tensorShape[N] = m_shape[N];
    tensorShape[S] = m_shape[S];
}

void MWTensorBase::getLayout(DIMSLABEL dimsLayout[]) {
    for (int idx = 0; idx < m_size; idx++) {
        dimsLayout[idx] = m_dimsLayout[idx];
    }
}

void MWTensorBase::setLayout(DIMSLABEL dimsLayout[]) {
    for (int idx = 0; idx < m_size; idx++) {
        m_dimsLayout[idx] = dimsLayout[idx];
    }
}

void MWTensorBase::getDimsByLayout(DIMSLABEL layout[], int size, int dims[]) {
    // size is size of layout
    // for TensorRT layout size < m_size
    for (int idx = 0; idx < size; idx++) {
        dims[idx] = m_shape[layout[idx]];
    }
}

/********************************************************************
                         Static Methods
*********************************************************************/

// Inputs
//   dims: array of dimensions, sorted from most-slowly varying dimension to fastest-varying
//   dimension left-to-right size: number of dimensions
// Output:
//   stride: an array of the same size as dimensions specifying the stride of the corresponding
//   dimension
//
//   The right-most stride should always be 1. The stride of any other dimension will be the
//   cumulative product of all more-slowly-varying dimensions. Thus, if dims is passed in as
//   {seqLength, batchSize, channels, height, width}, the output strides will be SNCHW.
void MWTensorBase::getStrides(const int dims[], int size, int stride[]) {
    int totalStride = 1;
    for (int i = 0; i < size; ++i) {
        stride[size - 1 - i] = totalStride;
        totalStride *= dims[size - 1 - i];
    }
}


// Inputs
//   srcLayout : array of DIMSLABEL for the source
//   destLayout : array of DIMSLABEL for the destination
//   dims: array of dimensions, sorted from most-slowly varying dimension to fastest-varying
//   dimension left-to-right
//   size: number of dimensions
// Output:
//   stride: an array of the same size as dimensions specifying the stride of the DIMSLABEL
//      dimension corresponding to the source
//
// If source is {H, W, C} and dest is {C, W, H} the strides for transforming data from source to
// dest is {1, H, WH} The stride {1, H, WH} correspond to the source layout of {H, W, C}. Consumer
// of this stride is cudnn/mkldnn API's where "dims" correspond to the source layout

void MWTensorBase::getTransformStrides(const DIMSLABEL srcLayout[],
                                       const DIMSLABEL destLayout[],
                                       const int dims[],
                                       int size,
                                       int strides[]) {
    // conversion from src layout to dest layout

    for (int idxSrc = 0; idxSrc < size; idxSrc++) {
        int totalStride = 1;
        bool foundDim = false;
        for (int idxDest = 0; idxDest < size; idxDest++) {
            if (srcLayout[idxSrc] == destLayout[idxDest]) {
                foundDim = true;
            }
            if (foundDim && idxDest < (size - 1)) {
                // loop over dimensions to the right to find total stride for current dimension
                totalStride *= dims[idxDest + 1];
            }
        }
        strides[idxSrc] = totalStride;
    }
}

// Inputs
//   srcLayout : array of DIMSLABEL for the source
//   destLayout : array of DIMSLABEL for the destination
//   size: number of dimensions of the source/dest layout
// Output:
//   order: an array of the same size as layout specifying the order by which the source needs
//      needs to be permuted to obtain dest layout
//
// If source is {H, W, C} and dest is {C, W, H}, then order is {2, 1, 0}
void MWTensorBase::getPermutationOrder(const DIMSLABEL srcLayout[],
                                       const DIMSLABEL destLayout[],
                                       int size,
                                       int order[]) {

    // conversion from src layout to dest layout
    for (int idxDest = 0; idxDest < size; idxDest++) {
        for (int idxSrc = 0; idxSrc < size; idxSrc++) {
            if (srcLayout[idxSrc] == destLayout[idxDest]) {
                order[idxDest] = idxSrc;
                break;
            }
        }
    }
}
