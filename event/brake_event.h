#pragma once
#include "../base/event_base.h"
#include <typeinfo>
namespace miauto {
namespace function_management {
class BrakeEvent : public EventBase {
public:
  bool brake_signal_value;
  BrakeEvent(u_int32_t type_id, bool brake_signal)
      : EventBase(type_id), brake_signal_value(brake_signal){};
  ~BrakeEvent() = default;

private:
};

} // namespace function_management
} // namespace miauto