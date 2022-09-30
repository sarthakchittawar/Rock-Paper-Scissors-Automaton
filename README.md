# Rock Paper Scissors using Automata Theory
Implementation of a Rock Paper Scissors Automaton, which would beat opponent as many times as possible.

## Basic Logic:
    I have made ‘n’ DFAs, one for each input state(opponent state).
    Now, let’s say input state is ‘x’, so the program will keep redirecting
    to the DFA which beats the next state of input state, in simple words,
    be one step ahead almost always.

## Notes to evaluator:
I will have a total of n^2 states in my FSM if there are n states in the input file. \
I have taken care of TLEs while iterating through my output, by breaking the while loop after m*m i.e. total possible win states. \
To an extent, I have also taken care of infinite/semi infinite loss loops. But the program can be broken.

## Notations & Variables -
1. `in_states`: vector of input states
2. `in_transitions`: vector of input transitions
3. `out_states`: vector of output states
4. `out_transitions`: vector of output transitions
5. `rps_in`: Index of in_transitions depending on my prev state
6. `rps_out`: Index of out_transitions depending on opp’s prev state

The `evalscript_auto.zip` file has all necessary files for automated checking of code.
  P.S. It is not made by me, but by my TAs of this course. Shoutout to them.
