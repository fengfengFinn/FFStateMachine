#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "state_base.h"

namespace miauto {
namespace function_management {

template <typename TSE> class StateMachineBase {
public:
  StateMachineBase() = default;

  virtual ~StateMachineBase() = default;

  virtual void Init() = 0;

  void SetInitState(TSE init_state_enum) {
    typename std::unordered_map<TSE, std::unique_ptr<StateBase<TSE>>>::iterator
        iter_map = state_map_.find(init_state_enum);
    if (iter_map != state_map_.end()) {
      cur_state_ptr_ = iter_map->second.get();
      cur_state_enum_ = iter_map->first;
      cur_state_ptr_->Entry();
    }
  }

  void Update() { cur_state_ptr_->During(); }

  TSE GetCurStateEnum() { return cur_state_enum_; };

  void Transit(TSE target_state_enum) {
    typename std::unordered_map<TSE, std::unique_ptr<StateBase<TSE>>>::iterator
        iter_map = state_map_.find(target_state_enum);

    if (iter_map != state_map_.end()) {
      cur_state_ptr_->Exit();
      cur_state_ptr_ = iter_map->second.get();
      cur_state_enum_ = iter_map->first;
      cur_state_ptr_->Entry();
    }
  }

  template <typename F>
  void Transit(TSE target_state_enum, F &action_function) {
    typename std::unordered_map<TSE, std::unique_ptr<StateBase<TSE>>>::iterator
        iter_map = state_map_.find(target_state_enum);

    if (iter_map != state_map_.end()) {
      cur_state_ptr_->Exit();
      action_function();
      cur_state_ptr_ = iter_map->second.get();
      cur_state_enum_ = iter_map->first;
      cur_state_ptr_->Entry();
    }
  }

  template <typename F, typename C>
  void Transit(TSE target_state_enum, F &action_function,
               C &condition_function) {
    if (condition_function()) {
      Transit<F>(target_state_enum, action_function);
    }
  }

  void AddState(TSE state_enum, std::unique_ptr<StateBase<TSE>> state_ptr) {
    state_map_[state_enum] = std::move(state_ptr);
  }

  void Dispatch(EventBase const &event) {
    if (cur_state_ptr_ != nullptr)
      cur_state_ptr_->CallBack(event);
  }

  void Dispatch(EventBaseConstVectorRef events) {
    if (cur_state_ptr_ != nullptr)
      cur_state_ptr_->React(events);
  }

private:
  typename std::unordered_map<TSE, std::unique_ptr<StateBase<TSE>>> state_map_;

  StateBase<TSE> *cur_state_ptr_;

  TSE cur_state_enum_;
};
} // namespace function_management

} // namespace miauto
