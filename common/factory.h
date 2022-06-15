#pragma once
#include "../acc_state_machine.h"
#include "../state/fault_state.cc"
#include "../state/fault_state.h"
#include "../state/hold_state.cc"
#include "../state/hold_state.h"
#include "../state/normal_active_state.cc"
#include "../state/normal_active_state.h"
#include "../state/not_ready_state.cc"
#include "../state/not_ready_state.h"
#include <iostream>
#include <memory>

namespace miauto {
namespace function_management {
class Factory {
public:
  static void CreateACCState(ACCStateMachine *state_machine,
                             ACCState state_enum) {
    std::unique_ptr<StateBase<ACCState>> res_state;
    switch (state_enum) {
    case ACCState::NOT_READY:
      res_state = std::make_unique<ACCNotReadyState>(state_machine,
                                                     ACCState::NOT_READY);
      break;
    case ACCState::NORMAL_ACTIVE:
      res_state = std::make_unique<ACCNormalActiveState>(
          state_machine, ACCState::NORMAL_ACTIVE);
      break;
    case ACCState::FAULT:
      res_state =
          std::make_unique<ACCFaultState>(state_machine, ACCState::FAULT);
      break;
    case ACCState::HOLD:
      res_state = std::make_unique<ACCHoldState>(state_machine, ACCState::HOLD);
      break;

    default:
      break;
    }
    state_machine->AddState(state_enum, std::move(res_state));
  }
};
} // namespace function_management
} // namespace miauto
