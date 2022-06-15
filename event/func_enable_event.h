#pragma once
#include "../base/event_base.h"
#include <typeinfo>
namespace miauto {
namespace function_management {
class FuncEnableEvent : public EventBase {
public:
  FuncEnableEvent(u_int32_t type_id) : EventBase(type_id){};
  ~FuncEnableEvent() = default;

private:
};

} // namespace function_management
} // namespace miauto