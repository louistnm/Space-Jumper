//
// Created by Louis Tennier on 2/13/26.
//

#include "fsm.h"

FSM::FSM(Transitions transitions, States states, StateType start)
    : transitions{transitions}, states{states}, current_state_type{start}, current_state{states[current_state_type]}{}

FSM::~FSM() {
    for (auto [_, state] : states) {
        delete state;
    }
}

void FSM::transition(Transition t, World& world, GameObject& obj) {
    auto itr = transitions.find({current_state_type, t}); //find transition corresponding to the current state type returning an itr
    if (itr != transitions.end()) {
        current_state->on_exit(world, obj);

        current_state_type = itr->second;
        current_state = states[current_state_type];

        current_state->on_enter(world, obj);
    }

}