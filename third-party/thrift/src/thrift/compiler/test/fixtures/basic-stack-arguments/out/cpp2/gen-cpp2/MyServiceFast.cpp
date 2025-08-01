/**
 * Autogenerated by Thrift for thrift/compiler/test/fixtures/basic-stack-arguments/src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */

#include "thrift/compiler/test/fixtures/basic-stack-arguments/gen-cpp2/MyServiceFast.h"
#include "thrift/compiler/test/fixtures/basic-stack-arguments/gen-cpp2/MyServiceFast.tcc"
#include "thrift/compiler/test/fixtures/basic-stack-arguments/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

std::unique_ptr<apache::thrift::AsyncProcessor> apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::getProcessor() {
  return std::make_unique<::cpp2::MyServiceFastAsyncProcessor>(this);
}

apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::CreateMethodMetadataResult apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::createMethodMetadata() {
  return ::apache::thrift::detail::ap::createMethodMetadataMap<::cpp2::MyServiceFastAsyncProcessor>(getServiceRequestInfoMap().value().get());
}


std::optional<std::reference_wrapper<apache::thrift::ServiceRequestInfoMap const>> apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::getServiceRequestInfoMap() const {
  return __fbthrift_serviceInfoHolder.requestInfoMap();
}

::cpp2::MyServiceFastServiceInfoHolder apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::__fbthrift_serviceInfoHolder;


void apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::async_eb_hasDataById(apache::thrift::HandlerCallbackPtr<bool> callback, ::std::int64_t /*id*/) {
  callback->exception(apache::thrift::detail::si::create_app_exn_unimplemented("hasDataById"));
}

void apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::async_eb_getDataById(apache::thrift::HandlerCallbackPtr<::std::string> callback, ::std::int64_t /*id*/) {
  callback->exception(apache::thrift::detail::si::create_app_exn_unimplemented("getDataById"));
}

void apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::async_eb_putDataById(apache::thrift::HandlerCallbackPtr<void> callback, ::std::int64_t /*id*/, const ::std::string& /*data*/) {
  callback->exception(apache::thrift::detail::si::create_app_exn_unimplemented("putDataById"));
}

void apache::thrift::ServiceHandler<::cpp2::MyServiceFast>::async_eb_lobDataById(apache::thrift::HandlerCallbackOneWay::Ptr /*callback*/, ::std::int64_t /*id*/, const ::std::string& /*data*/) {
  LOG(DFATAL) << "Function lobDataById is unimplemented";
}


namespace cpp2 {


std::string_view MyServiceFastAsyncProcessor::getServiceName() {
  return "MyServiceFast";
}

void MyServiceFastAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<::apache::thrift::ServiceHandler<::cpp2::MyServiceFast>>::gen(response);
}

void MyServiceFastAsyncProcessor::processSerializedCompressedRequestWithMetadata(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, iface_, std::move(req), std::move(serializedRequest), methodMetadata, protType, context, eb, tm);
}

void MyServiceFastAsyncProcessor::executeRequest(apache::thrift::ServerRequest&& request, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata) {
  apache::thrift::detail::ap::execute(this, std::move(request), apache::thrift::detail::ServerRequestHelper::protocol(request), methodMetadata);
}

const MyServiceFastAsyncProcessor::ProcessMap& MyServiceFastAsyncProcessor::getOwnProcessMap() {
  return kOwnProcessMap_;
}

const MyServiceFastAsyncProcessor::ProcessMap MyServiceFastAsyncProcessor::kOwnProcessMap_ {
  {"hasDataById",
    {&MyServiceFastAsyncProcessor::setUpAndProcess_hasDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::setUpAndProcess_hasDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_hasDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_hasDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"getDataById",
    {&MyServiceFastAsyncProcessor::setUpAndProcess_getDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::setUpAndProcess_getDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_getDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_getDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"putDataById",
    {&MyServiceFastAsyncProcessor::setUpAndProcess_putDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::setUpAndProcess_putDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_putDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_putDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"lobDataById",
    {&MyServiceFastAsyncProcessor::setUpAndProcess_lobDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::setUpAndProcess_lobDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_lobDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &MyServiceFastAsyncProcessor::executeRequest_lobDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
};

apache::thrift::ServiceRequestInfoMap const& MyServiceFastServiceInfoHolder::requestInfoMap() const {
  static folly::Indestructible<apache::thrift::ServiceRequestInfoMap> requestInfoMap{staticRequestInfoMap()};
  return *requestInfoMap;
}

apache::thrift::ServiceRequestInfoMap MyServiceFastServiceInfoHolder::staticRequestInfoMap() {
  apache::thrift::ServiceRequestInfoMap requestInfoMap = {
  {"hasDataById",
    { true,
     apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE,
     "MyServiceFast.hasDataById",
     std::nullopt,
     apache::thrift::concurrency::NORMAL,
     std::nullopt}},
  {"getDataById",
    { true,
     apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE,
     "MyServiceFast.getDataById",
     std::nullopt,
     apache::thrift::concurrency::NORMAL,
     std::nullopt}},
  {"putDataById",
    { true,
     apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE,
     "MyServiceFast.putDataById",
     std::nullopt,
     apache::thrift::concurrency::NORMAL,
     std::nullopt}},
  {"lobDataById",
    { true,
     apache::thrift::RpcKind::SINGLE_REQUEST_NO_RESPONSE,
     "MyServiceFast.lobDataById",
     std::nullopt,
     apache::thrift::concurrency::NORMAL,
     std::nullopt}},
  };

  return requestInfoMap;
}
} // namespace cpp2

namespace apache::thrift::detail {
::folly::Range<const ::std::string_view*>(*TSchemaAssociation<::cpp2::MyServiceFast, false>::bundle)() =
    nullptr;
}
