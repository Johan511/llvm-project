if (MLIR_ENABLE_CUDA_CONVERSIONS)
  set(NVPTX_LIBS
    NVPTXCodeGen
    NVPTXDesc
    NVPTXInfo
  )
endif()

if (MLIR_ENABLE_ROCM_CONVERSIONS)
  set(AMDGPU_LIBS
    IRReader
    IPO
    linker
    MCParser
    AMDGPUAsmParser
    AMDGPUCodeGen
    AMDGPUDesc
    AMDGPUInfo
    target
  )
endif()

add_mlir_dialect_library(MLIRGPUDialect
  IR/GPUDialect.cpp
  IR/InferIntRangeInterfaceImpls.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/GPU

  DEPENDS
  MLIRGPUOpsIncGen
  MLIRGPUOpsAttributesIncGen
  MLIRGPUOpsEnumsGen
  MLIRGPUOpInterfacesIncGen

  LINK_LIBS PUBLIC
  MLIRArithDialect
  MLIRDLTIDialect
  MLIRInferIntRangeInterface
  MLIRIR
  MLIRMemRefDialect
  MLIRSideEffectInterfaces
  MLIRSupport
  )

add_mlir_dialect_library(MLIRGPUTransforms
  Transforms/AllReduceLowering.cpp
  Transforms/AsyncRegionRewriter.cpp
  Transforms/GlobalIdRewriter.cpp
  Transforms/KernelOutlining.cpp
  Transforms/MemoryPromotion.cpp
  Transforms/ParallelLoopMapper.cpp
  Transforms/ShuffleRewriter.cpp
  Transforms/SerializeToBlob.cpp
  Transforms/SerializeToCubin.cpp
  Transforms/SerializeToHsaco.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/GPU

  LINK_COMPONENTS
  Core
  MC
  ${NVPTX_LIBS}
  ${AMDGPU_LIBS}

  DEPENDS
  MLIRGPUPassIncGen
  MLIRParallelLoopMapperEnumsGen

  LINK_LIBS PUBLIC
  MLIRAffineUtils
  MLIRArithDialect
  MLIRAsyncDialect
  MLIRBuiltinToLLVMIRTranslation
  MLIRDataLayoutInterfaces
  MLIRExecutionEngineUtils
  MLIRGPUDialect
  MLIRIR
  MLIRIndexDialect
  MLIRLLVMDialect
  MLIRGPUToLLVMIRTranslation
  MLIRLLVMToLLVMIRTranslation
  MLIRMemRefDialect
  MLIRPass
  MLIRSCFDialect
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRTransformUtils
  )

add_subdirectory(TransformOps)

if(MLIR_ENABLE_CUDA_RUNNER)
  if(NOT MLIR_ENABLE_CUDA_CONVERSIONS)
    message(SEND_ERROR
      "Building mlir with cuda support requires the NVPTX backend")
  endif()

  # Configure CUDA language support. Using check_language first allows us to
  # give a custom error message.
  include(CheckLanguage)
  check_language(CUDA)
  if (CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
  else()
    message(SEND_ERROR
      "Building mlir with cuda support requires a working CUDA install")
  endif()

  # Enable gpu-to-cubin pass.
  target_compile_definitions(obj.MLIRGPUTransforms
    PRIVATE
    MLIR_GPU_TO_CUBIN_PASS_ENABLE=1
  )

  # Add CUDA headers includes and the libcuda.so library.
  target_include_directories(obj.MLIRGPUTransforms
    PRIVATE
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
  )

  find_library(CUDA_DRIVER_LIBRARY cuda)

  target_link_libraries(MLIRGPUTransforms
    PRIVATE
    MLIRNVVMToLLVMIRTranslation
    ${CUDA_DRIVER_LIBRARY}
  )

endif()

if(MLIR_ENABLE_ROCM_CONVERSIONS)
  if (NOT ("AMDGPU" IN_LIST LLVM_TARGETS_TO_BUILD))
    message(SEND_ERROR
      "Building mlir with ROCm support requires the AMDGPU backend")
  endif()

  set(DEFAULT_ROCM_PATH "/opt/rocm" CACHE PATH "Fallback path to search for ROCm installs")
  target_compile_definitions(obj.MLIRGPUTransforms
    PRIVATE
    __DEFAULT_ROCM_PATH__="${DEFAULT_ROCM_PATH}"
    MLIR_GPU_TO_HSACO_PASS_ENABLE=1
  )

  target_link_libraries(MLIRGPUTransforms
    PRIVATE
    MLIRROCDLToLLVMIRTranslation
  )
endif()
