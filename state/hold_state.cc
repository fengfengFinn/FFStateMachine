#include "hold_state.h"

namespace miauto {
namespace function_management {

void ACCHoldState::InitPriorityLinks() {
  std::function<bool(EventBaseConstVectorRef)> access_hold_to_normal_active =
      std::bind(&ACCHoldState::AssessHoldToNormalActive, this,
                std::placeholders::_1);

  AddPriorityLink(access_hold_to_normal_active, ACCState::NORMAL_ACTIVE);
};

void ACCHoldState::Entry() {
  time_ = 0;
  std::cout << "Hold Entry: " << time_ << std::endl;
};

void ACCHoldState::During() {
  time_++;
  std::cout << "Hold Exec: " << time_ << std::endl;
};

void ACCHoldState::Exit() {
  time_ = 0;
  std::cout << "Hold  Exit: " << time_ << std::endl;
};

bool ACCHoldState::AssessHoldToNormalActive(EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (ACCEventEnum(event->type_enum_id()) ==
        ACCEventEnum::PEDAL_STEP_ON_EVENT) {
      return true;
    }
  }
  return false;
};

} // namespace function_management
} // namespace miauto