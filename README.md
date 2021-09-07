# Sound-Event-Detection
This project is based on [MATLAB Speech Command Recognition](https://kr.mathworks.com/help/audio/ug/speech-command-recognition-code-generation-with-raspi.html?searchHighlight=deep%20learning%20coder%20raspberry%20pi&s_tid=srchtitle) for real-Time sound event detection on Linux based system using pretrained CNN model.


## Prerequisites
1. Install [MATLAB](https://kr.mathworks.com/products/new_products/latest_features.html?s_tid=hp_release_2021a) on Linux based operating system. 
2. Install MATLAB Signal Processing Toolbox, DSP System Toolbox, Deep Learning Tollbox and Audio Toolbox.
3. If you are using Thingy:52 as microphone, go to [this repository](https://github.com/lucy0828/Thingy52-RaspberryPi-Mic) to connect and collect data from Thingy:52 on Linux OS.

## Dataset
Models in the `model` folder are trained with [Activity of Daily Living Sound Dataset (ADLSD)](https://sites.google.com/view/knu-rtlab/research/adl) on MATLAB.
ADLSD is a collection of 16 classes of real-life acoustic data in domestic environment for ADL testing.
Random oversampling is used to balance out the distribution of data.

<p align="center">
  <img src="https://user-images.githubusercontent.com/46836844/132270241-be3f7a1e-014e-4618-a854-1f8fa1454549.jpg" width="40%">
</p>

## Model
The CNN architecture is composed of five 2D convolutional layers with four max pooling layers and one fully connected layer.\
Input of the model is 98 by 128 log Mel spectrogram. ReLU is used for every convoultional layer and at the end of the classifier, a fully connected layer is used with Softmax for multi-class classification. 
We used 80% of data to train the network and 20% for validation.

<p align="center">
  <img src="https://user-images.githubusercontent.com/46836844/132269848-479d0a6b-19d6-4020-b1bf-b180f2b57c93.png" width="100%">
</p>

In `model` folder: 
- `trainedNet.mat` is a model trained without oversampling
- `trainedNetBalanced.mat` is a model trained with oversampling

Confusion matrix for validation data is shown in the following image:
<p align="center">
  <img src="https://user-images.githubusercontent.com/46836844/132270643-b14b0dfa-5a78-4dcf-9718-3cec4774e564.jpg" width="60%">
</p>

## Real-Time Classificaiton Algorithm
FIFO buffer for audio reading is created with a sample size of 16000 or 1 second. A while loop reads new audio samples and extract log Mel spectrogram features for input of CNN classifier.
Probabilities of each class are output of CNN model and the classification algorithm determines the final class per classification rate. The final class output is saved as `history_activity.mat` in `history` folder.

- `SED_File.m`:
MATLAB code for sound event detection of recorded WAV files. You can test out the sound event detection with WAV files inside `audio` folder. 
- `SED_RealTime.m`:
MATLAB code for sound event detection of streaming WAV files. First, start a microphone to record and run this code for streaming sound event detection. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/46836844/132271587-812ed0eb-e1e7-495a-abbf-44fd2bad36a2.jpg" width="60%">
</p>
