#pragma once
#include "../event/brake_event.h"
#include "../ff_state_machine.h"
#include "active_domain_state.h"
namespace miauto {
namespace function_management {

class FaultState : public ActiveDomainState {
private:
  int time_ = -2;

public:
  FaultState(FFStateBase *state_machine, StateEunm state_enum)
      : ActiveDomainState(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~FaultState() = default;

  virtual void InitPriorityLinks() override;

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event){};

  bool AssessFaultToNotReady(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto