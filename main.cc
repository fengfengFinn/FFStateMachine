#include "./event/acc_event_enum.h"
#include "./event/brake_event.h"
#include "./event/error_event.h"
#include "acc_state_machine.cc"
#include "acc_state_machine.h"
#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<miauto::function_management::ACCStateMachine>
      acc_state_machine =
          std::make_unique<miauto::function_management::ACCStateMachine>();
  acc_state_machine->Init();

  int time = 0;
  while (true) {
    acc_state_machine->Update();

    if (time == 5 || time == 10) {
      std::vector<miauto::function_management::EventBase> events;
      events.emplace_back(miauto::function_management::BrakeEvent(
          miauto::function_management::ACCEventEnum::BRAKE_EVENT, 2));
      if (time != 20)
        events.emplace_back(miauto::function_management::ErrorEvent(
            miauto::function_management::ACCEventEnum::ERROR_EVENT));
      acc_state_machine->Dispatch(events);
    }
    time++;

    if (time == 20)
      return 1;
  }

  return 0;
}



