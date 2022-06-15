#pragma once
#include "../ff_state_machine.h"

namespace miauto {
namespace function_management {

class NotReadyState : public StateBase<StateEunm> {
private:
  int time_ = -1;

public:
  NotReadyState(FFStateBase *state_machine, StateEunm state_enum)
      : StateBase(state_machine, state_enum) {
    InitPriorityLinks();
  };

  ~NotReadyState() = default;

  virtual void InitPriorityLinks() override;

  virtual void Entry() override;

  virtual void During() override;

  virtual void Exit() override;

  FFStateBase *ff_state_machine() {
    return dynamic_cast<FFStateBase *>(state_machine());
  }

  virtual void CallBack(EventBase const &event){};

  bool AssessNotReadyToFault(EventBaseConstVectorRef events);

  bool AssessNotReadyToNormalActive(EventBaseConstVectorRef events);
};

} // namespace function_management
} // namespace miauto