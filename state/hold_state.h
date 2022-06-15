#pragma once
#include "../acc_state_machine.h"
#include "active_domain_state.h"
namespace miauto {
namespace function_management {

class ACCHoldState : public ActiveDomainState {
private:
  int time_ = -2;

public:
  ACCHoldState(ACCStateMachine *state_machine, ACCState state_enum)
      : ActiveDomainState(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~ACCHoldState() = default;

  virtual void InitPriorityLinks() override;

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event){};

  bool AssessHoldToNormalActive(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto