//===- InitAllDialects.h - MLIR Dialects Registration -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines a helper to trigger the registration of all dialects and
// passes to the system.
//
//===----------------------------------------------------------------------===//

#ifndef MLIR_INITALLDIALECTS_H_
#define MLIR_INITALLDIALECTS_H_

#include "mlir/Dialect/AMDGPU/IR/AMDGPUDialect.h"
#include "mlir/Dialect/AMX/AMXDialect.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/IR/ValueBoundsOpInterfaceImpl.h"
#include "mlir/Dialect/Affine/TransformOps/AffineTransformOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Arith/IR/ValueBoundsOpInterfaceImpl.h"
#include "mlir/Dialect/Arith/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/ArmNeon/ArmNeonDialect.h"
#include "mlir/Dialect/ArmSVE/ArmSVEDialect.h"
#include "mlir/Dialect/Async/IR/Async.h"
#include "mlir/Dialect/Bufferization/IR/Bufferization.h"
#include "mlir/Dialect/Bufferization/TransformOps/BufferizationTransformOps.h"
#include "mlir/Dialect/Bufferization/Transforms/FuncBufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Complex/IR/Complex.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "mlir/Dialect/DLTI/DLTI.h"
#include "mlir/Dialect/EmitC/IR/EmitC.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/Dialect/GPU/TransformOps/GPUTransformOps.h"
#include "mlir/Dialect/IRDL/IR/IRDL.h"
#include "mlir/Dialect/Index/IR/IndexDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/NVVMDialect.h"
#include "mlir/Dialect/LLVMIR/ROCDLDialect.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/IR/ValueBoundsOpInterfaceImpl.h"
#include "mlir/Dialect/Linalg/TransformOps/DialectExtension.h"
#include "mlir/Dialect/Linalg/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Linalg/Transforms/TilingInterfaceImpl.h"
#include "mlir/Dialect/MLProgram/IR/MLProgram.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/MemRef/IR/MemRefMemorySlot.h"
#include "mlir/Dialect/MemRef/IR/ValueBoundsOpInterfaceImpl.h"
#include "mlir/Dialect/MemRef/TransformOps/MemRefTransformOps.h"
#include "mlir/Dialect/MemRef/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/MemRef/Transforms/RuntimeOpVerification.h"
#include "mlir/Dialect/NVGPU/IR/NVGPUDialect.h"
#include "mlir/Dialect/OpenACC/OpenACC.h"
#include "mlir/Dialect/OpenMP/OpenMPDialect.h"
#include "mlir/Dialect/PDL/IR/PDL.h"
#include "mlir/Dialect/PDLInterp/IR/PDLInterp.h"
#include "mlir/Dialect/Quant/QuantOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/SCF/IR/ValueBoundsOpInterfaceImpl.h"
#include "mlir/Dialect/SCF/TransformOps/SCFTransformOps.h"
#include "mlir/Dialect/SCF/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/SPIRV/IR/SPIRVDialect.h"
#include "mlir/Dialect/Shape/IR/Shape.h"
#include "mlir/Dialect/Shape/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/SparseTensor/IR/SparseTensor.h"
#include "mlir/Dialect/SparseTensor/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Tensor/IR/TensorInferTypeOpInterfaceImpl.h"
#include "mlir/Dialect/Tensor/IR/TensorTilingInterfaceImpl.h"
#include "mlir/Dialect/Tensor/IR/ValueBoundsOpInterfaceImpl.h"
#include "mlir/Dialect/Tensor/TransformOps/TensorTransformOps.h"
#include "mlir/Dialect/Tensor/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Tosa/IR/TosaOps.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/Dialect/Transform/PDLExtension/PDLExtension.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Vector/TransformOps/VectorTransformOps.h"
#include "mlir/Dialect/Vector/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/X86Vector/X86VectorDialect.h"
#include "mlir/IR/Dialect.h"

namespace mlir {

/// Add all the MLIR dialects to the provided registry.
inline void registerAllDialects(DialectRegistry &registry) {
  // clang-format off
  registry.insert<acc::OpenACCDialect,
                  affine::AffineDialect,
                  arith::ArithDialect,
                  amdgpu::AMDGPUDialect,
                  amx::AMXDialect,
                  arm_neon::ArmNeonDialect,
                  async::AsyncDialect,
                  bufferization::BufferizationDialect,
                  cf::ControlFlowDialect,
                  complex::ComplexDialect,
                  DLTIDialect,
                  emitc::EmitCDialect,
                  func::FuncDialect,
                  gpu::GPUDialect,
                  index::IndexDialect,
                  irdl::IRDLDialect,
                  LLVM::LLVMDialect,
                  linalg::LinalgDialect,
                  math::MathDialect,
                  memref::MemRefDialect,
                  ml_program::MLProgramDialect,
                  nvgpu::NVGPUDialect,
                  scf::SCFDialect,
                  omp::OpenMPDialect,
                  pdl::PDLDialect,
                  pdl_interp::PDLInterpDialect,
                  quant::QuantizationDialect,
                  spirv::SPIRVDialect,
                  arm_sve::ArmSVEDialect,
                  vector::VectorDialect,
                  NVVM::NVVMDialect,
                  ROCDL::ROCDLDialect,
                  shape::ShapeDialect,
                  sparse_tensor::SparseTensorDialect,
                  tensor::TensorDialect,
                  transform::TransformDialect,
                  tosa::TosaDialect,
                  x86vector::X86VectorDialect>();
  // clang-format on

  // Register all dialect extensions.
  affine::registerTransformDialectExtension(registry);
  bufferization::registerTransformDialectExtension(registry);
  gpu::registerTransformDialectExtension(registry);
  linalg::registerTransformDialectExtension(registry);
  memref::registerTransformDialectExtension(registry);
  scf::registerTransformDialectExtension(registry);
  tensor::registerTransformDialectExtension(registry);
  transform::registerPDLExtension(registry);
  vector::registerTransformDialectExtension(registry);

  // Register all external models.
  affine::registerValueBoundsOpInterfaceExternalModels(registry);
  arith::registerBufferizableOpInterfaceExternalModels(registry);
  arith::registerValueBoundsOpInterfaceExternalModels(registry);
  bufferization::func_ext::registerBufferizableOpInterfaceExternalModels(
      registry);
  linalg::registerBufferizableOpInterfaceExternalModels(registry);
  linalg::registerTilingInterfaceExternalModels(registry);
  linalg::registerValueBoundsOpInterfaceExternalModels(registry);
  memref::registerBufferizableOpInterfaceExternalModels(registry);
  memref::registerRuntimeVerifiableOpInterfaceExternalModels(registry);
  memref::registerValueBoundsOpInterfaceExternalModels(registry);
  memref::registerMemorySlotExternalModels(registry);
  scf::registerBufferizableOpInterfaceExternalModels(registry);
  scf::registerValueBoundsOpInterfaceExternalModels(registry);
  shape::registerBufferizableOpInterfaceExternalModels(registry);
  sparse_tensor::registerBufferizableOpInterfaceExternalModels(registry);
  tensor::registerBufferizableOpInterfaceExternalModels(registry);
  tensor::registerInferTypeOpInterfaceExternalModels(registry);
  tensor::registerTilingInterfaceExternalModels(registry);
  tensor::registerValueBoundsOpInterfaceExternalModels(registry);
  vector::registerBufferizableOpInterfaceExternalModels(registry);
}

/// Append all the MLIR dialects to the registry contained in the given context.
inline void registerAllDialects(MLIRContext &context) {
  DialectRegistry registry;
  registerAllDialects(registry);
  context.appendDialectRegistry(registry);
}

} // namespace mlir

#endif // MLIR_INITALLDIALECTS_H_
