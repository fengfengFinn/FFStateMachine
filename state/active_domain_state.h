#pragma once
#include "../base/state_base.h"
#include "../base/state_machine_base.h"
#include "../event/acc_event_enum.h"
namespace miauto {
namespace function_management {

class ActiveDomainState
    : public StateBase<StateMachineBase<ACCState>, ACCState> {
public:
  ActiveDomainState(StateMachineBase<ACCState> *state_machine,
                    ACCState state_enum)
      : StateBase(state_machine, state_enum) {
    InitActiveDomainPriorityLinks();
  };

  virtual ~ActiveDomainState() = default;

  virtual void InitPriorityLinks() = 0;

  virtual void Entry() = 0;

  virtual void During() = 0;

  virtual void Exit() = 0;

  virtual void CallBack(EventBase const &event) = 0;

  void InitActiveDomainPriorityLinks() {
    std::function<bool(EventBaseConstVectorRef)> access_active_to_fault =
        std::bind(&ActiveDomainState::AssessActiveToFault, this,
                  std::placeholders::_1);

    AddPriorityLink(access_active_to_fault, ACCState::FAULT);
  };

  bool AssessActiveToFault(EventBaseConstVectorRef events) {
    for (std::vector<EventBase>::const_iterator event = events.begin();
         event != events.end(); event++) {
      if (ACCEventEnum(event->type_enum_id()) == ACCEventEnum::ERROR_EVENT) {
        std::cout << "Active to Fault" << std::endl;
        return true;
      }
    }
  };
};

} // namespace function_management
} // namespace miauto