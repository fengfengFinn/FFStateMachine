#pragma once
#include "../acc_state_machine.h"
#include "../base/state_base.h"
#include "../base/state_machine_base.h"

namespace miauto {
namespace function_management {

class ACCNotReadyState
    : public StateBase<StateMachineBase<ACCState>, ACCState> {
private:
  int time_ = -1;
  ACCStateMachine *acc_state_machine_;

public:
  ACCNotReadyState(StateMachineBase<ACCState> *state_machine,
                   ACCState state_enum)
      : StateBase(state_machine, state_enum),
        acc_state_machine_(dynamic_cast<ACCStateMachine *>(state_machine)) {
    InitPriorityLinks();
  };

  ~ACCNotReadyState() = default;

  virtual void InitPriorityLinks() override;

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  virtual void CallBack(EventBase const &event){};

  bool AssessNotReadyToFault(EventBaseConstVectorRef events);

  bool AssessNotReadyToNormalActive(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto