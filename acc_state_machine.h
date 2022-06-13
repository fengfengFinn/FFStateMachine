#pragma once
#include "./base/state_machine_base.h"
namespace miauto {
namespace function_management {

class ACCStateMachine : public StateMachineBase<ACCState> {
public:
  ACCStateMachine() = default;

  ~ACCStateMachine() = default;

  void Init() override;
};

} // namespace function_management
} // namespace miauto
