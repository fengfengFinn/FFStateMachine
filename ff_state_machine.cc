#include "ff_state_machine.h"
#include "common/factory.h"
#include <iostream>

namespace miauto {
namespace function_management {

void FFStateBase::Init() {

  Factory::CreateState(this, StateEunm::NOT_READY);
  Factory::CreateState(this, StateEunm::NORMAL_ACTIVE);
  Factory::CreateState(this, StateEunm::FAULT);
  Factory::CreateState(this, StateEunm::HOLD);

  SetInitState(StateEunm::NOT_READY);
}

} // namespace function_management
} // namespace miauto