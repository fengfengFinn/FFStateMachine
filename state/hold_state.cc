#include "hold_state.h"

namespace miauto {
namespace function_management {

void HoldState::InitPriorityLinks() {
  std::function<bool(EventBaseConstVectorRef)> access_hold_to_normal_active =
      std::bind(&HoldState::AssessHoldToNormalActive, this,
                std::placeholders::_1);

  AddPriorityLink(access_hold_to_normal_active, StateEunm::NORMAL_ACTIVE);
};

void HoldState::Entry() {
  time_ = 0;
  std::cout << "Hold Entry: " << time_ << std::endl;
};

void HoldState::During() {
  time_++;
  std::cout << "Hold Exec: " << time_ << std::endl;
};

void HoldState::Exit() {
  time_ = 0;
  std::cout << "Hold  Exit: " << time_ << std::endl;
};

bool HoldState::AssessHoldToNormalActive(EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (EventEnum(event->type_enum_id()) == EventEnum::PEDAL_STEP_ON_EVENT) {
      return true;
    }
  }
  return false;
};

} // namespace function_management
} // namespace miauto