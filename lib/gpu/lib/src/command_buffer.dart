// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// ignore_for_file: public_member_api_docs

part of flutter_gpu;

typedef CompletionCallback<T> = void Function(bool success);

base class CommandBuffer extends NativeFieldWrapperClass1 {
  /// Creates a new CommandBuffer.
  CommandBuffer._(GpuContext gpuContext) {
    _initialize(gpuContext);
  }

  RenderPass createRenderPass(
      {required ColorAttachment colorAttachment,
      StencilAttachment? stencilAttachment = null}) {
    return RenderPass._(this, colorAttachment, stencilAttachment);
  }

  void submit({CompletionCallback? completionCallback}) {
    String? error = _submit(completionCallback);
    if (error != null) {
      throw Exception(error);
    }
  }

  /// Wrap with native counterpart.
  @Native<Bool Function(Handle, Pointer<Void>)>(
      symbol: 'InternalFlutterGpu_CommandBuffer_Initialize')
  external bool _initialize(GpuContext gpuContext);

  @Native<Handle Function(Pointer<Void>, Handle)>(
      symbol: 'InternalFlutterGpu_CommandBuffer_Submit')
  external String? _submit(CompletionCallback? completionCallback);
}
