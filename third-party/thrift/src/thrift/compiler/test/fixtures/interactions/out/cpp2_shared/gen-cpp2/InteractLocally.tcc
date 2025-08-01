/**
 * Autogenerated by Thrift for thrift/compiler/test/fixtures/interactions/src/shared.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include "thrift/compiler/test/fixtures/interactions/gen-cpp2/InteractLocally.h"

#include <thrift/lib/cpp2/gen/service_tcc.h>

namespace thrift::shared_interactions {

typedef apache::thrift::ThriftPresult<false> InteractLocally_SharedInteraction_init_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, ::apache::thrift::type_class::integral, ::std::int32_t*>> InteractLocally_SharedInteraction_init_presult;
typedef apache::thrift::ThriftPresult<false> InteractLocally_SharedInteraction_do_something_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, ::apache::thrift::type_class::structure, ::thrift::shared_interactions::DoSomethingResult*>> InteractLocally_SharedInteraction_do_something_presult;
typedef apache::thrift::ThriftPresult<false> InteractLocally_SharedInteraction_tear_down_pargs;
typedef apache::thrift::ThriftPresult<true> InteractLocally_SharedInteraction_tear_down_presult;
template <typename ProtocolIn_, typename ProtocolOut_>
void InteractLocallyAsyncProcessor::setUpAndProcess_SharedInteraction_init(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, [[maybe_unused]] apache::thrift::concurrency::ThreadManager* tm) {
  if (!setUpRequestProcessing(req, ctx, eb, tm, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, iface_, "SharedInteraction")) {
    return;
  }
  auto scope = iface_->getRequestExecutionScope(ctx, apache::thrift::concurrency::NORMAL);
  ctx->setRequestExecutionScope(std::move(scope));
  processInThread(std::move(req), std::move(serializedRequest), ctx, eb, tm, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &InteractLocallyAsyncProcessor::executeRequest_SharedInteraction_init<ProtocolIn_, ProtocolOut_>, this);
}

template <typename ProtocolIn_, typename ProtocolOut_>
void InteractLocallyAsyncProcessor::executeRequest_SharedInteraction_init(apache::thrift::ServerRequest&& serverRequest) {
  auto tile = serverRequest.requestContext()->releaseTile();
  // make sure getRequestContext is null
  // so async calls don't accidentally use it
  iface_->setRequestContext(nullptr);
  struct ArgsState {
    InteractLocally_SharedInteraction_init_pargs pargs() {
      InteractLocally_SharedInteraction_init_pargs args;
      return args;
    }

    auto asTupleOfRefs() & {
      return std::tie(
      );
    }
  } args;

  auto ctxStack = apache::thrift::ContextStack::create(
    this->getEventHandlersSharedPtr(),
    this->getServiceName(),
    "InteractLocally.SharedInteraction.init",
    serverRequest.requestContext());
  auto& iface = static_cast<apache::thrift::ServiceHandler<InteractLocally>::SharedInteractionIf&>(*tile);
  try {
    auto pargs = args.pargs();
    deserializeRequest<ProtocolIn_>(pargs, "SharedInteraction.init", apache::thrift::detail::ServerRequestHelper::compressedRequest(std::move(serverRequest)).uncompress(), ctxStack.get());
  }
  catch (...) {
    folly::exception_wrapper ew(std::current_exception());
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ew
        , apache::thrift::detail::ServerRequestHelper::request(std::move(serverRequest))
        , serverRequest.requestContext()
        , apache::thrift::detail::ServerRequestHelper::eventBase(serverRequest)
        , "SharedInteraction.init");
    return;
  }
  auto requestPileNotification = apache::thrift::detail::ServerRequestHelper::moveRequestPileNotification(serverRequest);
  auto concurrencyControllerNotification = apache::thrift::detail::ServerRequestHelper::moveConcurrencyControllerNotification(serverRequest);
  apache::thrift::HandlerCallbackBase::MethodNameInfo methodNameInfo{
    /* .serviceName =*/ this->getServiceName(),
    /* .definingServiceName =*/ "InteractLocally",
    /* .methodName =*/ "SharedInteraction.init",
    /* .qualifiedMethodName =*/ "InteractLocally.SharedInteraction.init"};
  auto callback = apache::thrift::HandlerCallbackPtr<::std::int32_t>::make(
    apache::thrift::detail::ServerRequestHelper::request(std::move(serverRequest))
    , std::move(ctxStack)
    , std::move(methodNameInfo)
    , return_SharedInteraction_init<ProtocolIn_,ProtocolOut_>
    , throw_wrapped_SharedInteraction_init<ProtocolIn_, ProtocolOut_>
    , serverRequest.requestContext()->getProtoSeqId()
    , apache::thrift::detail::ServerRequestHelper::eventBase(serverRequest)
    , apache::thrift::detail::ServerRequestHelper::executor(serverRequest)
    , serverRequest.requestContext()
    , requestPileNotification
    , concurrencyControllerNotification, std::move(serverRequest.requestData())
    , std::move(tile));
  const auto makeExecuteHandler = [&] {
    return [ifacePtr = &iface](auto&& cb, ArgsState args) mutable {
      (void)args;
      ifacePtr->async_tm_init(std::move(cb));
    };
  };
#if FOLLY_HAS_COROUTINES
  if (apache::thrift::detail::shouldProcessServiceInterceptorsOnRequest(*callback)) {
    [](auto callback, auto executeHandler, ArgsState args) -> folly::coro::Task<void> {
      auto argRefs = args.asTupleOfRefs();
      co_await apache::thrift::detail::processServiceInterceptorsOnRequest(
          *callback,
          apache::thrift::detail::ServiceInterceptorOnRequestArguments(argRefs));
      executeHandler(std::move(callback), std::move(args));
    }(std::move(callback), makeExecuteHandler(), std::move(args))
              .scheduleOn(apache::thrift::detail::ServerRequestHelper::executor(serverRequest))
              .startInlineUnsafe();
  } else {
    makeExecuteHandler()(std::move(callback), std::move(args));
  }
#else
  makeExecuteHandler()(std::move(callback), std::move(args));
#endif // FOLLY_HAS_COROUTINES
}

template <class ProtocolIn_, class ProtocolOut_>
apache::thrift::SerializedResponse InteractLocallyAsyncProcessor::return_SharedInteraction_init(apache::thrift::ContextStack* ctx, ::std::int32_t const& _return) {
  ProtocolOut_ prot;
  ::thrift::shared_interactions::InteractLocally_SharedInteraction_init_presult result;
  result.get<0>().value = const_cast<::std::int32_t*>(&_return);
  result.setIsSet(0, true);
  return serializeResponse("SharedInteraction.init", &prot, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void InteractLocallyAsyncProcessor::throw_wrapped_SharedInteraction_init(apache::thrift::ResponseChannelRequest::UniquePtr req,[[maybe_unused]] int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "SharedInteraction.init");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void InteractLocallyAsyncProcessor::setUpAndProcess_SharedInteraction_do_something(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, [[maybe_unused]] apache::thrift::concurrency::ThreadManager* tm) {
  if (!setUpRequestProcessing(req, ctx, eb, tm, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, iface_, "SharedInteraction")) {
    return;
  }
  auto scope = iface_->getRequestExecutionScope(ctx, apache::thrift::concurrency::NORMAL);
  ctx->setRequestExecutionScope(std::move(scope));
  processInThread(std::move(req), std::move(serializedRequest), ctx, eb, tm, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &InteractLocallyAsyncProcessor::executeRequest_SharedInteraction_do_something<ProtocolIn_, ProtocolOut_>, this);
}

template <typename ProtocolIn_, typename ProtocolOut_>
void InteractLocallyAsyncProcessor::executeRequest_SharedInteraction_do_something(apache::thrift::ServerRequest&& serverRequest) {
  auto tile = serverRequest.requestContext()->releaseTile();
  // make sure getRequestContext is null
  // so async calls don't accidentally use it
  iface_->setRequestContext(nullptr);
  struct ArgsState {
    InteractLocally_SharedInteraction_do_something_pargs pargs() {
      InteractLocally_SharedInteraction_do_something_pargs args;
      return args;
    }

    auto asTupleOfRefs() & {
      return std::tie(
      );
    }
  } args;

  auto ctxStack = apache::thrift::ContextStack::create(
    this->getEventHandlersSharedPtr(),
    this->getServiceName(),
    "InteractLocally.SharedInteraction.do_something",
    serverRequest.requestContext());
  auto& iface = static_cast<apache::thrift::ServiceHandler<InteractLocally>::SharedInteractionIf&>(*tile);
  try {
    auto pargs = args.pargs();
    deserializeRequest<ProtocolIn_>(pargs, "SharedInteraction.do_something", apache::thrift::detail::ServerRequestHelper::compressedRequest(std::move(serverRequest)).uncompress(), ctxStack.get());
  }
  catch (...) {
    folly::exception_wrapper ew(std::current_exception());
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ew
        , apache::thrift::detail::ServerRequestHelper::request(std::move(serverRequest))
        , serverRequest.requestContext()
        , apache::thrift::detail::ServerRequestHelper::eventBase(serverRequest)
        , "SharedInteraction.do_something");
    return;
  }
  auto requestPileNotification = apache::thrift::detail::ServerRequestHelper::moveRequestPileNotification(serverRequest);
  auto concurrencyControllerNotification = apache::thrift::detail::ServerRequestHelper::moveConcurrencyControllerNotification(serverRequest);
  apache::thrift::HandlerCallbackBase::MethodNameInfo methodNameInfo{
    /* .serviceName =*/ this->getServiceName(),
    /* .definingServiceName =*/ "InteractLocally",
    /* .methodName =*/ "SharedInteraction.do_something",
    /* .qualifiedMethodName =*/ "InteractLocally.SharedInteraction.do_something"};
  auto callback = apache::thrift::HandlerCallbackPtr<std::unique_ptr<::thrift::shared_interactions::DoSomethingResult>>::make(
    apache::thrift::detail::ServerRequestHelper::request(std::move(serverRequest))
    , std::move(ctxStack)
    , std::move(methodNameInfo)
    , return_SharedInteraction_do_something<ProtocolIn_,ProtocolOut_>
    , throw_wrapped_SharedInteraction_do_something<ProtocolIn_, ProtocolOut_>
    , serverRequest.requestContext()->getProtoSeqId()
    , apache::thrift::detail::ServerRequestHelper::eventBase(serverRequest)
    , apache::thrift::detail::ServerRequestHelper::executor(serverRequest)
    , serverRequest.requestContext()
    , requestPileNotification
    , concurrencyControllerNotification, std::move(serverRequest.requestData())
    , std::move(tile));
  const auto makeExecuteHandler = [&] {
    return [ifacePtr = &iface](auto&& cb, ArgsState args) mutable {
      (void)args;
      ifacePtr->async_tm_do_something(std::move(cb));
    };
  };
#if FOLLY_HAS_COROUTINES
  if (apache::thrift::detail::shouldProcessServiceInterceptorsOnRequest(*callback)) {
    [](auto callback, auto executeHandler, ArgsState args) -> folly::coro::Task<void> {
      auto argRefs = args.asTupleOfRefs();
      co_await apache::thrift::detail::processServiceInterceptorsOnRequest(
          *callback,
          apache::thrift::detail::ServiceInterceptorOnRequestArguments(argRefs));
      executeHandler(std::move(callback), std::move(args));
    }(std::move(callback), makeExecuteHandler(), std::move(args))
              .scheduleOn(apache::thrift::detail::ServerRequestHelper::executor(serverRequest))
              .startInlineUnsafe();
  } else {
    makeExecuteHandler()(std::move(callback), std::move(args));
  }
#else
  makeExecuteHandler()(std::move(callback), std::move(args));
#endif // FOLLY_HAS_COROUTINES
}

template <class ProtocolIn_, class ProtocolOut_>
apache::thrift::SerializedResponse InteractLocallyAsyncProcessor::return_SharedInteraction_do_something(apache::thrift::ContextStack* ctx, ::thrift::shared_interactions::DoSomethingResult const& _return) {
  ProtocolOut_ prot;
  ::thrift::shared_interactions::InteractLocally_SharedInteraction_do_something_presult result;
  result.get<0>().value = const_cast<::thrift::shared_interactions::DoSomethingResult*>(&_return);
  result.setIsSet(0, true);
  return serializeResponse("SharedInteraction.do_something", &prot, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void InteractLocallyAsyncProcessor::throw_wrapped_SharedInteraction_do_something(apache::thrift::ResponseChannelRequest::UniquePtr req,[[maybe_unused]] int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "SharedInteraction.do_something");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void InteractLocallyAsyncProcessor::setUpAndProcess_SharedInteraction_tear_down(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, [[maybe_unused]] apache::thrift::concurrency::ThreadManager* tm) {
  if (!setUpRequestProcessing(req, ctx, eb, tm, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, iface_, "SharedInteraction")) {
    return;
  }
  auto scope = iface_->getRequestExecutionScope(ctx, apache::thrift::concurrency::NORMAL);
  ctx->setRequestExecutionScope(std::move(scope));
  processInThread(std::move(req), std::move(serializedRequest), ctx, eb, tm, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &InteractLocallyAsyncProcessor::executeRequest_SharedInteraction_tear_down<ProtocolIn_, ProtocolOut_>, this);
}

template <typename ProtocolIn_, typename ProtocolOut_>
void InteractLocallyAsyncProcessor::executeRequest_SharedInteraction_tear_down(apache::thrift::ServerRequest&& serverRequest) {
  auto tile = serverRequest.requestContext()->releaseTile();
  // make sure getRequestContext is null
  // so async calls don't accidentally use it
  iface_->setRequestContext(nullptr);
  struct ArgsState {
    InteractLocally_SharedInteraction_tear_down_pargs pargs() {
      InteractLocally_SharedInteraction_tear_down_pargs args;
      return args;
    }

    auto asTupleOfRefs() & {
      return std::tie(
      );
    }
  } args;

  auto ctxStack = apache::thrift::ContextStack::create(
    this->getEventHandlersSharedPtr(),
    this->getServiceName(),
    "InteractLocally.SharedInteraction.tear_down",
    serverRequest.requestContext());
  auto& iface = static_cast<apache::thrift::ServiceHandler<InteractLocally>::SharedInteractionIf&>(*tile);
  try {
    auto pargs = args.pargs();
    deserializeRequest<ProtocolIn_>(pargs, "SharedInteraction.tear_down", apache::thrift::detail::ServerRequestHelper::compressedRequest(std::move(serverRequest)).uncompress(), ctxStack.get());
  }
  catch (...) {
    folly::exception_wrapper ew(std::current_exception());
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ew
        , apache::thrift::detail::ServerRequestHelper::request(std::move(serverRequest))
        , serverRequest.requestContext()
        , apache::thrift::detail::ServerRequestHelper::eventBase(serverRequest)
        , "SharedInteraction.tear_down");
    return;
  }
  auto requestPileNotification = apache::thrift::detail::ServerRequestHelper::moveRequestPileNotification(serverRequest);
  auto concurrencyControllerNotification = apache::thrift::detail::ServerRequestHelper::moveConcurrencyControllerNotification(serverRequest);
  apache::thrift::HandlerCallbackBase::MethodNameInfo methodNameInfo{
    /* .serviceName =*/ this->getServiceName(),
    /* .definingServiceName =*/ "InteractLocally",
    /* .methodName =*/ "SharedInteraction.tear_down",
    /* .qualifiedMethodName =*/ "InteractLocally.SharedInteraction.tear_down"};
  auto callback = apache::thrift::HandlerCallbackPtr<void>::make(
    apache::thrift::detail::ServerRequestHelper::request(std::move(serverRequest))
    , std::move(ctxStack)
    , std::move(methodNameInfo)
    , return_SharedInteraction_tear_down<ProtocolIn_,ProtocolOut_>
    , throw_wrapped_SharedInteraction_tear_down<ProtocolIn_, ProtocolOut_>
    , serverRequest.requestContext()->getProtoSeqId()
    , apache::thrift::detail::ServerRequestHelper::eventBase(serverRequest)
    , apache::thrift::detail::ServerRequestHelper::executor(serverRequest)
    , serverRequest.requestContext()
    , requestPileNotification
    , concurrencyControllerNotification, std::move(serverRequest.requestData())
    , std::move(tile));
  const auto makeExecuteHandler = [&] {
    return [ifacePtr = &iface](auto&& cb, ArgsState args) mutable {
      (void)args;
      ifacePtr->async_tm_tear_down(std::move(cb));
    };
  };
#if FOLLY_HAS_COROUTINES
  if (apache::thrift::detail::shouldProcessServiceInterceptorsOnRequest(*callback)) {
    [](auto callback, auto executeHandler, ArgsState args) -> folly::coro::Task<void> {
      auto argRefs = args.asTupleOfRefs();
      co_await apache::thrift::detail::processServiceInterceptorsOnRequest(
          *callback,
          apache::thrift::detail::ServiceInterceptorOnRequestArguments(argRefs));
      executeHandler(std::move(callback), std::move(args));
    }(std::move(callback), makeExecuteHandler(), std::move(args))
              .scheduleOn(apache::thrift::detail::ServerRequestHelper::executor(serverRequest))
              .startInlineUnsafe();
  } else {
    makeExecuteHandler()(std::move(callback), std::move(args));
  }
#else
  makeExecuteHandler()(std::move(callback), std::move(args));
#endif // FOLLY_HAS_COROUTINES
}

template <class ProtocolIn_, class ProtocolOut_>
apache::thrift::SerializedResponse InteractLocallyAsyncProcessor::return_SharedInteraction_tear_down(apache::thrift::ContextStack* ctx) {
  ProtocolOut_ prot;
  ::thrift::shared_interactions::InteractLocally_SharedInteraction_tear_down_presult result;
  return serializeResponse("SharedInteraction.tear_down", &prot, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void InteractLocallyAsyncProcessor::throw_wrapped_SharedInteraction_tear_down(apache::thrift::ResponseChannelRequest::UniquePtr req,[[maybe_unused]] int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "SharedInteraction.tear_down");
    return;
  }
}

} // namespace thrift::shared_interactions
