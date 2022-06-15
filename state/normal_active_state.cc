#include "normal_active_state.h"

namespace miauto {
namespace function_management {

void NormalActiveState::InitPriorityLinks() {

  std::function<bool(EventBaseConstVectorRef)> access_normal_active_to_hold =
      std::bind(&NormalActiveState::AssessNormalActiveToHold, this,
                std::placeholders::_1);

  AddPriorityLink(access_normal_active_to_hold, StateEunm::HOLD);
}

void NormalActiveState::Entry() {
  time_ = 0;
  std::cout << "Normal Active Entry: " << time_ << std::endl;
};

void NormalActiveState::During() {
  time_++;
  std::cout << "Normal Active Exec: " << time_ << std::endl;
};

void NormalActiveState::Exit() {
  time_ = 0;
  std::cout << "Normal Active  Exit: " << time_ << std::endl;
};

void NormalActiveState::CallBack(EventBase const &event){
    // here can receive additional signal event.
};

bool NormalActiveState::AssessNormalActiveToHold(
    EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (EventEnum(event->type_enum_id()) == EventEnum::BRAKE_EVENT) {
      std::cout << "NormalActive To Hold: " << time_ << std::endl;
      return true;
    }
  }
  return false;
}

} // namespace function_management
} // namespace miauto