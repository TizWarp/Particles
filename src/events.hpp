#pragma once

#include <cstdint>
#include <functional>
namespace Events {
enum {
  QUIT,
};

union EventContext{

};


typedef std::function<bool(EventContext)> EventCallback;
typedef uint32_t EventType;

struct EventListener{
  void *listener;
  EventCallback callback;
};

namespace Handler {
  void addListener(EventType eventType, void* listener, EventCallback callback);
  void fireEvent(EventType eventType, EventContext ctx);
  void removeListener(EventType eventType, void* listener);
};

}; // namespace Events
