#include "not_ready_state.h"

namespace miauto {
namespace function_management {

void ACCNotReadyState::InitPriorityLinks() {
  // Notice: the sequence is important here, which means priority.
  // first link
  std::function<bool(EventBaseConstVectorRef)> access_not_ready_to_fault =
      std::bind(&ACCNotReadyState::AssessNotReadyToFault, this,
                std::placeholders::_1);

  AddPriorityLink(access_not_ready_to_fault, ACCState::FAULT);

  // second link
  std::function<bool(EventBaseConstVectorRef)>
      access_not_ready_to_normal_active =
          std::bind(&ACCNotReadyState::AssessNotReadyToNormalActive, this,
                    std::placeholders::_1);

  std::function<void(void)> action([]() -> void {
    std::cout << "action between not_ready exit and normal_active enter"
              << std::endl;
  });

  AddPriorityLink(access_not_ready_to_normal_active, ACCState::NORMAL_ACTIVE,
                  action);
};

void ACCNotReadyState::Entry() {
  time_ = 0;
  std::cout << "Not Ready Entry: " << time_ << std::endl;
};

void ACCNotReadyState::During() {
  time_++;
  std::cout << "Not Ready Exec: " << acc_state_machine()->state_machine_data
            << ", time: " << time_ << std::endl;
};

void ACCNotReadyState::Exit() {
  time_ = 0;
  std::cout << "Not Ready Exit: " << time_ << std::endl;
};

bool ACCNotReadyState::AssessNotReadyToFault(EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (ACCEventEnum(event->type_enum_id()) == ACCEventEnum::ERROR_EVENT) {
      std::cout << "NotReady To Fault: " << time_ << std::endl;
      return true;
    }
  }
  return false;
};

bool ACCNotReadyState::AssessNotReadyToNormalActive(
    EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (ACCEventEnum(event->type_enum_id()) ==
        ACCEventEnum::FUNC_ENABLE_EVENT) {
      std::cout << "NotReady To NormalActive: " << time_ << std::endl;
      return true;
    }
  }
  return false;
};

} // namespace function_management
} // namespace miauto