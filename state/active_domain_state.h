#pragma once
#include "../acc_state_machine.h"
#include "../event/acc_event_enum.h"
namespace miauto {
namespace function_management {

class ActiveDomainState : public StateBase<ACCState> {
public:
  ActiveDomainState(ACCStateMachine *state_machine, ACCState state_enum)
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

    std::function<bool(EventBaseConstVectorRef)>
        access_normal_active_to_not_ready =
            std::bind(&ActiveDomainState::AssessActiveToNotReady, this,
                      std::placeholders::_1);

    AddPriorityLink(access_normal_active_to_not_ready, ACCState::NOT_READY);
  };

  bool AssessActiveToFault(EventBaseConstVectorRef events) {
    for (std::vector<EventBase>::const_iterator event = events.begin();
         event != events.end(); event++) {
      if (ACCEventEnum(event->type_enum_id()) == ACCEventEnum::ERROR_EVENT) {
        std::cout << "Active to Fault" << std::endl;
        return true;
      }
    }
    return false;
  };

  bool AssessActiveToNotReady(EventBaseConstVectorRef events) {
    for (std::vector<EventBase>::const_iterator event = events.begin();
         event != events.end(); event++) {
      if (ACCEventEnum(event->type_enum_id()) ==
          ACCEventEnum::FUNC_ENABLE_EVENT) {
        return false;
      }
    }

    std::cout << "Active To NotReady: " << std::endl;
    return true;
  }
};

} // namespace function_management
} // namespace miauto