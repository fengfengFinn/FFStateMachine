#pragma once
#include "../base/event_base.h"
#include <typeinfo>
namespace miauto {
namespace function_management {
class ErrorEvent : public EventBase {
public:
  ErrorEvent(u_int32_t type_id) : EventBase(type_id){};
  ~ErrorEvent() = default;

private:
};

} // namespace function_management
} // namespace miauto