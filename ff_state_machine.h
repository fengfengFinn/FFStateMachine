#pragma once
#include "./base/state_machine_base.h"
namespace miauto {
namespace function_management {

class FFStateBase : public StateMachineBase<StateEunm> {
public:
  FFStateBase() = default;

  ~FFStateBase() = default;

  void Init() override;

  std::string state_machine_data = "[data in state machine]";
};

} // namespace function_management
} // namespace miauto
