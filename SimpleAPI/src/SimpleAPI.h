#pragma once

namespace SimpleAPI
{
  // callback function prototype
  typedef void (*Callback) (int id, void *closure);

  // register a callback handler
  void registerHandler(Callback callback, void *closure);

  // start dispatching
  void start();

  // stop dispatching
  void stop();
}
