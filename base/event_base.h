#pragma once

#include <string>

namespace miauto {
namespace function_management {

class EventBase {
public:
  EventBase(int type_id) : type_enum_id_(type_id){};
  virtual ~EventBase() = default;

  int type_enum_id() const { return type_enum_id_; }

private:
  int type_enum_id_;
};

} // namespace function_management
} // namespace miauto