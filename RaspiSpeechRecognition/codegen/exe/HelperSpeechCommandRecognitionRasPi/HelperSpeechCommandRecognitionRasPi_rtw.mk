###########################################################################
## Makefile generated for component 'HelperSpeechCommandRecognitionRasPi'. 
## 
## Makefile     : HelperSpeechCommandRecognitionRasPi_rtw.mk
## Generated on : Wed Jul 07 17:35:46 2021
## Final product: $(MATLAB_WORKSPACE)/home/ahhyun/MATLAB/HelperSpeechCommandRecognitionRasPi.elf
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = HelperSpeechCommandRecognitionRasPi
MAKEFILE                  = HelperSpeechCommandRecognitionRasPi_rtw.mk
MATLAB_ROOT               = $(MATLAB_WORKSPACE)/usr/local/MATLAB/R2021a
MATLAB_BIN                = $(MATLAB_WORKSPACE)/usr/local/MATLAB/R2021a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = $(MATLAB_WORKSPACE)/home/ahhyun/MATLAB/codegen/exe/HelperSpeechCommandRecognitionRasPi
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU GCC Embedded Linux
# Supported Version(s):    
# ToolchainInfo Version:   2021a
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

CCOUTPUTFLAG = --output_file=
LDOUTPUTFLAG = --output_file=

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm -lm -lstdc++

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: GNU GCC Embedded Linux Assembler
AS = as

# C Compiler: GNU GCC Embedded Linux C Compiler
CC = gcc

# Linker: GNU GCC Embedded Linux Linker
LD = gcc

# C++ Compiler: GNU GCC Embedded Linux C++ Compiler
CPP = g++

# C++ Linker: GNU GCC Embedded Linux C++ Linker
CPP_LD = g++

# Archiver: GNU GCC Embedded Linux Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: Make Tool
MAKE = make


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  =
ECHO                = echo
MV                  =
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = -r
ASFLAGS              = -c \
                       $(ASFLAGS_ADDITIONAL) \
                       $(INCLUDES)
CFLAGS               = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -O2
CPPFLAGS             = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -fpermissive  \
                       -O2
CPP_LDFLAGS          = -lrt -lpthread -ldl
CPP_SHAREDLIB_LDFLAGS  = -shared  \
                         -lrt -lpthread -ldl
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -lrt -lpthread -ldl
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared  \
                       -lrt -lpthread -ldl



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(MATLAB_WORKSPACE)/home/ahhyun/MATLAB/HelperSpeechCommandRecognitionRasPi.elf
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(MATLAB_WORKSPACE)/home/ahhyun/MATLAB -I$(ARM_COMPUTELIB) -I$(ARM_COMPUTELIB)/include -I$(START_DIR)/examples -I$(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/include -I$(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/include -I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DUSE_19_05_LIBRARY -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__
DEFINES_CUSTOM = 
DEFINES_SKIPFORSIL = -D__linux__ -DARM_PROJECT -D_USE_TARGET_UDP_ -D_RUNONTARGETHARDWARE_BUILD_ -DSTACK_SIZE=200000
DEFINES_STANDARD = -DMODEL=HelperSpeechCommandRecognitionRasPi

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/MWCNNLayer.cpp $(START_DIR)/MWElementwiseAffineLayer.cpp $(START_DIR)/MWFCLayer.cpp $(START_DIR)/MWFusedConvReLULayer.cpp $(START_DIR)/MWInputLayer.cpp $(START_DIR)/MWMaxPoolingLayer.cpp $(START_DIR)/MWOutputLayer.cpp $(START_DIR)/MWSoftmaxLayer.cpp $(START_DIR)/MWTensorBase.cpp $(START_DIR)/MWElementwiseAffineLayerImpl.cpp $(START_DIR)/MWFCLayerImpl.cpp $(START_DIR)/MWFusedConvReLULayerImpl.cpp $(START_DIR)/MWInputLayerImpl.cpp $(START_DIR)/MWMaxPoolingLayerImpl.cpp $(START_DIR)/MWOutputLayerImpl.cpp $(START_DIR)/MWSoftmaxLayerImpl.cpp $(START_DIR)/MWCNNLayerImpl.cpp $(START_DIR)/MWTargetNetworkImpl.cpp $(START_DIR)/MWACLUtils.cpp $(START_DIR)/MWCustomLayerForARMNEON.cpp $(START_DIR)/HelperSpeechCommandRecognitionRasPi_data.cpp $(START_DIR)/HelperSpeechCommandRecognitionRasPi_initialize.cpp $(START_DIR)/HelperSpeechCommandRecognitionRasPi_terminate.cpp $(START_DIR)/HelperSpeechCommandRecognitionRasPi.cpp $(START_DIR)/DeepLearningNetwork.cpp $(START_DIR)/extractSpeechFeatures.cpp $(START_DIR)/stft.cpp $(START_DIR)/computeDFT.cpp $(START_DIR)/predict.cpp $(START_DIR)/release.cpp $(START_DIR)/setup.cpp $(START_DIR)/examples/main.cpp $(START_DIR)/formatSTFTOutput.cpp $(START_DIR)/sort.cpp $(START_DIR)/sortIdx.cpp $(START_DIR)/UDPSender.cpp $(START_DIR)/UDPReceiver.cpp $(START_DIR)/AsyncBuffercgHelper.cpp $(START_DIR)/AsyncBuffer.cpp $(START_DIR)/FFTImplementationCallback.cpp $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_Network.c $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_rtw.c $(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/src/MW_raspi_init.c $(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/src/periphs/MW_Pyserver_control.c $(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/src/udp/linuxUDP.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = MWCNNLayer.cpp.o MWElementwiseAffineLayer.cpp.o MWFCLayer.cpp.o MWFusedConvReLULayer.cpp.o MWInputLayer.cpp.o MWMaxPoolingLayer.cpp.o MWOutputLayer.cpp.o MWSoftmaxLayer.cpp.o MWTensorBase.cpp.o MWElementwiseAffineLayerImpl.cpp.o MWFCLayerImpl.cpp.o MWFusedConvReLULayerImpl.cpp.o MWInputLayerImpl.cpp.o MWMaxPoolingLayerImpl.cpp.o MWOutputLayerImpl.cpp.o MWSoftmaxLayerImpl.cpp.o MWCNNLayerImpl.cpp.o MWTargetNetworkImpl.cpp.o MWACLUtils.cpp.o MWCustomLayerForARMNEON.cpp.o HelperSpeechCommandRecognitionRasPi_data.cpp.o HelperSpeechCommandRecognitionRasPi_initialize.cpp.o HelperSpeechCommandRecognitionRasPi_terminate.cpp.o HelperSpeechCommandRecognitionRasPi.cpp.o DeepLearningNetwork.cpp.o extractSpeechFeatures.cpp.o stft.cpp.o computeDFT.cpp.o predict.cpp.o release.cpp.o setup.cpp.o main.cpp.o formatSTFTOutput.cpp.o sort.cpp.o sortIdx.cpp.o UDPSender.cpp.o UDPReceiver.cpp.o AsyncBuffercgHelper.cpp.o AsyncBuffer.cpp.o FFTImplementationCallback.cpp.o DAHostLib_Network.c.o DAHostLib_rtw.c.o MW_raspi_init.c.o MW_Pyserver_control.c.o linuxUDP.c.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ =  -std=c++11  -mfpu=neon  -fopenmp
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ =  -std=c++11  -mfpu=neon  -fopenmp
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp
CPP_LDFLAGS_BLOCKMODULES = -lm -ldl

CPP_LDFLAGS += $(CPP_LDFLAGS_) $(CPP_LDFLAGS_BLOCKMODULES)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp
CPP_SHAREDLIB_LDFLAGS_BLOCKMODULES = -lm -ldl

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_) $(CPP_SHAREDLIB_LDFLAGS_BLOCKMODULES)

#-----------
# Linker
#-----------

LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp
LDFLAGS_BLOCKMODULES = -lm -ldl

LDFLAGS += $(LDFLAGS_) $(LDFLAGS_BLOCKMODULES)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp
SHAREDLIB_LDFLAGS_BLOCKMODULES = -lm -ldl

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_) $(SHAREDLIB_LDFLAGS_BLOCKMODULES)

###########################################################################
## INLINED COMMANDS
###########################################################################


DERIVED_SRCS = $(subst .o,.dep,$(OBJS))

build:

%.dep:



-include codertarget_assembly_flags.mk
-include *.dep


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS)
	echo "### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -o $(PRODUCT) $(OBJS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.c.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_WORKSPACE)/home/ahhyun/MATLAB/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_WORKSPACE)/home/ahhyun/MATLAB/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_WORKSPACE)/home/ahhyun/MATLAB/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/examples/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/examples/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/examples/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWCNNLayer.cpp.o : $(START_DIR)/MWCNNLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWElementwiseAffineLayer.cpp.o : $(START_DIR)/MWElementwiseAffineLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWFCLayer.cpp.o : $(START_DIR)/MWFCLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWFusedConvReLULayer.cpp.o : $(START_DIR)/MWFusedConvReLULayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWInputLayer.cpp.o : $(START_DIR)/MWInputLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWMaxPoolingLayer.cpp.o : $(START_DIR)/MWMaxPoolingLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWOutputLayer.cpp.o : $(START_DIR)/MWOutputLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWSoftmaxLayer.cpp.o : $(START_DIR)/MWSoftmaxLayer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWTensorBase.cpp.o : $(START_DIR)/MWTensorBase.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWElementwiseAffineLayerImpl.cpp.o : $(START_DIR)/MWElementwiseAffineLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWFCLayerImpl.cpp.o : $(START_DIR)/MWFCLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWFusedConvReLULayerImpl.cpp.o : $(START_DIR)/MWFusedConvReLULayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWInputLayerImpl.cpp.o : $(START_DIR)/MWInputLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWMaxPoolingLayerImpl.cpp.o : $(START_DIR)/MWMaxPoolingLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWOutputLayerImpl.cpp.o : $(START_DIR)/MWOutputLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWSoftmaxLayerImpl.cpp.o : $(START_DIR)/MWSoftmaxLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWCNNLayerImpl.cpp.o : $(START_DIR)/MWCNNLayerImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWTargetNetworkImpl.cpp.o : $(START_DIR)/MWTargetNetworkImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWACLUtils.cpp.o : $(START_DIR)/MWACLUtils.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MWCustomLayerForARMNEON.cpp.o : $(START_DIR)/MWCustomLayerForARMNEON.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


HelperSpeechCommandRecognitionRasPi_data.cpp.o : $(START_DIR)/HelperSpeechCommandRecognitionRasPi_data.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


HelperSpeechCommandRecognitionRasPi_initialize.cpp.o : $(START_DIR)/HelperSpeechCommandRecognitionRasPi_initialize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


HelperSpeechCommandRecognitionRasPi_terminate.cpp.o : $(START_DIR)/HelperSpeechCommandRecognitionRasPi_terminate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


HelperSpeechCommandRecognitionRasPi.cpp.o : $(START_DIR)/HelperSpeechCommandRecognitionRasPi.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


DeepLearningNetwork.cpp.o : $(START_DIR)/DeepLearningNetwork.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


extractSpeechFeatures.cpp.o : $(START_DIR)/extractSpeechFeatures.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


stft.cpp.o : $(START_DIR)/stft.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


computeDFT.cpp.o : $(START_DIR)/computeDFT.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


predict.cpp.o : $(START_DIR)/predict.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


release.cpp.o : $(START_DIR)/release.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


setup.cpp.o : $(START_DIR)/setup.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


main.cpp.o : $(START_DIR)/examples/main.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


formatSTFTOutput.cpp.o : $(START_DIR)/formatSTFTOutput.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sort.cpp.o : $(START_DIR)/sort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sortIdx.cpp.o : $(START_DIR)/sortIdx.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


UDPSender.cpp.o : $(START_DIR)/UDPSender.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


UDPReceiver.cpp.o : $(START_DIR)/UDPReceiver.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


AsyncBuffercgHelper.cpp.o : $(START_DIR)/AsyncBuffercgHelper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


AsyncBuffer.cpp.o : $(START_DIR)/AsyncBuffer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


FFTImplementationCallback.cpp.o : $(START_DIR)/FFTImplementationCallback.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


DAHostLib_Network.c.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_Network.c
	$(CC) $(CFLAGS) -o "$@" "$<"


DAHostLib_rtw.c.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_rtw.c
	$(CC) $(CFLAGS) -o "$@" "$<"


MW_raspi_init.c.o : $(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/src/MW_raspi_init.c
	$(CC) $(CFLAGS) -o "$@" "$<"


MW_Pyserver_control.c.o : $(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/src/periphs/MW_Pyserver_control.c
	$(CC) $(CFLAGS) -o "$@" "$<"


linuxUDP.c.o : $(MATLAB_WORKSPACE)/home/ahhyun/Documents/MATLAB/SupportPackages/R2021a/toolbox/realtime/targets/raspi/src/udp/linuxUDP.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	echo "### PRODUCT = $(PRODUCT)"
	echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	echo "### BUILD_TYPE = $(BUILD_TYPE)"
	echo "### INCLUDES = $(INCLUDES)"
	echo "### DEFINES = $(DEFINES)"
	echo "### ALL_SRCS = $(ALL_SRCS)"
	echo "### ALL_OBJS = $(ALL_OBJS)"
	echo "### LIBS = $(LIBS)"
	echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	echo "### ASFLAGS = $(ASFLAGS)"
	echo "### CFLAGS = $(CFLAGS)"
	echo "### LDFLAGS = $(LDFLAGS)"
	echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	echo "### CPPFLAGS = $(CPPFLAGS)"
	echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	echo "### ARFLAGS = $(ARFLAGS)"
	echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(RM) *.c.dep
	$(RM) *.cpp.dep
	$(ECHO) "### Deleted all derived files."


