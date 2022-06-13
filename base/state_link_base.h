#pragma once

#include <functional>
#include <utility>

#include "event_base.h"

namespace miauto {
namespace function_management {

using EventBaseConstVectorRef = std::vector<EventBase> const &;

template <typename TSE> class StateLinkBase {
public:
  StateLinkBase(std::function<bool(EventBaseConstVectorRef)> condition_function,
                TSE target_state_enum)
      : condition_function_(condition_function),
        target_state_enum_(target_state_enum){};

  StateLinkBase(std::function<bool(EventBaseConstVectorRef)> condition_function,
                TSE target_state_enum,
                std::function<void(void)> action_function)
      : condition_function_(condition_function),
        target_state_enum_(target_state_enum),
        action_function_(action_function){};

  StateLinkBase(std::function<bool(EventBaseConstVectorRef)> condition_function,
                TSE target_state_enum,
                std::function<void(void)> action_function,
                std::function<bool(void)> transit_condition_function)
      : condition_function_(condition_function),
        target_state_enum_(target_state_enum) {
    if (action_function_ == nullptr)
      return;
    action_function_ = action_function;
    transit_condition_function_ = transit_condition_function;
  };

  virtual ~StateLinkBase() = default;

  std::function<bool(EventBaseConstVectorRef)> &condition_function() {
    return condition_function_;
  }
  std::function<void(void)> &action_function() { return action_function_; }
  std::function<bool(void)> &transit_condition_function() {
    return transit_condition_function_;
  }

  TSE &target_state_enum() { return target_state_enum_; }

private:
  std::function<bool(EventBaseConstVectorRef)> condition_function_;
  TSE target_state_enum_;
  std::function<void(void)> action_function_;
  std::function<bool(void)> transit_condition_function_;
};

} // namespace function_management
} // namespace miauto