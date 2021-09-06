/* Copyright 2020 The MathWorks, Inc. */
#ifndef MWTENSOR_HPP
#define MWTENSOR_HPP

#include "MWTensorBase.hpp"

class MWCNNLayer;

// Helper functions used by the type-checking functions in MWTensor<T>.
// These are used in lieu of std::is_same<T,U>().
// We cannot use std::is_same<T,U>() since it is a C++11 language feature.
template <class T>
bool is_float() {
    return false;
}

template <>
inline bool is_float<float>() {
    return true;
}

template <class T>
bool is_int8() {
    return false;
}

template <>
inline bool is_int8<signed char>() {
    return true;
}

template <class T>
class MWTensor : public MWTensorBase {
  public:
    MWTensor()
        : MWTensorBase()
        , m_data(NULL){};
    MWTensor(int height,
             int width,
             int channels,
             int batchsize,
             int sequencelength,
             T* data,
             MWCNNLayer* owner,
             int srcport)
        : MWTensorBase(height, width, channels, batchsize, sequencelength, owner, srcport)
        , m_data(data){};
    ~MWTensor() {
    }

    void setData(T* data) {
        m_data = data;
    }

    T* getData() const {
        return m_data;
    }

    virtual bool isFloat() const {
        return is_float<T>();
    }

    virtual bool isInt8() const {
        return is_int8<T>();
    }

  private:
    T* m_data;
};


#endif
