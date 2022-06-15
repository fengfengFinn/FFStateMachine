#pragma once
#include "../base/event_base.h"
#include <typeinfo>
namespace miauto {
namespace function_management {
class PedalStepOnEvent : public EventBase {
public:
  PedalStepOnEvent(u_int32_t type_id) : EventBase(type_id){};
  ~PedalStepOnEvent() = default;

private:
};

} // namespace function_management
} // namespace miauto