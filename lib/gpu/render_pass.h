// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <memory>
#include "flutter/lib/gpu/command_buffer.h"
#include "flutter/lib/gpu/export.h"
#include "flutter/lib/ui/dart_wrapper.h"
#include "fml/memory/ref_ptr.h"
#include "impeller/core/vertex_buffer.h"
#include "impeller/renderer/command.h"
#include "impeller/renderer/render_pass.h"
#include "impeller/renderer/render_target.h"
#include "lib/gpu/device_buffer.h"
#include "lib/gpu/host_buffer.h"
#include "lib/gpu/render_pipeline.h"
#include "lib/gpu/texture.h"

namespace flutter {
namespace gpu {

class RenderPass : public RefCountedDartWrappable<RenderPass> {
  DEFINE_WRAPPERTYPEINFO();
  FML_FRIEND_MAKE_REF_COUNTED(RenderPass);

 public:
  RenderPass();

  ~RenderPass() override;

  const std::weak_ptr<const impeller::Context>& GetContext() const;

  impeller::Command& GetCommand();
  const impeller::Command& GetCommand() const;

  impeller::RenderTarget& GetRenderTarget();
  const impeller::RenderTarget& GetRenderTarget() const;

  impeller::VertexBuffer& GetVertexBuffer();

  bool Begin(flutter::gpu::CommandBuffer& command_buffer);

  void SetPipeline(fml::RefPtr<RenderPipeline> pipeline);

  /// Lookup an Impeller pipeline by building a descriptor based on the current
  /// command state.
  std::shared_ptr<impeller::Pipeline<impeller::PipelineDescriptor>>
  GetOrCreatePipeline();

  impeller::Command ProvisionRasterCommand();

  bool Draw();

 private:
  impeller::RenderTarget render_target_;
  std::shared_ptr<impeller::RenderPass> render_pass_;

  // Command encoding state.
  impeller::Command command_;
  fml::RefPtr<RenderPipeline> render_pipeline_;
  impeller::PipelineDescriptor pipeline_descriptor_;

  // Pipeline descriptor layout state. We always keep track of this state, but
  // we'll only apply it as necessary to match the RenderTarget.
  impeller::ColorAttachmentDescriptor color_desc_;
  impeller::StencilAttachmentDescriptor stencil_front_desc_;
  impeller::StencilAttachmentDescriptor stencil_back_desc_;
  impeller::DepthAttachmentDescriptor depth_desc_;

  // Command state.
  impeller::VertexBuffer vertex_buffer_;

  FML_DISALLOW_COPY_AND_ASSIGN(RenderPass);
};

}  // namespace gpu
}  // namespace flutter

//----------------------------------------------------------------------------
/// Exports
///

extern "C" {

FLUTTER_GPU_EXPORT
extern void InternalFlutterGpu_RenderPass_Initialize(Dart_Handle wrapper);

FLUTTER_GPU_EXPORT
extern Dart_Handle InternalFlutterGpu_RenderPass_SetColorAttachment(
    flutter::gpu::RenderPass* wrapper,
    int load_action,
    int store_action,
    int clear_color,
    flutter::gpu::Texture* texture,
    Dart_Handle resolve_texture_wrapper);

FLUTTER_GPU_EXPORT
extern Dart_Handle InternalFlutterGpu_RenderPass_SetStencilAttachment(
    flutter::gpu::RenderPass* wrapper,
    int load_action,
    int store_action,
    int clear_stencil,
    flutter::gpu::Texture* texture);

FLUTTER_GPU_EXPORT
extern Dart_Handle InternalFlutterGpu_RenderPass_Begin(
    flutter::gpu::RenderPass* wrapper,
    flutter::gpu::CommandBuffer* command_buffer);

FLUTTER_GPU_EXPORT
extern void InternalFlutterGpu_RenderPass_BindPipeline(
    flutter::gpu::RenderPass* wrapper,
    flutter::gpu::RenderPipeline* pipeline);

FLUTTER_GPU_EXPORT
extern void InternalFlutterGpu_RenderPass_BindVertexBufferDevice(
    flutter::gpu::RenderPass* wrapper,
    flutter::gpu::DeviceBuffer* device_buffer,
    int offset_in_bytes,
    int length_in_bytes,
    int vertex_count);

FLUTTER_GPU_EXPORT
extern void InternalFlutterGpu_RenderPass_BindVertexBufferHost(
    flutter::gpu::RenderPass* wrapper,
    flutter::gpu::HostBuffer* host_buffer,
    int offset_in_bytes,
    int length_in_bytes,
    int vertex_count);

FLUTTER_GPU_EXPORT
extern bool InternalFlutterGpu_RenderPass_BindUniformDevice(
    flutter::gpu::RenderPass* wrapper,
    int stage,
    int slot_id,
    flutter::gpu::DeviceBuffer* device_buffer,
    int offset_in_bytes,
    int length_in_bytes);

FLUTTER_GPU_EXPORT
extern bool InternalFlutterGpu_RenderPass_BindUniformHost(
    flutter::gpu::RenderPass* wrapper,
    int stage,
    int slot_id,
    flutter::gpu::HostBuffer* host_buffer,
    int offset_in_bytes,
    int length_in_bytes);

FLUTTER_GPU_EXPORT
extern bool InternalFlutterGpu_RenderPass_Draw(
    flutter::gpu::RenderPass* wrapper);

}  // extern "C"
