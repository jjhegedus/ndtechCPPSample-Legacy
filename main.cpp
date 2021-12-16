#include "pch.h"

#include "ndtechSampleApp.h"
#include <memory>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

#if NDTECH_WIN
#include <TraceLoggingProvider.h>

//#include "CustomSink.h"
#include <g3log_tracelogging/g3log_tracelogging.h>

TRACELOGGING_DEFINE_PROVIDER(
  traceProvider,
  "ndtech",
  // {c78f9e8e-2e05-5320-8f4e-7bd922ecb3a0}
  (0xc78f9e8e, 0x2e05, 0x5320, 0x8f, 0x4e, 0x7b, 0xd9, 0x22, 0xec, 0xb3, 0xa0));
#endif

#if NDTECH_HOLO

class AppViewSource sealed : public winrt::implements<AppViewSource, winrt::Windows::ApplicationModel::Core::IFrameworkViewSource>
{
public:
    // IFrameworkViewSource method.
  winrt::Windows::ApplicationModel::Core::IFrameworkView CreateView() {
    return app;
  };

private:
  ndtech::sample::ndtechSampleApp app;
};

// The main function bootstraps into the IFrameworkView.
int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
  TraceLoggingRegister(traceProvider);

  using namespace g3;
  std::unique_ptr<LogWorker> logworker{ LogWorker::createLogWorker() };
  auto sinkHandle = logworker->addSink(std::make_unique<g3logTracelogging>(),
    &g3logTracelogging::ReceiveLogMessage);

  // initialize the logger before it can receive LOG calls
  initializeLogging(logworker.get());

  winrt::init_apartment();
  winrt::Windows::ApplicationModel::Core::CoreApplication::Run(AppViewSource());

#endif

#if NDTECH_ML
#include <g3logMagicLeap/g3logMagicLeap.h>
#endif

#if NDTECH_ML
  int main() {
    {
#if NDTECH_WIN
      TraceLoggingRegister(traceProvider);
#endif
      using namespace g3;
      std::unique_ptr<LogWorker> logworker{ LogWorker::createLogWorker() };
#if NDTECH_WIN
      auto sinkHandle = logworker->addSink(std::make_unique<g3logTracelogging>(),
        &g3logTracelogging::ReceiveLogMessage);
      auto sinkHandle2 = logworker->addSink(std::make_unique<g3logMagicLeap>(),
        &g3logMagicLeap::ReceiveLogMessage);
#endif
#if ML_DEVICE
      auto sinkHandle = logworker->addSink(std::make_unique<g3logMagicLeap>(),
        &g3logMagicLeap::ReceiveLogMessage);
#endif

      // initialize the logger before it can receive LOG calls
      initializeLogging(logworker.get());
      // and set the log level for the magic leap
      MLLoggingEnableLogLevel(MLLogLevel::MLLogLevel_Info);

      ndtech::sample::ndtechSampleApp app;

      app.Configure();

      app.Run();
    }

#endif
   
  return 0;
}
