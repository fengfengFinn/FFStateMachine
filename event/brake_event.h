#pragma once
#include "../base/event_base.h"
#include <typeinfo>
namespace miauto {
namespace function_management {
class BrakeEvent : public EventBase {
public:
  BrakeEvent(u_int32_t type_id, int brake_percentage)
      : EventBase(type_id), brake_percentage_(brake_percentage){};
  ~BrakeEvent() = default;

private:
  int brake_percentage_;
};

} // namespace function_management
} // namespace miauto