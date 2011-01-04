// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CameraInfo.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace naothmessages {

namespace {

const ::google::protobuf::Descriptor* CameraInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CameraInfo_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* CameraInfo_CameraID_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_CameraInfo_2eproto() {
  protobuf_AddDesc_CameraInfo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "CameraInfo.proto");
  GOOGLE_CHECK(file != NULL);
  CameraInfo_descriptor_ = file->message_type(0);
  static const int CameraInfo_offsets_[12] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, resolutionwidth_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, resolutionheight_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, cameraid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, focallength_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, openinganglewidth_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, openingangleheight_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, opticalcenterx_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, opticalcentery_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, memorysize_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, camerarolloffset_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, cameratiltoffset_),
  };
  CameraInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CameraInfo_descriptor_,
      CameraInfo::default_instance_,
      CameraInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CameraInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CameraInfo));
  CameraInfo_CameraID_descriptor_ = CameraInfo_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_CameraInfo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CameraInfo_descriptor_, &CameraInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_CameraInfo_2eproto() {
  delete CameraInfo::default_instance_;
  delete CameraInfo_reflection_;
}

void protobuf_AddDesc_CameraInfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020CameraInfo.proto\022\rnaothmessages\"\360\002\n\nCa"
    "meraInfo\022\027\n\017resolutionWidth\030\001 \002(\005\022\030\n\020res"
    "olutionHeight\030\002 \002(\005\022<\n\010cameraID\030\004 \001(\0162\"."
    "naothmessages.CameraInfo.CameraID:\006botto"
    "m\022\023\n\013focalLength\030\005 \001(\001\022\031\n\021openingAngleWi"
    "dth\030\006 \001(\001\022\032\n\022openingAngleHeight\030\007 \001(\001\022\026\n"
    "\016opticalCenterX\030\010 \001(\001\022\026\n\016opticalCenterY\030"
    "\t \001(\001\022\014\n\004size\030\n \001(\003\022\022\n\nmemorysize\030\013 \001(\003\022"
    "\030\n\020cameraRollOffset\030\014 \001(\001\022\030\n\020cameraTiltO"
    "ffset\030\r \001(\001\"\037\n\010CameraID\022\007\n\003top\020\000\022\n\n\006bott"
    "om\020\001B8\n\'de.hu_berlin.informatik.ki.nao.m"
    "essagesB\rCameraInfoMsg", 462);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CameraInfo.proto", &protobuf_RegisterTypes);
  CameraInfo::default_instance_ = new CameraInfo();
  CameraInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_CameraInfo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_CameraInfo_2eproto {
  StaticDescriptorInitializer_CameraInfo_2eproto() {
    protobuf_AddDesc_CameraInfo_2eproto();
  }
} static_descriptor_initializer_CameraInfo_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* CameraInfo_CameraID_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CameraInfo_CameraID_descriptor_;
}
bool CameraInfo_CameraID_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const CameraInfo_CameraID CameraInfo::top;
const CameraInfo_CameraID CameraInfo::bottom;
const CameraInfo_CameraID CameraInfo::CameraID_MIN;
const CameraInfo_CameraID CameraInfo::CameraID_MAX;
const int CameraInfo::CameraID_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int CameraInfo::kResolutionWidthFieldNumber;
const int CameraInfo::kResolutionHeightFieldNumber;
const int CameraInfo::kCameraIDFieldNumber;
const int CameraInfo::kFocalLengthFieldNumber;
const int CameraInfo::kOpeningAngleWidthFieldNumber;
const int CameraInfo::kOpeningAngleHeightFieldNumber;
const int CameraInfo::kOpticalCenterXFieldNumber;
const int CameraInfo::kOpticalCenterYFieldNumber;
const int CameraInfo::kSizeFieldNumber;
const int CameraInfo::kMemorysizeFieldNumber;
const int CameraInfo::kCameraRollOffsetFieldNumber;
const int CameraInfo::kCameraTiltOffsetFieldNumber;
#endif  // !_MSC_VER

CameraInfo::CameraInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void CameraInfo::InitAsDefaultInstance() {
}

CameraInfo::CameraInfo(const CameraInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void CameraInfo::SharedCtor() {
  _cached_size_ = 0;
  resolutionwidth_ = 0;
  resolutionheight_ = 0;
  cameraid_ = 1;
  focallength_ = 0;
  openinganglewidth_ = 0;
  openingangleheight_ = 0;
  opticalcenterx_ = 0;
  opticalcentery_ = 0;
  size_ = GOOGLE_LONGLONG(0);
  memorysize_ = GOOGLE_LONGLONG(0);
  camerarolloffset_ = 0;
  cameratiltoffset_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CameraInfo::~CameraInfo() {
  SharedDtor();
}

void CameraInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void CameraInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CameraInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CameraInfo_descriptor_;
}

const CameraInfo& CameraInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_CameraInfo_2eproto();  return *default_instance_;
}

CameraInfo* CameraInfo::default_instance_ = NULL;

CameraInfo* CameraInfo::New() const {
  return new CameraInfo;
}

void CameraInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    resolutionwidth_ = 0;
    resolutionheight_ = 0;
    cameraid_ = 1;
    focallength_ = 0;
    openinganglewidth_ = 0;
    openingangleheight_ = 0;
    opticalcenterx_ = 0;
    opticalcentery_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    size_ = GOOGLE_LONGLONG(0);
    memorysize_ = GOOGLE_LONGLONG(0);
    camerarolloffset_ = 0;
    cameratiltoffset_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CameraInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 resolutionWidth = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &resolutionwidth_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_resolutionHeight;
        break;
      }
      
      // required int32 resolutionHeight = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_resolutionHeight:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &resolutionheight_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_cameraID;
        break;
      }
      
      // optional .naothmessages.CameraInfo.CameraID cameraID = 4 [default = bottom];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cameraID:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::naothmessages::CameraInfo_CameraID_IsValid(value)) {
            set_cameraid(static_cast< ::naothmessages::CameraInfo_CameraID >(value));
          } else {
            mutable_unknown_fields()->AddVarint(4, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(41)) goto parse_focalLength;
        break;
      }
      
      // optional double focalLength = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_focalLength:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &focallength_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(49)) goto parse_openingAngleWidth;
        break;
      }
      
      // optional double openingAngleWidth = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_openingAngleWidth:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &openinganglewidth_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(57)) goto parse_openingAngleHeight;
        break;
      }
      
      // optional double openingAngleHeight = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_openingAngleHeight:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &openingangleheight_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(65)) goto parse_opticalCenterX;
        break;
      }
      
      // optional double opticalCenterX = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_opticalCenterX:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &opticalcenterx_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(73)) goto parse_opticalCenterY;
        break;
      }
      
      // optional double opticalCenterY = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_opticalCenterY:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &opticalcentery_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_size;
        break;
      }
      
      // optional int64 size = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &size_)));
          _set_bit(8);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(88)) goto parse_memorysize;
        break;
      }
      
      // optional int64 memorysize = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_memorysize:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &memorysize_)));
          _set_bit(9);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(97)) goto parse_cameraRollOffset;
        break;
      }
      
      // optional double cameraRollOffset = 12;
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_cameraRollOffset:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &camerarolloffset_)));
          _set_bit(10);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(105)) goto parse_cameraTiltOffset;
        break;
      }
      
      // optional double cameraTiltOffset = 13;
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_cameraTiltOffset:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &cameratiltoffset_)));
          _set_bit(11);
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

void CameraInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 resolutionWidth = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->resolutionwidth(), output);
  }
  
  // required int32 resolutionHeight = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->resolutionheight(), output);
  }
  
  // optional .naothmessages.CameraInfo.CameraID cameraID = 4 [default = bottom];
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->cameraid(), output);
  }
  
  // optional double focalLength = 5;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->focallength(), output);
  }
  
  // optional double openingAngleWidth = 6;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->openinganglewidth(), output);
  }
  
  // optional double openingAngleHeight = 7;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->openingangleheight(), output);
  }
  
  // optional double opticalCenterX = 8;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(8, this->opticalcenterx(), output);
  }
  
  // optional double opticalCenterY = 9;
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(9, this->opticalcentery(), output);
  }
  
  // optional int64 size = 10;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(10, this->size(), output);
  }
  
  // optional int64 memorysize = 11;
  if (_has_bit(9)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(11, this->memorysize(), output);
  }
  
  // optional double cameraRollOffset = 12;
  if (_has_bit(10)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(12, this->camerarolloffset(), output);
  }
  
  // optional double cameraTiltOffset = 13;
  if (_has_bit(11)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(13, this->cameratiltoffset(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* CameraInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 resolutionWidth = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->resolutionwidth(), target);
  }
  
  // required int32 resolutionHeight = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->resolutionheight(), target);
  }
  
  // optional .naothmessages.CameraInfo.CameraID cameraID = 4 [default = bottom];
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      4, this->cameraid(), target);
  }
  
  // optional double focalLength = 5;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->focallength(), target);
  }
  
  // optional double openingAngleWidth = 6;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->openinganglewidth(), target);
  }
  
  // optional double openingAngleHeight = 7;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->openingangleheight(), target);
  }
  
  // optional double opticalCenterX = 8;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(8, this->opticalcenterx(), target);
  }
  
  // optional double opticalCenterY = 9;
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(9, this->opticalcentery(), target);
  }
  
  // optional int64 size = 10;
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(10, this->size(), target);
  }
  
  // optional int64 memorysize = 11;
  if (_has_bit(9)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(11, this->memorysize(), target);
  }
  
  // optional double cameraRollOffset = 12;
  if (_has_bit(10)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(12, this->camerarolloffset(), target);
  }
  
  // optional double cameraTiltOffset = 13;
  if (_has_bit(11)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(13, this->cameratiltoffset(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int CameraInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 resolutionWidth = 1;
    if (has_resolutionwidth()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->resolutionwidth());
    }
    
    // required int32 resolutionHeight = 2;
    if (has_resolutionheight()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->resolutionheight());
    }
    
    // optional .naothmessages.CameraInfo.CameraID cameraID = 4 [default = bottom];
    if (has_cameraid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->cameraid());
    }
    
    // optional double focalLength = 5;
    if (has_focallength()) {
      total_size += 1 + 8;
    }
    
    // optional double openingAngleWidth = 6;
    if (has_openinganglewidth()) {
      total_size += 1 + 8;
    }
    
    // optional double openingAngleHeight = 7;
    if (has_openingangleheight()) {
      total_size += 1 + 8;
    }
    
    // optional double opticalCenterX = 8;
    if (has_opticalcenterx()) {
      total_size += 1 + 8;
    }
    
    // optional double opticalCenterY = 9;
    if (has_opticalcentery()) {
      total_size += 1 + 8;
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional int64 size = 10;
    if (has_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->size());
    }
    
    // optional int64 memorysize = 11;
    if (has_memorysize()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->memorysize());
    }
    
    // optional double cameraRollOffset = 12;
    if (has_camerarolloffset()) {
      total_size += 1 + 8;
    }
    
    // optional double cameraTiltOffset = 13;
    if (has_cameratiltoffset()) {
      total_size += 1 + 8;
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

void CameraInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CameraInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CameraInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CameraInfo::MergeFrom(const CameraInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_resolutionwidth(from.resolutionwidth());
    }
    if (from._has_bit(1)) {
      set_resolutionheight(from.resolutionheight());
    }
    if (from._has_bit(2)) {
      set_cameraid(from.cameraid());
    }
    if (from._has_bit(3)) {
      set_focallength(from.focallength());
    }
    if (from._has_bit(4)) {
      set_openinganglewidth(from.openinganglewidth());
    }
    if (from._has_bit(5)) {
      set_openingangleheight(from.openingangleheight());
    }
    if (from._has_bit(6)) {
      set_opticalcenterx(from.opticalcenterx());
    }
    if (from._has_bit(7)) {
      set_opticalcentery(from.opticalcentery());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_size(from.size());
    }
    if (from._has_bit(9)) {
      set_memorysize(from.memorysize());
    }
    if (from._has_bit(10)) {
      set_camerarolloffset(from.camerarolloffset());
    }
    if (from._has_bit(11)) {
      set_cameratiltoffset(from.cameratiltoffset());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CameraInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CameraInfo::CopyFrom(const CameraInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CameraInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void CameraInfo::Swap(CameraInfo* other) {
  if (other != this) {
    std::swap(resolutionwidth_, other->resolutionwidth_);
    std::swap(resolutionheight_, other->resolutionheight_);
    std::swap(cameraid_, other->cameraid_);
    std::swap(focallength_, other->focallength_);
    std::swap(openinganglewidth_, other->openinganglewidth_);
    std::swap(openingangleheight_, other->openingangleheight_);
    std::swap(opticalcenterx_, other->opticalcenterx_);
    std::swap(opticalcentery_, other->opticalcentery_);
    std::swap(size_, other->size_);
    std::swap(memorysize_, other->memorysize_);
    std::swap(camerarolloffset_, other->camerarolloffset_);
    std::swap(cameratiltoffset_, other->cameratiltoffset_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CameraInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CameraInfo_descriptor_;
  metadata.reflection = CameraInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace naothmessages

// @@protoc_insertion_point(global_scope)
