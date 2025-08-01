/**
 * Autogenerated by Thrift for thrift/compiler/test/fixtures/basic-stack-arguments/src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */

#include "thrift/compiler/test/fixtures/basic-stack-arguments/gen-cpp2/DbMixedStackArguments.h"
#include "thrift/compiler/test/fixtures/basic-stack-arguments/gen-cpp2/DbMixedStackArguments.tcc"
#include "thrift/compiler/test/fixtures/basic-stack-arguments/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

std::unique_ptr<apache::thrift::AsyncProcessor> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::getProcessor() {
  return std::make_unique<::cpp2::DbMixedStackArgumentsAsyncProcessor>(this);
}

apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::CreateMethodMetadataResult apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::createMethodMetadata() {
  return ::apache::thrift::detail::ap::createMethodMetadataMap<::cpp2::DbMixedStackArgumentsAsyncProcessor>(getServiceRequestInfoMap().value().get());
}


std::optional<std::reference_wrapper<apache::thrift::ServiceRequestInfoMap const>> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::getServiceRequestInfoMap() const {
  return __fbthrift_serviceInfoHolder.requestInfoMap();
}

::cpp2::DbMixedStackArgumentsServiceInfoHolder apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::__fbthrift_serviceInfoHolder;


void apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::getDataByKey0(::std::string& /*_return*/, std::unique_ptr<::std::string> /*key*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getDataByKey0");
}

void apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::sync_getDataByKey0(::std::string& _return, std::unique_ptr<::std::string> p_key) {
  return getDataByKey0(_return, std::move(p_key));
}

folly::SemiFuture<std::unique_ptr<::std::string>> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::semifuture_getDataByKey0(std::unique_ptr<::std::string> p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_getDataByKey0.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  auto ret = std::make_unique<::std::string>();
  sync_getDataByKey0(*ret, std::move(p_key));
  return folly::makeSemiFuture(std::move(ret));
}

folly::Future<std::unique_ptr<::std::string>> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::future_getDataByKey0(std::unique_ptr<::std::string> p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_getDataByKey0.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_getDataByKey0(std::move(p_key)), getInternalKeepAlive());
}

#if FOLLY_HAS_COROUTINES
folly::coro::Task<std::unique_ptr<::std::string>> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::co_getDataByKey0(std::unique_ptr<::std::string> p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::Coro};
  __fbthrift_invocation_getDataByKey0.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
  folly::throw_exception(apache::thrift::detail::si::UnimplementedCoroMethod::withCapturedArgs<std::unique_ptr<::std::string> /*key*/>(std::move(p_key)));
}

folly::coro::Task<std::unique_ptr<::std::string>> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::co_getDataByKey0(apache::thrift::RequestParams /* params */, std::unique_ptr<::std::string> p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::CoroParam};
  __fbthrift_invocation_getDataByKey0.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Coro, std::memory_order_relaxed);
  return co_getDataByKey0(std::move(p_key));
}
#endif // FOLLY_HAS_COROUTINES

void apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::async_tm_getDataByKey0(apache::thrift::HandlerCallbackPtr<std::unique_ptr<::std::string>> callback, std::unique_ptr<::std::string> p_key) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
#if FOLLY_HAS_COROUTINES
determineInvocationType:
#endif // FOLLY_HAS_COROUTINES
  auto invocationType = __fbthrift_invocation_getDataByKey0.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
#if FOLLY_HAS_COROUTINES
        __fbthrift_invocation_getDataByKey0.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::CoroParam, std::memory_order_relaxed);
        apache::thrift::RequestParams params{callback->getRequestContext(),
          callback->getThreadManager_deprecated(), callback->getEventBase(), callback->getHandlerExecutor()};
        auto task = co_getDataByKey0(params, std::move(p_key));
        apache::thrift::detail::si::async_tm_coro(std::move(callback), std::move(task));
        return;
#else // FOLLY_HAS_COROUTINES
        __fbthrift_invocation_getDataByKey0.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        [[fallthrough]];
#endif // FOLLY_HAS_COROUTINES
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_getDataByKey0(std::move(p_key));
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_getDataByKey0(std::move(p_key));
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
#if FOLLY_HAS_COROUTINES
      case apache::thrift::detail::si::InvocationType::CoroParam:
      {
        apache::thrift::RequestParams params{callback->getRequestContext(),
          callback->getThreadManager_deprecated(), callback->getEventBase(), callback->getHandlerExecutor()};
        auto task = co_getDataByKey0(params, std::move(p_key));
        apache::thrift::detail::si::async_tm_coro(std::move(callback), std::move(task));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Coro:
      {
        auto task = co_getDataByKey0(std::move(p_key));
        apache::thrift::detail::si::async_tm_coro(std::move(callback), std::move(task));
        return;
      }
#endif // FOLLY_HAS_COROUTINES
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        ::std::string _return;
        sync_getDataByKey0(_return, std::move(p_key));
        callback->result(std::move(_return));
        return;
      }
      default:
      {
        folly::assume_unreachable();
      }
    }
#if FOLLY_HAS_COROUTINES
  } catch (apache::thrift::detail::si::UnimplementedCoroMethod& ex) {
    std::tie(p_key) = std::move(ex).restoreArgs<std::unique_ptr<::std::string> /*key*/>();
    goto determineInvocationType;
#endif // FOLLY_HAS_COROUTINES
  } catch (...) {
    callback->exception(std::current_exception());
  }
}

void apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::getDataByKey1(::std::string& /*_return*/, const ::std::string& /*key*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getDataByKey1");
}

void apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::sync_getDataByKey1(::std::string& _return, const ::std::string& p_key) {
  return getDataByKey1(_return, p_key);
}

folly::SemiFuture<::std::string> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::semifuture_getDataByKey1(const ::std::string& p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_getDataByKey1.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  ::std::string ret;
  sync_getDataByKey1(ret, p_key);
  return folly::makeSemiFuture(std::move(ret));
}

folly::Future<::std::string> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::future_getDataByKey1(const ::std::string& p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_getDataByKey1.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_getDataByKey1(p_key), getInternalKeepAlive());
}

#if FOLLY_HAS_COROUTINES
folly::coro::Task<::std::string> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::co_getDataByKey1(const ::std::string& p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::Coro};
  __fbthrift_invocation_getDataByKey1.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
  apache::thrift::detail::si::ignore(p_key);
  folly::throw_exception(apache::thrift::detail::si::UnimplementedCoroMethod::withoutCapturedArgs());
}

folly::coro::Task<::std::string> apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::co_getDataByKey1(apache::thrift::RequestParams /* params */, const ::std::string& p_key) {
  auto expected{apache::thrift::detail::si::InvocationType::CoroParam};
  __fbthrift_invocation_getDataByKey1.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Coro, std::memory_order_relaxed);
  return co_getDataByKey1(p_key);
}
#endif // FOLLY_HAS_COROUTINES

void apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>::async_tm_getDataByKey1(apache::thrift::HandlerCallbackPtr<::std::string> callback, const ::std::string& p_key) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
#if FOLLY_HAS_COROUTINES
determineInvocationType:
#endif // FOLLY_HAS_COROUTINES
  auto invocationType = __fbthrift_invocation_getDataByKey1.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
#if FOLLY_HAS_COROUTINES
        __fbthrift_invocation_getDataByKey1.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::CoroParam, std::memory_order_relaxed);
        apache::thrift::RequestParams params{callback->getRequestContext(),
          callback->getThreadManager_deprecated(), callback->getEventBase(), callback->getHandlerExecutor()};
        auto task = co_getDataByKey1(params, p_key);
        apache::thrift::detail::si::async_tm_coro(std::move(callback), std::move(task));
        return;
#else // FOLLY_HAS_COROUTINES
        __fbthrift_invocation_getDataByKey1.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        [[fallthrough]];
#endif // FOLLY_HAS_COROUTINES
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_getDataByKey1(p_key);
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_getDataByKey1(p_key);
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
#if FOLLY_HAS_COROUTINES
      case apache::thrift::detail::si::InvocationType::CoroParam:
      {
        apache::thrift::RequestParams params{callback->getRequestContext(),
          callback->getThreadManager_deprecated(), callback->getEventBase(), callback->getHandlerExecutor()};
        auto task = co_getDataByKey1(params, p_key);
        apache::thrift::detail::si::async_tm_coro(std::move(callback), std::move(task));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Coro:
      {
        auto task = co_getDataByKey1(p_key);
        apache::thrift::detail::si::async_tm_coro(std::move(callback), std::move(task));
        return;
      }
#endif // FOLLY_HAS_COROUTINES
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        ::std::string _return;
        sync_getDataByKey1(_return, p_key);
        callback->result(std::move(_return));
        return;
      }
      default:
      {
        folly::assume_unreachable();
      }
    }
#if FOLLY_HAS_COROUTINES
  } catch (apache::thrift::detail::si::UnimplementedCoroMethod&) {
    goto determineInvocationType;
#endif // FOLLY_HAS_COROUTINES
  } catch (...) {
    callback->exception(std::current_exception());
  }
}


namespace cpp2 {

void DbMixedStackArgumentsSvNull::getDataByKey0(::std::string& /*_return*/, std::unique_ptr<::std::string> /*key*/) {  }

void DbMixedStackArgumentsSvNull::getDataByKey1(::std::string& /*_return*/, const ::std::string& /*key*/) {  }


std::string_view DbMixedStackArgumentsAsyncProcessor::getServiceName() {
  return "DbMixedStackArguments";
}

void DbMixedStackArgumentsAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<::apache::thrift::ServiceHandler<::cpp2::DbMixedStackArguments>>::gen(response);
}

void DbMixedStackArgumentsAsyncProcessor::processSerializedCompressedRequestWithMetadata(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, iface_, std::move(req), std::move(serializedRequest), methodMetadata, protType, context, eb, tm);
}

void DbMixedStackArgumentsAsyncProcessor::executeRequest(apache::thrift::ServerRequest&& request, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata) {
  apache::thrift::detail::ap::execute(this, std::move(request), apache::thrift::detail::ServerRequestHelper::protocol(request), methodMetadata);
}

const DbMixedStackArgumentsAsyncProcessor::ProcessMap& DbMixedStackArgumentsAsyncProcessor::getOwnProcessMap() {
  return kOwnProcessMap_;
}

const DbMixedStackArgumentsAsyncProcessor::ProcessMap DbMixedStackArgumentsAsyncProcessor::kOwnProcessMap_ {
  {"getDataByKey0",
    {&DbMixedStackArgumentsAsyncProcessor::setUpAndProcess_getDataByKey0<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &DbMixedStackArgumentsAsyncProcessor::setUpAndProcess_getDataByKey0<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>,
     &DbMixedStackArgumentsAsyncProcessor::executeRequest_getDataByKey0<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &DbMixedStackArgumentsAsyncProcessor::executeRequest_getDataByKey0<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"getDataByKey1",
    {&DbMixedStackArgumentsAsyncProcessor::setUpAndProcess_getDataByKey1<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &DbMixedStackArgumentsAsyncProcessor::setUpAndProcess_getDataByKey1<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>,
     &DbMixedStackArgumentsAsyncProcessor::executeRequest_getDataByKey1<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>,
     &DbMixedStackArgumentsAsyncProcessor::executeRequest_getDataByKey1<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
};

apache::thrift::ServiceRequestInfoMap const& DbMixedStackArgumentsServiceInfoHolder::requestInfoMap() const {
  static folly::Indestructible<apache::thrift::ServiceRequestInfoMap> requestInfoMap{staticRequestInfoMap()};
  return *requestInfoMap;
}

apache::thrift::ServiceRequestInfoMap DbMixedStackArgumentsServiceInfoHolder::staticRequestInfoMap() {
  apache::thrift::ServiceRequestInfoMap requestInfoMap = {
  {"getDataByKey0",
    { false,
     apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE,
     "DbMixedStackArguments.getDataByKey0",
     std::nullopt,
     apache::thrift::concurrency::NORMAL,
     std::nullopt}},
  {"getDataByKey1",
    { false,
     apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE,
     "DbMixedStackArguments.getDataByKey1",
     std::nullopt,
     apache::thrift::concurrency::NORMAL,
     std::nullopt}},
  };

  return requestInfoMap;
}
} // namespace cpp2

namespace apache::thrift::detail {
::folly::Range<const ::std::string_view*>(*TSchemaAssociation<::cpp2::DbMixedStackArguments, false>::bundle)() =
    nullptr;
}
