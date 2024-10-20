#include "events.hpp"
#include <vector>

namespace Events::Handler{
  static std::vector<EventListener> listeners[512];
}

void Events::Handler::removeListener(Events::EventType eventType, void *listener){
  std::vector<EventListener> &listener_vec = listeners[eventType];
  for (int index = 0; index < listener_vec.size(); index++){
    if (listener_vec[index].listener == listener){
      listener_vec.erase(listener_vec.begin() + index);
    }
  }
}

void Events::Handler::addListener(Events::EventType eventType, void *listener, EventCallback callback){
  listeners[eventType].push_back(EventListener{listener, callback});
}

void Events::Handler::fireEvent(Events::EventType eventType, Events::EventContext ctx){
  for (EventListener listener : listeners[eventType]){
    if (listener.callback(ctx)){
      return;
    }
  }
}
