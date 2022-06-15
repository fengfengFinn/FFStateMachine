#pragma once
#include "../ff_state_machine.h"

#include "active_domain_state.h"
namespace miauto {
namespace function_management {

class NormalActiveState : public ActiveDomainState {
private:
  int time_ = -1;

public:
  NormalActiveState(FFStateBase *state_machine, StateEunm state_enum)
      : ActiveDomainState(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~NormalActiveState() = default;

  virtual void InitPriorityLinks();

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event) override;

  bool AssessNormalActiveToHold(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto