// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Image.proto

#ifndef PROTOBUF_Image_2eproto__INCLUDED
#define PROTOBUF_Image_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "CameraInfo.pb.h"
// @@protoc_insertion_point(includes)

namespace naothmessages {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Image_2eproto();
void protobuf_AssignDesc_Image_2eproto();
void protobuf_ShutdownFile_Image_2eproto();

class Image;

enum Image_Format {
  Image_Format_YUV = 0,
  Image_Format_YUV422 = 1
};
bool Image_Format_IsValid(int value);
const Image_Format Image_Format_Format_MIN = Image_Format_YUV;
const Image_Format Image_Format_Format_MAX = Image_Format_YUV422;
const int Image_Format_Format_ARRAYSIZE = Image_Format_Format_MAX + 1;

const ::google::protobuf::EnumDescriptor* Image_Format_descriptor();
inline const ::std::string& Image_Format_Name(Image_Format value) {
  return ::google::protobuf::internal::NameOfEnum(
    Image_Format_descriptor(), value);
}
inline bool Image_Format_Parse(
    const ::std::string& name, Image_Format* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Image_Format>(
    Image_Format_descriptor(), name, value);
}
// ===================================================================

class Image : public ::google::protobuf::Message {
 public:
  Image();
  virtual ~Image();
  
  Image(const Image& from);
  
  inline Image& operator=(const Image& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Image& default_instance();
  
  void Swap(Image* other);
  
  // implements Message ----------------------------------------------
  
  Image* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Image& from);
  void MergeFrom(const Image& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Image_Format Format;
  static const Format YUV = Image_Format_YUV;
  static const Format YUV422 = Image_Format_YUV422;
  static inline bool Format_IsValid(int value) {
    return Image_Format_IsValid(value);
  }
  static const Format Format_MIN =
    Image_Format_Format_MIN;
  static const Format Format_MAX =
    Image_Format_Format_MAX;
  static const int Format_ARRAYSIZE =
    Image_Format_Format_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Format_descriptor() {
    return Image_Format_descriptor();
  }
  static inline const ::std::string& Format_Name(Format value) {
    return Image_Format_Name(value);
  }
  static inline bool Format_Parse(const ::std::string& name,
      Format* value) {
    return Image_Format_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required bytes data = 1;
  inline bool has_data() const;
  inline void clear_data();
  static const int kDataFieldNumber = 1;
  inline const ::std::string& data() const;
  inline void set_data(const ::std::string& value);
  inline void set_data(const char* value);
  inline void set_data(const void* value, size_t size);
  inline ::std::string* mutable_data();
  
  // optional int32 width = 2 [default = 320];
  inline bool has_width() const;
  inline void clear_width();
  static const int kWidthFieldNumber = 2;
  inline ::google::protobuf::int32 width() const;
  inline void set_width(::google::protobuf::int32 value);
  
  // optional int32 height = 3 [default = 240];
  inline bool has_height() const;
  inline void clear_height();
  static const int kHeightFieldNumber = 3;
  inline ::google::protobuf::int32 height() const;
  inline void set_height(::google::protobuf::int32 value);
  
  // optional .naothmessages.CameraInfo cameraInfo = 4;
  inline bool has_camerainfo() const;
  inline void clear_camerainfo();
  static const int kCameraInfoFieldNumber = 4;
  inline const ::naothmessages::CameraInfo& camerainfo() const;
  inline ::naothmessages::CameraInfo* mutable_camerainfo();
  
  // optional .naothmessages.Image.Format format = 5 [default = YUV];
  inline bool has_format() const;
  inline void clear_format();
  static const int kFormatFieldNumber = 5;
  inline ::naothmessages::Image_Format format() const;
  inline void set_format(::naothmessages::Image_Format value);
  
  // @@protoc_insertion_point(class_scope:naothmessages.Image)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* data_;
  static const ::std::string _default_data_;
  ::google::protobuf::int32 width_;
  ::google::protobuf::int32 height_;
  ::naothmessages::CameraInfo* camerainfo_;
  int format_;
  friend void  protobuf_AddDesc_Image_2eproto();
  friend void protobuf_AssignDesc_Image_2eproto();
  friend void protobuf_ShutdownFile_Image_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Image* default_instance_;
};
// ===================================================================


// ===================================================================

// Image

// required bytes data = 1;
inline bool Image::has_data() const {
  return _has_bit(0);
}
inline void Image::clear_data() {
  if (data_ != &_default_data_) {
    data_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Image::data() const {
  return *data_;
}
inline void Image::set_data(const ::std::string& value) {
  _set_bit(0);
  if (data_ == &_default_data_) {
    data_ = new ::std::string;
  }
  data_->assign(value);
}
inline void Image::set_data(const char* value) {
  _set_bit(0);
  if (data_ == &_default_data_) {
    data_ = new ::std::string;
  }
  data_->assign(value);
}
inline void Image::set_data(const void* value, size_t size) {
  _set_bit(0);
  if (data_ == &_default_data_) {
    data_ = new ::std::string;
  }
  data_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Image::mutable_data() {
  _set_bit(0);
  if (data_ == &_default_data_) {
    data_ = new ::std::string;
  }
  return data_;
}

// optional int32 width = 2 [default = 320];
inline bool Image::has_width() const {
  return _has_bit(1);
}
inline void Image::clear_width() {
  width_ = 320;
  _clear_bit(1);
}
inline ::google::protobuf::int32 Image::width() const {
  return width_;
}
inline void Image::set_width(::google::protobuf::int32 value) {
  _set_bit(1);
  width_ = value;
}

// optional int32 height = 3 [default = 240];
inline bool Image::has_height() const {
  return _has_bit(2);
}
inline void Image::clear_height() {
  height_ = 240;
  _clear_bit(2);
}
inline ::google::protobuf::int32 Image::height() const {
  return height_;
}
inline void Image::set_height(::google::protobuf::int32 value) {
  _set_bit(2);
  height_ = value;
}

// optional .naothmessages.CameraInfo cameraInfo = 4;
inline bool Image::has_camerainfo() const {
  return _has_bit(3);
}
inline void Image::clear_camerainfo() {
  if (camerainfo_ != NULL) camerainfo_->::naothmessages::CameraInfo::Clear();
  _clear_bit(3);
}
inline const ::naothmessages::CameraInfo& Image::camerainfo() const {
  return camerainfo_ != NULL ? *camerainfo_ : *default_instance_->camerainfo_;
}
inline ::naothmessages::CameraInfo* Image::mutable_camerainfo() {
  _set_bit(3);
  if (camerainfo_ == NULL) camerainfo_ = new ::naothmessages::CameraInfo;
  return camerainfo_;
}

// optional .naothmessages.Image.Format format = 5 [default = YUV];
inline bool Image::has_format() const {
  return _has_bit(4);
}
inline void Image::clear_format() {
  format_ = 0;
  _clear_bit(4);
}
inline ::naothmessages::Image_Format Image::format() const {
  return static_cast< ::naothmessages::Image_Format >(format_);
}
inline void Image::set_format(::naothmessages::Image_Format value) {
  GOOGLE_DCHECK(::naothmessages::Image_Format_IsValid(value));
  _set_bit(4);
  format_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace naothmessages

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::naothmessages::Image_Format>() {
  return ::naothmessages::Image_Format_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Image_2eproto__INCLUDED
