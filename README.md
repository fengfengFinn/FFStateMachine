# First Fast State Machine

1. Matlab State Machine Style.

2. This state machine no need to create any map. only need to define every state and corresponding links, then add them to your state machine.

3. Based on pointer and enum.

4. Provide two different message pattern, namely matlab style signal event pattern (react()) and normal event pattern (callback()).

5. Clear Class Difinition.
    - event (which means event or signals (matlab way))
    - state machine (center handler)
    - state (which contains links)
    - state link (the line connects two states, which also contains condition judge methods)


## Architecture
### Main interface
- base/event_base.h
- base/state_base.h
- base/state_link_base.h
- base/state_machine_base.h

### One Factory Util
- common/factory.h
