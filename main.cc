#include "./event/brake_event.h"
#include "./event/error_event.h"
#include "./event/event_enum.h"
#include "./event/func_enable_event.h"
#include "./event/pedal_step_on_event.h"
#include "ff_state_machine.cc"
#include "ff_state_machine.h"
#include <iostream>
#include <memory>

int main() {
  using miauto::function_management::BrakeEvent;
  using miauto::function_management::ErrorEvent;
  using miauto::function_management::EventBase;
  using miauto::function_management::EventEnum;
  using miauto::function_management::FFStateBase;
  using miauto::function_management::FuncEnableEvent;
  using miauto::function_management::PedalStepOnEvent;

  std::cout << "Welcome Finn State machine Demo! Hope this will help you."
            << time << std::endl;
  std::unique_ptr<FFStateBase> state_machine = std::make_unique<FFStateBase>();

  state_machine->Init();

  int time = 0;

  while (true) {
    state_machine->Update();

    if (time >= 5) {
      std::vector<EventBase> events;
      events.emplace_back(FuncEnableEvent(EventEnum::FUNC_ENABLE_EVENT));
      if (time == 10)
        events.emplace_back(ErrorEvent(EventEnum::ERROR_EVENT));
      if (time == 15)
        events.emplace_back(BrakeEvent(EventEnum::BRAKE_EVENT, 10));
      if (time == 20)
        events.emplace_back(PedalStepOnEvent(EventEnum::PEDAL_STEP_ON_EVENT));
      if (time == 25)
        events.emplace_back(ErrorEvent(EventEnum::ERROR_EVENT));
      state_machine->Dispatch(events);
    }
    time++;

    if (time == 30) {

      std::cout << "Demo Over, Thanks!" << time << std::endl;
      return 1;
    }
  }

  return 0;
}
