#include "normal_active_state.h"
#include "../event/acc_event_enum.h"
namespace miauto {
namespace function_management {

void ACCNormalActiveState::Entry() {
  time_ = 0;
  std::cout << "Normal Active Entry: " << time_ << std::endl;
};

void ACCNormalActiveState::During() {
  std::cout << "Normal Active Exec: " << time_ << std::endl;
  time_++;
};

void ACCNormalActiveState::Exit() {
  time_ = 0;
  std::cout << "Normal Active  Exit: " << time_ << std::endl;
};

void ACCNormalActiveState::CallBack(EventBase const &event) {
  if (ACCEventEnum(event.type_enum_id()) == ACCEventEnum::BRAKE_EVENT) {
    BrakeEventHandler(dynamic_cast<BrakeEvent const &>(event));
  }
};

void ACCNormalActiveState::BrakeEventHandler(BrakeEvent const &event) {
  std::cout << "Normal Active trigglered: " << event.brake_signal_value
            << std::endl;
};

} // namespace function_management
} // namespace miauto