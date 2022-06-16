#pragma once

#include "event_base.h"
#include "state_link_base.h"
#include "state_machine_base.h"

namespace miauto {
namespace function_management {

enum StateEunm { NOT_READY, NORMAL_ACTIVE, FAULT, HOLD };

using EventBaseConstVectorRef = std::vector<EventBase> const &;

template <typename TSE> class StateMachineBase;

template <typename TSE> class StateBase {
public:
  StateBase(StateMachineBase<TSE> *state_machine, TSE state_enum)
      : state_machine_(state_machine), state_enum_(state_enum){};

  virtual ~StateBase() = default;

  virtual void InitPriorityLinks() = 0;

  virtual void Entry() = 0;

  virtual void During() = 0;

  virtual void Exit() = 0;

  virtual void CallBack(EventBase const &event) = 0;

  void React(EventBaseConstVectorRef events) {
    for (int32_t i = 0; i < GetPriorityLinks()->size(); i++) {
      StateLinkBase<TSE> &link = GetPriorityLinks()->at(i);
      if (link.condition_function()(events)) {
        if (link.transit_condition_function() != nullptr)
          RequestTransit<std::function<void(void)>, std::function<bool(void)>>(
              link.target_state_enum(), link.action_function(),
              link.transit_condition_function());
        else if (link.action_function() != nullptr)
          RequestTransit<std::function<void(void)>>(link.target_state_enum(),
                                                    link.action_function());
        else
          RequestTransit(link.target_state_enum());

        return;
      }
    }
  }

  void RequestTransit(TSE state) { state_machine_->Transit(state); }

  template <typename F> void RequestTransit(TSE state, F &action_function) {
    state_machine_->Transit(state, action_function);
  }

  template <typename F, typename C>
  void RequestTransit(TSE state, F &action_function, C &condition_function) {
    state_machine_->Transit(state, action_function, condition_function);
  }

  void RequestDispatch(EventBase const &event) {
    state_machine_->Dispatch(event);
  }

  TSE GetStateEnum() { return state_enum_; }

  StateMachineBase<TSE> *GetStateMachinePtr() { return state_machine_; }

  void AddPriorityLink(
      std::function<bool(EventBaseConstVectorRef)> condition_function,
      TSE target_state_enum) {
    StateLinkBase<TSE> func_event_pair(condition_function, target_state_enum);
    priority_links_.emplace_back(func_event_pair);
  }

  void AddPriorityLink(
      std::function<bool(EventBaseConstVectorRef)> condition_function,
      TSE target_state_enum, std::function<void(void)> transit_function) {
    StateLinkBase<TSE> func_event_pair(condition_function, target_state_enum,
                                       transit_function);
    priority_links_.emplace_back(func_event_pair);
  }

  void AddPriorityLink(
      std::function<bool(EventBaseConstVectorRef)> condition_function,
      TSE target_state_enum, std::function<void(void)> transit_function,
      std::function<bool(void)> transit_condition_function) {
    StateLinkBase<TSE> func_event_pair(condition_function, target_state_enum,
                                       transit_function,
                                       transit_condition_function);
    priority_links_.emplace_back(func_event_pair);
  }

  std::vector<StateLinkBase<TSE>> *GetPriorityLinks() {
    return &priority_links_;
  }

  StateMachineBase<TSE> *state_machine() { return state_machine_; }

private:
  StateMachineBase<TSE> *state_machine_;
  std::vector<StateLinkBase<TSE>> priority_links_;
  TSE state_enum_;
};
} // namespace function_management
} // namespace miauto
