// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "FrameInfo.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace naothmessages {

namespace {

const ::google::protobuf::Descriptor* FrameInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FrameInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_FrameInfo_2eproto() {
  protobuf_AddDesc_FrameInfo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "FrameInfo.proto");
  GOOGLE_CHECK(file != NULL);
  FrameInfo_descriptor_ = file->message_type(0);
  static const int FrameInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FrameInfo, framenumber_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FrameInfo, time_),
  };
  FrameInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FrameInfo_descriptor_,
      FrameInfo::default_instance_,
      FrameInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FrameInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FrameInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FrameInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_FrameInfo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FrameInfo_descriptor_, &FrameInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_FrameInfo_2eproto() {
  delete FrameInfo::default_instance_;
  delete FrameInfo_reflection_;
}

void protobuf_AddDesc_FrameInfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017FrameInfo.proto\022\rnaothmessages\".\n\tFram"
    "eInfo\022\023\n\013frameNumber\030\001 \001(\r\022\014\n\004time\030\002 \001(\r"
    "B7\n\'de.hu_berlin.informatik.ki.nao.messa"
    "gesB\014FrameInfoMsg", 137);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "FrameInfo.proto", &protobuf_RegisterTypes);
  FrameInfo::default_instance_ = new FrameInfo();
  FrameInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_FrameInfo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_FrameInfo_2eproto {
  StaticDescriptorInitializer_FrameInfo_2eproto() {
    protobuf_AddDesc_FrameInfo_2eproto();
  }
} static_descriptor_initializer_FrameInfo_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int FrameInfo::kFrameNumberFieldNumber;
const int FrameInfo::kTimeFieldNumber;
#endif  // !_MSC_VER

FrameInfo::FrameInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FrameInfo::InitAsDefaultInstance() {
}

FrameInfo::FrameInfo(const FrameInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FrameInfo::SharedCtor() {
  _cached_size_ = 0;
  framenumber_ = 0u;
  time_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FrameInfo::~FrameInfo() {
  SharedDtor();
}

void FrameInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void FrameInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FrameInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FrameInfo_descriptor_;
}

const FrameInfo& FrameInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_FrameInfo_2eproto();  return *default_instance_;
}

FrameInfo* FrameInfo::default_instance_ = NULL;

FrameInfo* FrameInfo::New() const {
  return new FrameInfo;
}

void FrameInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    framenumber_ = 0u;
    time_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FrameInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 frameNumber = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &framenumber_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_time;
        break;
      }
      
      // optional uint32 time = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &time_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FrameInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 frameNumber = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->framenumber(), output);
  }
  
  // optional uint32 time = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->time(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FrameInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 frameNumber = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->framenumber(), target);
  }
  
  // optional uint32 time = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->time(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FrameInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 frameNumber = 1;
    if (has_framenumber()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->framenumber());
    }
    
    // optional uint32 time = 2;
    if (has_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->time());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FrameInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FrameInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FrameInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FrameInfo::MergeFrom(const FrameInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_framenumber(from.framenumber());
    }
    if (from._has_bit(1)) {
      set_time(from.time());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FrameInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FrameInfo::CopyFrom(const FrameInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FrameInfo::IsInitialized() const {
  
  return true;
}

void FrameInfo::Swap(FrameInfo* other) {
  if (other != this) {
    std::swap(framenumber_, other->framenumber_);
    std::swap(time_, other->time_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FrameInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FrameInfo_descriptor_;
  metadata.reflection = FrameInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace naothmessages

// @@protoc_insertion_point(global_scope)
