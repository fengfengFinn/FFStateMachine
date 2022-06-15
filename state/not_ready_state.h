#pragma once
#include "../acc_state_machine.h"

namespace miauto {
namespace function_management {

class ACCNotReadyState : public StateBase<ACCState> {
private:
  int time_ = -1;

public:
  ACCNotReadyState(ACCStateMachine *state_machine, ACCState state_enum)
      : StateBase(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~ACCNotReadyState() = default;

  virtual void InitPriorityLinks() override;

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  ACCStateMachine *acc_state_machine() {
    return dynamic_cast<ACCStateMachine *>(state_machine());
  }

  virtual void CallBack(EventBase const &event){};

  bool AssessNotReadyToFault(EventBaseConstVectorRef events);

  bool AssessNotReadyToNormalActive(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto