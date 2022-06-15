#include "fault_state.h"
#include "../event/event_enum.h"
namespace miauto {
namespace function_management {

void FaultState::InitPriorityLinks() {
  std::function<bool(EventBaseConstVectorRef)> access_fault_to_notready =
      std::bind(&FaultState::AssessFaultToNotReady, this,
                std::placeholders::_1);

  AddPriorityLink(access_fault_to_notready, StateEunm::NOT_READY);
};

void FaultState::Entry() {
  time_ = 0;
  std::cout << "Fault Entry: " << time_ << std::endl;
};

void FaultState::During() {
  time_++;
  std::cout << "Fault Exec: " << time_ << std::endl;
};

void FaultState::Exit() {
  time_ = 0;
  std::cout << "Fault  Exit: " << time_ << std::endl;
};

bool FaultState::AssessFaultToNotReady(EventBaseConstVectorRef events) {
  for (std::vector<EventBase>::const_iterator event = events.begin();
       event != events.end(); event++) {
    if (EventEnum(event->type_enum_id()) == EventEnum::ERROR_EVENT) {
      return false;
    }
  }
  return true;
};

} // namespace function_management
} // namespace miauto