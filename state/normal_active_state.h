#pragma once
#include "../base/state_base.h"
#include "../base/state_machine_base.h"
#include "../event/brake_event.h"
#include "active_domain_state.h"
namespace miauto {
namespace function_management {

class ACCNormalActiveState : public ActiveDomainState {
private:
  int time_ = -1;

public:
  ACCNormalActiveState(StateMachineBase<ACCState> *state_machine,
                       ACCState state_enum)
      : ActiveDomainState(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~ACCNormalActiveState() = default;

  virtual void InitPriorityLinks(){};

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event) override;

  void BrakeEventHandler(BrakeEvent const &event);
};

} // namespace function_management
} // namespace miauto