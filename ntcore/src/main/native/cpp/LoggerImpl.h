// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef NTCORE_LOGGERIMPL_H_
#define NTCORE_LOGGERIMPL_H_

#include <utility>

#include <wpi/CallbackManager.h>

#include "Handle.h"
#include "ntcore_cpp.h"

namespace nt {

namespace impl {

struct LoggerListenerData : public wpi::CallbackListenerData<
                                std::function<void(const LogMessage& msg)>> {
  LoggerListenerData() = default;
  LoggerListenerData(std::function<void(const LogMessage& msg)> callback_,
                     unsigned int min_level_, unsigned int max_level_)
      : CallbackListenerData(callback_),
        min_level(min_level_),
        max_level(max_level_) {}
  LoggerListenerData(unsigned int poller_uid_, unsigned int min_level_,
                     unsigned int max_level_)
      : CallbackListenerData(poller_uid_),
        min_level(min_level_),
        max_level(max_level_) {}

  unsigned int min_level;
  unsigned int max_level;
};

class LoggerThread
    : public wpi::CallbackThread<LoggerThread, LogMessage, LoggerListenerData> {
 public:
  LoggerThread(std::function<void()> on_start, std::function<void()> on_exit,
               int inst)
      : CallbackThread(std::move(on_start), std::move(on_exit)), m_inst(inst) {}

  bool Matches(const LoggerListenerData& listener, const LogMessage& data) {
    return data.level >= listener.min_level && data.level <= listener.max_level;
  }

  void SetListener(LogMessage* data, unsigned int listener_uid) {
    data->logger = Handle(m_inst, listener_uid, Handle::kLogger).handle();
  }

  void DoCallback(std::function<void(const LogMessage& msg)> callback,
                  const LogMessage& data) {
    callback(data);
  }

  int m_inst;
};

}  // namespace impl

class LoggerImpl : public wpi::CallbackManager<LoggerImpl, impl::LoggerThread> {
  friend class LoggerTest;
  friend class wpi::CallbackManager<LoggerImpl, impl::LoggerThread>;

 public:
  explicit LoggerImpl(int inst);

  void Start();

  unsigned int Add(std::function<void(const LogMessage& msg)> callback,
                   unsigned int min_level, unsigned int max_level);
  unsigned int AddPolled(unsigned int poller_uid, unsigned int min_level,
                         unsigned int max_level);

  unsigned int GetMinLevel();

  void Log(unsigned int level, const char* file, unsigned int line,
           const char* msg);

 private:
  int m_inst;
};

}  // namespace nt

#endif  // NTCORE_LOGGERIMPL_H_
