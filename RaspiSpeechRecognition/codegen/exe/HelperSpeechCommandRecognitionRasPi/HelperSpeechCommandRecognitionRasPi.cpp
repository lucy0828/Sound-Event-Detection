//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: HelperSpeechCommandRecognitionRasPi.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "HelperSpeechCommandRecognitionRasPi.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "DeepLearningNetwork.h"
#include "HelperSpeechCommandRecognitionRasPi_data.h"
#include "HelperSpeechCommandRecognitionRasPi_initialize.h"
#include "HelperSpeechCommandRecognitionRasPi_internal_types.h"
#include "UDPReceiver.h"
#include "UDPSender.h"
#include "extractSpeechFeatures.h"
#include "predict.h"
#include "sort.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// C++ EXECUTABLE generated using MATLAB Coder for this function, runs on
//  Raspberry Pi board. It receives speech data from the matlab script
//  running on host PC/LAPTOP through UDP and process it to get the
//  predicted scores and audio features. This function sends the predicted
//  scores and auditory feature matrix to the UDP port of the host PC/LAPTOP.
//  Matlab script running on host PC/LAPTOP receives this data and shows
//  the results on Time scope and Matrix Viewer
//
// Arguments    : void
// Return Type  : void
//
void HelperSpeechCommandRecognitionRasPi()
{
  static coder::dsp::AsyncBuffer audioBuffer;
  static float b_y_data[16000];
  static int y_data[16001];
  coder::dspcodegen::UDPReceiver UDPReceive;
  coder::dspcodegen::UDPSender UDPSend;
  commandNet0_0 trainedNet;
  coder::array<int, 2U> bc;
  coder::array<int, 2U> y;
  float U0_data[4901];
  float c_features_data[4901];
  float b_features_data[4900];
  float features_data[4900];
  float b_UDPReceive[800];
  float probBuffer[120];
  float probs[12];
  float v[10];
  int features_size[2];
  int i;
  int n;
  int samplesRead;
  short tmp_data[16800];
  signed char YBuffer[10];
  char *sErr;
  if (!isInitialized_HelperSpeechCommandRecognitionRasPi) {
    HelperSpeechCommandRecognitionRasPi_initialize();
  }
  UDPSend.matlabCodegenIsDeleted = true;
  UDPReceive.matlabCodegenIsDeleted = true;
  //  Copyright 2020 The MathWorks, Inc.
  //  Load Network
  coder::DeepLearningNetwork_setup(&trainedNet);
  //  Setting Real-Time Parameters
  //  Configure UDP system objects
  UDPSend.isInitialized = 0;
  // System object Constructor function: dsp.UDPSender
  UDPSend.cSFunObject.P0_Port = 9441;
  UDPSend.matlabCodegenIsDeleted = false;
  // Sends to matlab script to display
  //  This is in sync with the UDPReceiver at host end
  UDPReceive.isInitialized = 0;
  // System object Constructor function: dsp.UDPReceiver
  UDPReceive.cSFunObject.P0_Port = 9442;
  UDPReceive.matlabCodegenIsDeleted = false;
  //   %Receives from EXE
  //  Defining and Initializing History Buffers
  std::memset(&probBuffer[0], 0, 120U * sizeof(float));
  for (i = 0; i < 10; i++) {
    YBuffer[i] = 12;
  }
  // "background" --> 12
  //  Create audio buffer
  audioBuffer.pBuffer.NumChannels = -1;
  audioBuffer.pBuffer.isInitialized = 0;
  audioBuffer.pBuffer.matlabCodegenIsDeleted = false;
  audioBuffer.matlabCodegenIsDeleted = false;
  //  Speech Command Recognition
  while (1) {
    //  Capture and Buffer Audio
    if (UDPReceive.isInitialized != 1) {
      UDPReceive.isSetupComplete = false;
      UDPReceive.isInitialized = 1;
      // System object Start function: dsp.UDPReceiver
      sErr = GetErrorBuffer(&UDPReceive.cSFunObject.W0_NetworkLib[0U]);
      CreateUDPInterface(&UDPReceive.cSFunObject.W0_NetworkLib[0U]);
      if (*sErr == 0) {
        LibCreate_Network(&UDPReceive.cSFunObject.W0_NetworkLib[0U], 0,
                          "0.0.0.0", UDPReceive.cSFunObject.P0_Port, "0.0.0.0",
                          -1, 9600, 4, 0);
      }
      if (*sErr == 0) {
        LibStart(&UDPReceive.cSFunObject.W0_NetworkLib[0U]);
      }
      if (*sErr != 0) {
        DestroyUDPInterface(&UDPReceive.cSFunObject.W0_NetworkLib[0U]);
        if (*sErr != 0) {
          PrintError(sErr);
        }
      }
      UDPReceive.isSetupComplete = true;
    }
    // System object Outputs function: dsp.UDPReceiver
    sErr = GetErrorBuffer(&UDPReceive.cSFunObject.W0_NetworkLib[0U]);
    UDPReceive.cSFunObject.O0_Y0.size[0] = 800;
    UDPReceive.cSFunObject.O0_Y0.size[1] = 1;
    samplesRead = 800;
    LibOutputs_Network(&UDPReceive.cSFunObject.W0_NetworkLib[0U],
                       &UDPReceive.cSFunObject.O0_Y0.data[0U], &samplesRead);
    if (*sErr != 0) {
      PrintError(sErr);
    }
    UDPReceive.cSFunObject.O0_Y0.size[0] = samplesRead;
    UDPReceive.cSFunObject.O0_Y0.size[1] = 1;
    if ((UDPReceive.cSFunObject.O0_Y0.size[0] != 0) &&
        (UDPReceive.cSFunObject.O0_Y0.size[1] != 0)) {
      float f;
      float mtmp;
      float speechCommandIdx;
      int b_qY;
      int c;
      int k;
      int loop_ub;
      int qY;
      int rPtr;
      int yk;
      bool exitg1;
      //  Buffer audio in 1s buffer y
      if (audioBuffer.pBuffer.isInitialized != 1) {
        audioBuffer.pBuffer.isInitialized = 1;
        audioBuffer.pBuffer.NumChannels = 1;
        audioBuffer.pBuffer.AsyncBuffercgHelper_isInitialized = true;
        audioBuffer.pBuffer.isSetupComplete = true;
        audioBuffer.pBuffer.ReadPointer = 1;
        audioBuffer.pBuffer.WritePointer = 2;
        audioBuffer.pBuffer.CumulativeOverrun = 0;
        audioBuffer.pBuffer.CumulativeUnderrun = 0;
        std::memset(&audioBuffer.pBuffer.Cache[0], 0, 16001U * sizeof(float));
      }
      rPtr = audioBuffer.pBuffer.ReadPointer;
      qY = 0;
      if (audioBuffer.pBuffer.WritePointer > 2147482847) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = audioBuffer.pBuffer.WritePointer + 800;
      }
      c = b_qY - 1;
      if (b_qY - 1 > 16001) {
        c = b_qY - 16002;
        n = 16002 - audioBuffer.pBuffer.WritePointer;
        y_data[0] = audioBuffer.pBuffer.WritePointer;
        yk = audioBuffer.pBuffer.WritePointer;
        for (k = 2; k <= n; k++) {
          yk++;
          y_data[k - 1] = yk;
        }
        y.set_size(1, b_qY - 16002);
        y[0] = 1;
        yk = 1;
        for (k = 2; k <= c; k++) {
          yk++;
          y[k - 1] = yk;
        }
        bc.set_size(1, (y.size(1) - audioBuffer.pBuffer.WritePointer) + 16002);
        for (i = 0; i < n; i++) {
          bc[i] = y_data[i];
        }
        loop_ub = y.size(1);
        for (i = 0; i < loop_ub; i++) {
          bc[i + n] = y[i];
        }
        if (audioBuffer.pBuffer.WritePointer <=
            audioBuffer.pBuffer.ReadPointer) {
          if (audioBuffer.pBuffer.ReadPointer < -2147467646) {
            qY = MAX_int32_T;
          } else {
            qY = 16001 - audioBuffer.pBuffer.ReadPointer;
          }
          if (qY > 2147483646) {
            qY = MAX_int32_T;
          } else {
            qY++;
          }
          if ((qY < 0) && (b_qY - 16002 < MIN_int32_T - qY)) {
            qY = MIN_int32_T;
          } else if ((qY > 0) && (b_qY - 16002 > MAX_int32_T - qY)) {
            qY = MAX_int32_T;
          } else {
            qY = (qY + b_qY) - 16002;
          }
        } else if (audioBuffer.pBuffer.ReadPointer <= b_qY - 16002) {
          if (audioBuffer.pBuffer.ReadPointer < b_qY + 2147467647) {
            b_qY = MAX_int32_T;
          } else {
            b_qY = (b_qY - audioBuffer.pBuffer.ReadPointer) - 16002;
          }
          if (b_qY > 2147483646) {
            qY = MAX_int32_T;
          } else {
            qY = b_qY + 1;
          }
        }
      } else {
        if (b_qY - 1 < audioBuffer.pBuffer.WritePointer) {
          n = 0;
        } else {
          n = b_qY - audioBuffer.pBuffer.WritePointer;
        }
        if (n > 0) {
          y_data[0] = audioBuffer.pBuffer.WritePointer;
          yk = audioBuffer.pBuffer.WritePointer;
          for (k = 2; k <= n; k++) {
            yk++;
            y_data[k - 1] = yk;
          }
        }
        bc.set_size(1, n);
        for (i = 0; i < n; i++) {
          bc[i] = y_data[i];
        }
        if ((audioBuffer.pBuffer.WritePointer <=
             audioBuffer.pBuffer.ReadPointer) &&
            (audioBuffer.pBuffer.ReadPointer <= b_qY - 1)) {
          if ((b_qY - 1 >= 0) &&
              (audioBuffer.pBuffer.ReadPointer < b_qY + MIN_int32_T)) {
            b_qY = MAX_int32_T;
          } else if ((b_qY - 1 < 0) &&
                     (audioBuffer.pBuffer.ReadPointer > b_qY + MAX_int32_T)) {
            b_qY = MIN_int32_T;
          } else {
            b_qY = (b_qY - audioBuffer.pBuffer.ReadPointer) - 1;
          }
          if (b_qY > 2147483646) {
            qY = MAX_int32_T;
          } else {
            qY = b_qY + 1;
          }
        }
      }
      n = bc.size(1);
      loop_ub = bc.size(1);
      for (i = 0; i < loop_ub; i++) {
        tmp_data[i] = static_cast<short>(static_cast<short>(bc[i]) - 1);
      }
      std::copy(&UDPReceive.cSFunObject.O0_Y0.data[0],
                &UDPReceive.cSFunObject.O0_Y0.data[800], &b_UDPReceive[0]);
      for (i = 0; i < n; i++) {
        audioBuffer.pBuffer.Cache[tmp_data[i]] = b_UDPReceive[i];
      }
      if (c + 1 > 16001) {
        n = 1;
      } else {
        n = c + 1;
      }
      if (qY != 0) {
        rPtr = n;
      }
      if ((audioBuffer.pBuffer.CumulativeOverrun < 0) &&
          (qY < MIN_int32_T - audioBuffer.pBuffer.CumulativeOverrun)) {
        b_qY = MIN_int32_T;
      } else if ((audioBuffer.pBuffer.CumulativeOverrun > 0) &&
                 (qY > MAX_int32_T - audioBuffer.pBuffer.CumulativeOverrun)) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = audioBuffer.pBuffer.CumulativeOverrun + qY;
      }
      audioBuffer.pBuffer.CumulativeOverrun = b_qY;
      audioBuffer.pBuffer.WritePointer = n;
      audioBuffer.pBuffer.ReadPointer = rPtr;
      audioBuffer.read(b_y_data, &n);
      //  Extract Features
      extractSpeechFeatures(b_y_data, features_data, features_size);
      //  Take the log.
      for (k = 0; k < 4900; k++) {
        features_data[k] = std::log10(features_data[k] + 1.0E-6F);
      }
      //  Predict Speech Commmand
      //  features must have known size to generate code for predict()
      coder::DeepLearningNetwork_predict(
          &trainedNet, *(float(*)[4900]) & features_data[0], probs);
      if (!std::isnan(probs[0])) {
        yk = 1;
      } else {
        yk = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 13)) {
          if (!std::isnan(probs[k - 1])) {
            yk = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }
      if (yk == 0) {
        yk = 1;
      } else {
        mtmp = probs[yk - 1];
        i = yk + 1;
        for (k = i; k < 13; k++) {
          f = probs[k - 1];
          if (mtmp < f) {
            mtmp = f;
            yk = k;
          }
        }
      }
      //  Statistical Post Processing
      //  Keeping history
      for (i = 0; i < 9; i++) {
        YBuffer[i] = YBuffer[i + 1];
        for (n = 0; n < 12; n++) {
          probBuffer[n + 12 * i] = probBuffer[n + 12 * (i + 1)];
        }
      }
      YBuffer[9] = static_cast<signed char>(yk);
      for (i = 0; i < 12; i++) {
        probBuffer[i + 108] = probs[i];
      }
      for (i = 0; i < 10; i++) {
        v[i] = YBuffer[i];
      }
      coder::internal::sort(v);
      speechCommandIdx = v[0];
      loop_ub = 1;
      mtmp = v[0];
      n = 1;
      for (k = 0; k < 9; k++) {
        f = v[k + 1];
        if (f == mtmp) {
          n++;
        } else {
          if (n > loop_ub) {
            speechCommandIdx = mtmp;
            loop_ub = n;
          }
          mtmp = f;
          n = 1;
        }
      }
      if (n > loop_ub) {
        speechCommandIdx = mtmp;
        loop_ub = n;
      }
      if (!std::isnan(probBuffer[static_cast<int>(speechCommandIdx) - 1])) {
        yk = 1;
      } else {
        yk = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 11)) {
          if (!std::isnan(probBuffer[(static_cast<int>(speechCommandIdx) +
                                      12 * (k - 1)) -
                                     1])) {
            yk = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }
      if (yk == 0) {
        mtmp = probBuffer[static_cast<int>(speechCommandIdx) - 1];
      } else {
        mtmp = probBuffer[(static_cast<int>(speechCommandIdx) + 12 * (yk - 1)) -
                          1];
        i = yk + 1;
        for (k = i; k < 11; k++) {
          f = probBuffer[(static_cast<int>(speechCommandIdx) + 12 * (k - 1)) -
                         1];
          if (mtmp < f) {
            mtmp = f;
          }
        }
      }
      if ((speechCommandIdx == 12.0F) || (loop_ub < 4.0F) || (mtmp < 0.7)) {
        speechCommandIdx = 12.0F;
      }
      if (UDPSend.isInitialized != 1) {
        UDPSend.isSetupComplete = false;
        UDPSend.isInitialized = 1;
        // System object Start function: dsp.UDPSender
        sErr = GetErrorBuffer(&UDPSend.cSFunObject.W0_NetworkLib[0U]);
        CreateUDPInterface(&UDPSend.cSFunObject.W0_NetworkLib[0U]);
        if (*sErr == 0) {
          LibCreate_Network(&UDPSend.cSFunObject.W0_NetworkLib[0U], 1,
                            "0.0.0.0", -1, "192.168.0.38",
                            UDPSend.cSFunObject.P0_Port, 8192, 4, 0);
        }
        if (*sErr == 0) {
          LibStart(&UDPSend.cSFunObject.W0_NetworkLib[0U]);
        }
        if (*sErr != 0) {
          DestroyUDPInterface(&UDPSend.cSFunObject.W0_NetworkLib[0U]);
          if (*sErr != 0) {
            PrintError(sErr);
          }
        }
        UDPSend.isSetupComplete = true;
      }
      for (i = 0; i < 98; i++) {
        for (n = 0; n < 50; n++) {
          b_features_data[n + 50 * i] = features_data[i + 98 * n];
        }
      }
      std::copy(&b_features_data[0], &b_features_data[4900],
                &c_features_data[0]);
      c_features_data[4900] = speechCommandIdx;
      std::copy(&c_features_data[0], &c_features_data[4901], &U0_data[0]);
      // System object Update function: dsp.UDPSender
      sErr = GetErrorBuffer(&UDPSend.cSFunObject.W0_NetworkLib[0U]);
      LibUpdate_Network(&UDPSend.cSFunObject.W0_NetworkLib[0U], &U0_data[0U],
                        4901);
      if (*sErr != 0) {
        PrintError(sErr);
      }
    }
  }
}

//
// File trailer for HelperSpeechCommandRecognitionRasPi.cpp
//
// [EOF]
//
