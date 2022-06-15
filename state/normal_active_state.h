#pragma once
#include "../acc_state_machine.h"

#include "active_domain_state.h"
namespace miauto {
namespace function_management {

class ACCNormalActiveState : public ActiveDomainState {
private:
  int time_ = -1;

public:
  ACCNormalActiveState(ACCStateMachine *state_machine, ACCState state_enum)
      : ActiveDomainState(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~ACCNormalActiveState() = default;

  virtual void InitPriorityLinks();

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event) override;

  bool AssessNormalActiveToHold(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto