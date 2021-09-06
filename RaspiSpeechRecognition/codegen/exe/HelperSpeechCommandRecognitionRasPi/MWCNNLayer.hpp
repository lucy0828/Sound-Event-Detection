/* Copyright 2020 The MathWorks, Inc. */
#ifndef CNN_LAYER_HPP
#define CNN_LAYER_HPP

#include "MWTensor.hpp"

#include <cstdio>
#include <string>
#include <map>
#include <cassert>
#include <stdexcept>

class MWTensorBase;
class MWCNNLayerImpl;

class MWCNNLayer {
  protected:
    std::string m_name;                    // Name of the layer
    std::map<int, MWTensorBase*> m_input;  // inputs
    std::map<int, MWTensorBase*> m_output; // outputs

    MWCNNLayerImpl* m_impl; // layer impl

    bool m_isCustomLayer; // flag that returns true if the layer is a custom layer

  public:
    MWCNNLayer();
    virtual ~MWCNNLayer();
    virtual void predict();
    virtual void cleanup();
    virtual void propagateSize() = 0;
    virtual void allocate();

    template <class T>
    void allocateOutputData(int i);

    void deallocate();

    template <class T>
    void deallocateOutputData(int i);

    void resetTensorDataPointers();
    void postSetup();

    MWCNNLayerImpl* getImpl() {
        return m_impl;
    }
    size_t getNumOutputs() {
        return m_output.size();
    }
    size_t getNumInputs() {
        return m_input.size();
    }
    MWTensorBase* getInputTensor(int index = 0);
    float* getLayerOutput(int index);
    MWTensorBase* getOutputTensor(size_t index = 0);
    void setName(const std::string&); // Set the name for this layer
    std::string getName() const {
        return m_name;
    }; // Get the name for this layer

    int getInPlaceIndex(int outIdx) {
        std::map<int, int>::iterator it = m_inPlaceIndexMap.find(outIdx);
        if (it == m_inPlaceIndexMap.end()) {
            return -1;
        }

        int inIdx = it->second;

        assert(inIdx != -1);

        return inIdx;
    }
    void setInPlaceIndex(int outIdx, int inIdx) {
        std::map<int, int>::iterator it = m_inPlaceIndexMap.find(outIdx);
        assert(it == m_inPlaceIndexMap.end());
        m_inPlaceIndexMap[outIdx] = inIdx;
    }

    static bool isDebuggingEnabled() {
        return m_enableDebugging;
    };

    bool isCustomLayer() const {
        return m_isCustomLayer;
    }

  protected:
    int getBatchSize();                      // Get the batch size
    int getHeight(int index = 0);            // Get the height of output y
    int getWidth(int index = 0);             // Get the width of output y
    int getNumInputFeatures(int index = 0);  // Get the number of channels of the input
    int getNumOutputFeatures(int index = 0); // Get the number of channels of the output

    void setInputTensor(MWTensorBase* other, int index = 0); // shallow copy tensor from other

    template <class T>
    void allocateOutputTensor(int numHeight,
                              int numWidth,
                              int numChannels,
                              int batchsize,
                              int sequencelength,
                              T* data,
                              int index = 0); // allocate output tensor

    void resizeOutputTensor(int numHeight,
                            int numWidth,
                            int numChannels,
                            int batchsize,
                            int sequencelength,
                            int index = 0); // resize output tensor

    // load non-scalar numeric parameters for custom layers
    template <typename T>
    void loadParams(const char* MW_mangled_fileName,
                    const int MW_mangled_num,
                    T* MW_mangled_buffer) {
        // MW_mangled_buffer is float buffer of size MW_mangled_num
        FILE* MW_mangled_fp = MWCNNLayer::openBinaryFile(MW_mangled_fileName);
        assert(MW_mangled_fp);
        MWCNNLayer::call_fread(MW_mangled_buffer, sizeof(T), MW_mangled_num, MW_mangled_fp,
                   MW_mangled_fileName);
        fclose(MW_mangled_fp);
    }

    void setupTensors(int numInputs, int numOutputs, ...); // setup method for input-output tensors


  public:
    static FILE* openBinaryFile(const char* filename);
    static std::runtime_error getFileOpenError(const char* filename);

    template <typename T>
    static void call_fread(T* m_buffer,
                    size_t m_size,
                    size_t m_num,
                    FILE* m_fp,
                    char const* const m_fileName) {
        if (fread(m_buffer, m_size, m_num, m_fp) != m_num) {
            throw std::runtime_error("Unexpected number of bytes read from " + std::string(m_fileName));
        }
    }

  private:
    static std::string getFilePath(std::string);

  private:
    std::map<int, int> m_inPlaceIndexMap;

#if DEBUG

    const static bool m_enableDebugging = true;

#else

    const static bool m_enableDebugging = false;

#endif
};

template <class T>
void MWCNNLayer::allocateOutputTensor(int numHeight,
                                      int numWidth,
                                      int numChannels,
                                      int batchSize,
                                      int sequenceLength,
                                      T* data,
                                      int index) {
    MWTensorBase* op = new MWTensor<T>(numHeight, numWidth, numChannels, batchSize, sequenceLength,
                                       data, this, index);
    assert(op != NULL);
    std::map<int, MWTensorBase*>::iterator it = m_output.find(index);
    assert(it == m_output.end());
    m_output[index] = op;
}

#endif
