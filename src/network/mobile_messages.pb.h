// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mobile_messages.proto

#ifndef PROTOBUF_INCLUDED_mobile_5fmessages_2eproto
#define PROTOBUF_INCLUDED_mobile_5fmessages_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_mobile_5fmessages_2eproto 

namespace protobuf_mobile_5fmessages_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_mobile_5fmessages_2eproto
namespace mobile_messages {
class HandshakeRequest;
class HandshakeRequestDefaultTypeInternal;
extern HandshakeRequestDefaultTypeInternal _HandshakeRequest_default_instance_;
class HandshakeResponse;
class HandshakeResponseDefaultTypeInternal;
extern HandshakeResponseDefaultTypeInternal _HandshakeResponse_default_instance_;
class NetworkMessage;
class NetworkMessageDefaultTypeInternal;
extern NetworkMessageDefaultTypeInternal _NetworkMessage_default_instance_;
}  // namespace mobile_messages
namespace google {
namespace protobuf {
template<> ::mobile_messages::HandshakeRequest* Arena::CreateMaybeMessage<::mobile_messages::HandshakeRequest>(Arena*);
template<> ::mobile_messages::HandshakeResponse* Arena::CreateMaybeMessage<::mobile_messages::HandshakeResponse>(Arena*);
template<> ::mobile_messages::NetworkMessage* Arena::CreateMaybeMessage<::mobile_messages::NetworkMessage>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace mobile_messages {

enum HandshakeResponse_ResponseType {
  HandshakeResponse_ResponseType_OK = 0,
  HandshakeResponse_ResponseType_NOK = 1
};
bool HandshakeResponse_ResponseType_IsValid(int value);
const HandshakeResponse_ResponseType HandshakeResponse_ResponseType_ResponseType_MIN = HandshakeResponse_ResponseType_OK;
const HandshakeResponse_ResponseType HandshakeResponse_ResponseType_ResponseType_MAX = HandshakeResponse_ResponseType_NOK;
const int HandshakeResponse_ResponseType_ResponseType_ARRAYSIZE = HandshakeResponse_ResponseType_ResponseType_MAX + 1;

const ::google::protobuf::EnumDescriptor* HandshakeResponse_ResponseType_descriptor();
inline const ::std::string& HandshakeResponse_ResponseType_Name(HandshakeResponse_ResponseType value) {
  return ::google::protobuf::internal::NameOfEnum(
    HandshakeResponse_ResponseType_descriptor(), value);
}
inline bool HandshakeResponse_ResponseType_Parse(
    const ::std::string& name, HandshakeResponse_ResponseType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<HandshakeResponse_ResponseType>(
    HandshakeResponse_ResponseType_descriptor(), name, value);
}
// ===================================================================

class NetworkMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mobile_messages.NetworkMessage) */ {
 public:
  NetworkMessage();
  virtual ~NetworkMessage();

  NetworkMessage(const NetworkMessage& from);

  inline NetworkMessage& operator=(const NetworkMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NetworkMessage(NetworkMessage&& from) noexcept
    : NetworkMessage() {
    *this = ::std::move(from);
  }

  inline NetworkMessage& operator=(NetworkMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const NetworkMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NetworkMessage* internal_default_instance() {
    return reinterpret_cast<const NetworkMessage*>(
               &_NetworkMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(NetworkMessage* other);
  friend void swap(NetworkMessage& a, NetworkMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NetworkMessage* New() const final {
    return CreateMaybeMessage<NetworkMessage>(NULL);
  }

  NetworkMessage* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<NetworkMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const NetworkMessage& from);
  void MergeFrom(const NetworkMessage& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NetworkMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 messageId = 1;
  bool has_messageid() const;
  void clear_messageid();
  static const int kMessageIdFieldNumber = 1;
  ::google::protobuf::int32 messageid() const;
  void set_messageid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:mobile_messages.NetworkMessage)
 private:
  void set_has_messageid();
  void clear_has_messageid();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 messageid_;
  friend struct ::protobuf_mobile_5fmessages_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class HandshakeRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mobile_messages.HandshakeRequest) */ {
 public:
  HandshakeRequest();
  virtual ~HandshakeRequest();

  HandshakeRequest(const HandshakeRequest& from);

  inline HandshakeRequest& operator=(const HandshakeRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  HandshakeRequest(HandshakeRequest&& from) noexcept
    : HandshakeRequest() {
    *this = ::std::move(from);
  }

  inline HandshakeRequest& operator=(HandshakeRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const HandshakeRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const HandshakeRequest* internal_default_instance() {
    return reinterpret_cast<const HandshakeRequest*>(
               &_HandshakeRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(HandshakeRequest* other);
  friend void swap(HandshakeRequest& a, HandshakeRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HandshakeRequest* New() const final {
    return CreateMaybeMessage<HandshakeRequest>(NULL);
  }

  HandshakeRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<HandshakeRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const HandshakeRequest& from);
  void MergeFrom(const HandshakeRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HandshakeRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 messageId = 1;
  bool has_messageid() const;
  void clear_messageid();
  static const int kMessageIdFieldNumber = 1;
  ::google::protobuf::int32 messageid() const;
  void set_messageid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:mobile_messages.HandshakeRequest)
 private:
  void set_has_messageid();
  void clear_has_messageid();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 messageid_;
  friend struct ::protobuf_mobile_5fmessages_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class HandshakeResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mobile_messages.HandshakeResponse) */ {
 public:
  HandshakeResponse();
  virtual ~HandshakeResponse();

  HandshakeResponse(const HandshakeResponse& from);

  inline HandshakeResponse& operator=(const HandshakeResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  HandshakeResponse(HandshakeResponse&& from) noexcept
    : HandshakeResponse() {
    *this = ::std::move(from);
  }

  inline HandshakeResponse& operator=(HandshakeResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const HandshakeResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const HandshakeResponse* internal_default_instance() {
    return reinterpret_cast<const HandshakeResponse*>(
               &_HandshakeResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(HandshakeResponse* other);
  friend void swap(HandshakeResponse& a, HandshakeResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HandshakeResponse* New() const final {
    return CreateMaybeMessage<HandshakeResponse>(NULL);
  }

  HandshakeResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<HandshakeResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const HandshakeResponse& from);
  void MergeFrom(const HandshakeResponse& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HandshakeResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef HandshakeResponse_ResponseType ResponseType;
  static const ResponseType OK =
    HandshakeResponse_ResponseType_OK;
  static const ResponseType NOK =
    HandshakeResponse_ResponseType_NOK;
  static inline bool ResponseType_IsValid(int value) {
    return HandshakeResponse_ResponseType_IsValid(value);
  }
  static const ResponseType ResponseType_MIN =
    HandshakeResponse_ResponseType_ResponseType_MIN;
  static const ResponseType ResponseType_MAX =
    HandshakeResponse_ResponseType_ResponseType_MAX;
  static const int ResponseType_ARRAYSIZE =
    HandshakeResponse_ResponseType_ResponseType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  ResponseType_descriptor() {
    return HandshakeResponse_ResponseType_descriptor();
  }
  static inline const ::std::string& ResponseType_Name(ResponseType value) {
    return HandshakeResponse_ResponseType_Name(value);
  }
  static inline bool ResponseType_Parse(const ::std::string& name,
      ResponseType* value) {
    return HandshakeResponse_ResponseType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required int32 messageId = 1;
  bool has_messageid() const;
  void clear_messageid();
  static const int kMessageIdFieldNumber = 1;
  ::google::protobuf::int32 messageid() const;
  void set_messageid(::google::protobuf::int32 value);

  // required int32 mobileId = 2;
  bool has_mobileid() const;
  void clear_mobileid();
  static const int kMobileIdFieldNumber = 2;
  ::google::protobuf::int32 mobileid() const;
  void set_mobileid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:mobile_messages.HandshakeResponse)
 private:
  void set_has_messageid();
  void clear_has_messageid();
  void set_has_mobileid();
  void clear_has_mobileid();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 messageid_;
  ::google::protobuf::int32 mobileid_;
  friend struct ::protobuf_mobile_5fmessages_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NetworkMessage

// required int32 messageId = 1;
inline bool NetworkMessage::has_messageid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NetworkMessage::set_has_messageid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NetworkMessage::clear_has_messageid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NetworkMessage::clear_messageid() {
  messageid_ = 0;
  clear_has_messageid();
}
inline ::google::protobuf::int32 NetworkMessage::messageid() const {
  // @@protoc_insertion_point(field_get:mobile_messages.NetworkMessage.messageId)
  return messageid_;
}
inline void NetworkMessage::set_messageid(::google::protobuf::int32 value) {
  set_has_messageid();
  messageid_ = value;
  // @@protoc_insertion_point(field_set:mobile_messages.NetworkMessage.messageId)
}

// -------------------------------------------------------------------

// HandshakeRequest

// required int32 messageId = 1;
inline bool HandshakeRequest::has_messageid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void HandshakeRequest::set_has_messageid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void HandshakeRequest::clear_has_messageid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void HandshakeRequest::clear_messageid() {
  messageid_ = 0;
  clear_has_messageid();
}
inline ::google::protobuf::int32 HandshakeRequest::messageid() const {
  // @@protoc_insertion_point(field_get:mobile_messages.HandshakeRequest.messageId)
  return messageid_;
}
inline void HandshakeRequest::set_messageid(::google::protobuf::int32 value) {
  set_has_messageid();
  messageid_ = value;
  // @@protoc_insertion_point(field_set:mobile_messages.HandshakeRequest.messageId)
}

// -------------------------------------------------------------------

// HandshakeResponse

// required int32 messageId = 1;
inline bool HandshakeResponse::has_messageid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void HandshakeResponse::set_has_messageid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void HandshakeResponse::clear_has_messageid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void HandshakeResponse::clear_messageid() {
  messageid_ = 0;
  clear_has_messageid();
}
inline ::google::protobuf::int32 HandshakeResponse::messageid() const {
  // @@protoc_insertion_point(field_get:mobile_messages.HandshakeResponse.messageId)
  return messageid_;
}
inline void HandshakeResponse::set_messageid(::google::protobuf::int32 value) {
  set_has_messageid();
  messageid_ = value;
  // @@protoc_insertion_point(field_set:mobile_messages.HandshakeResponse.messageId)
}

// required int32 mobileId = 2;
inline bool HandshakeResponse::has_mobileid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void HandshakeResponse::set_has_mobileid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void HandshakeResponse::clear_has_mobileid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void HandshakeResponse::clear_mobileid() {
  mobileid_ = 0;
  clear_has_mobileid();
}
inline ::google::protobuf::int32 HandshakeResponse::mobileid() const {
  // @@protoc_insertion_point(field_get:mobile_messages.HandshakeResponse.mobileId)
  return mobileid_;
}
inline void HandshakeResponse::set_mobileid(::google::protobuf::int32 value) {
  set_has_mobileid();
  mobileid_ = value;
  // @@protoc_insertion_point(field_set:mobile_messages.HandshakeResponse.mobileId)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mobile_messages

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::mobile_messages::HandshakeResponse_ResponseType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::mobile_messages::HandshakeResponse_ResponseType>() {
  return ::mobile_messages::HandshakeResponse_ResponseType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_mobile_5fmessages_2eproto
