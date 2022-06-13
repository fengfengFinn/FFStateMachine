#include "fault_state.h"
#include "../event/acc_event_enum.h"
namespace miauto {
namespace function_management {

void ACCFaultState::InitPriorityLinks() {
  std::function<bool(EventBaseConstVectorRef)> access_fault_to_notready =
      std::bind(&ACCFaultState::AssessFaultToNotReady, this,
                std::placeholders::_1);

  AddPriorityLink(access_fault_to_notready, ACCState::NOT_READY);
};

void ACCFaultState::Entry() {
  time_ = 0;
  std::cout << "Fault Entry: " << time_ << std::endl;
};

void ACCFaultState::During() {
  std::cout << "Fault Exec: " << time_ << std::endl;
  time_++;
};

void ACCFaultState::Exit() {
  time_ = 0;
  std::cout << "Fault  Exit: " << time_ << std::endl;
};

bool ACCFaultState::AssessFaultToNotReady(EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (ACCEventEnum(event->type_enum_id()) == ACCEventEnum::ERROR_EVENT) {
      return false;
    }
  }
  return true;
};

} // namespace function_management
} // namespace miauto