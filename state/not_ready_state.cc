#include "not_ready_state.h"
#include "../event/acc_event_enum.h"
namespace miauto {
namespace function_management {

void ACCNotReadyState::InitPriorityLinks() {
  // Notice: the sequence is important here, which means priority.
  // first link
  // second link
  std::function<bool(EventBaseConstVectorRef)>
      access_not_ready_to_normal_active =
          std::bind(&ACCNotReadyState::AssessNotReadyToNormalActive, this,
                    std::placeholders::_1);
  std::function<void(void)> action(
      []() -> void { std::cout << "hello world action" << std::endl; });
  AddPriorityLink(access_not_ready_to_normal_active, ACCState::NORMAL_ACTIVE,
                  action);

  std::function<bool(EventBaseConstVectorRef)> access_not_ready_to_fault =
      std::bind(&ACCNotReadyState::AssessNotReadyToFault, this,
                std::placeholders::_1);

  AddPriorityLink(access_not_ready_to_fault, ACCState::FAULT);
};

void ACCNotReadyState::Entry() {
  time_ = 0;
  std::cout << "Not Ready Entry: " << time_ << std::endl;
};

void ACCNotReadyState::During() {
  std::cout << "Not Ready Exec: " << time_ << std::endl;
  time_++;
};

void ACCNotReadyState::Exit() {
  time_ = 0;
  std::cout << "Not Ready Exit: " << time_ << std::endl;
};

bool ACCNotReadyState::AssessNotReadyToFault(EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (ACCEventEnum(event->type_enum_id()) == ACCEventEnum::BRAKE_EVENT) {
      std::cout << "Not Ready AccessNotReadyToFault: " << time_ << std::endl;
      return true;
    }
  }
};

bool ACCNotReadyState::AssessNotReadyToNormalActive(
    EventBaseConstVectorRef events) {
  std::cout << "ddd" << std::endl;
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (ACCEventEnum(event->type_enum_id()) == ACCEventEnum::BRAKE_EVENT) {
      std::cout << "Not Ready AccessNotReadyToNormalActive: " << time_
                << std::endl;
      return true;
    }
  }
};

} // namespace function_management
} // namespace miauto