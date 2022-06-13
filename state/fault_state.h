#pragma once
#include "../base/state_base.h"
#include "../base/state_machine_base.h"
#include "../event/brake_event.h"
#include "active_domain_state.h"
namespace miauto {
namespace function_management {

class ACCFaultState : public ActiveDomainState {
private:
  int time_ = -2;

public:
  ACCFaultState(StateMachineBase<ACCState> *state_machine, ACCState state_enum)
      : ActiveDomainState(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~ACCFaultState() = default;

  virtual void InitPriorityLinks() override;

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event){};

  bool AssessFaultToNotReady(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto