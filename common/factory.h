#pragma once
#include "../ff_state_machine.h"
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
  static void CreateState(FFStateBase *state_machine, StateEunm state_enum) {
    std::unique_ptr<StateBase<StateEunm>> res_state;
    switch (state_enum) {
    case StateEunm::NOT_READY:
      res_state =
          std::make_unique<NotReadyState>(state_machine, StateEunm::NOT_READY);
      break;
    case StateEunm::NORMAL_ACTIVE:
      res_state = std::make_unique<NormalActiveState>(state_machine,
                                                      StateEunm::NORMAL_ACTIVE);
      break;
    case StateEunm::FAULT:
      res_state = std::make_unique<FaultState>(state_machine, StateEunm::FAULT);
      break;
    case StateEunm::HOLD:
      res_state = std::make_unique<HoldState>(state_machine, StateEunm::HOLD);
      break;

    default:
      break;
    }
    state_machine->AddState(state_enum, std::move(res_state));
  }
};
} // namespace function_management
} // namespace miauto
