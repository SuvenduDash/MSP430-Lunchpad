Project Listing
---------------


- msp430_blink1:  Initializes leds, button as interrupt, spi, and uart interface.  Implements a very simple command handler for uart data.

- msp430_qpn:  A simple project that uses QP Nano.

- msp430_Code Oscillator: For practice sending CW using a straight key, sideswiper, or bug. Ground Pin P2.0 to generate a 580 hz square wave out of Pin P2.1. Green and red leds alternate on key-up and -down.

- msp430_task: A tasking project that makes use of a single timer and a while loop to create a simple tasker. The timer is configured to interrupt every 1ms, which runs the tasker. The task files, task.c/.h are portable and can be reused in other applications. See msp430_tasksigs for an extension on this project, that adds ability for one task to send a message to another task.

- msp_430_MooreFSM: A project that uses a simple Moore finite state machine. The project contains 4 states and an input value that takes a value from 0 to 3. Toggle the state by pressing the user button. State pattern: input 0 - state0, input 1 - state 1.. etc. Each state runs the cooresponding state function. State_t defintion also contains an entry function pointer to run on trnasition from one state to the next.
