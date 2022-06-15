#include "acc_state_machine.h"
#include "common/factory.h"
#include <iostream>

namespace miauto {
namespace function_management {

void ACCStateMachine::Init() {

  Factory::CreateACCState(this, ACCState::NOT_READY);
  Factory::CreateACCState(this, ACCState::NORMAL_ACTIVE);
  Factory::CreateACCState(this, ACCState::FAULT);
  Factory::CreateACCState(this, ACCState::HOLD);

  SetInitState(ACCState::NOT_READY);
}

} // namespace function_management
} // namespace miauto