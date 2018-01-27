# MSP430-Lunchpad
The purpose of this repository is to present several projects built on the MSP430 Launchpad. 
All projects were built using Code Composer Studio and the MSP430G2553 processor. 
The following is a list of projects with a short description. Source code for each is located in source/ccs/project.

# Project Listing
  ---------------

- msp430_blink1:  Initializes leds, button as interrupt, spi, and uart interface.  Implements a very simple command handler for uart data.

- msp430_qpn:  A simple project that uses QP Nano.

- msp430_Code Oscillator: For practice sending CW using a straight key, sideswiper, or bug. Ground Pin P2.0 to generate a 580 hz square wave out of Pin P2.1. Green and red leds alternate on key-up and -down.

- msp430_task: A tasking project that makes use of a single timer and a while loop to create a simple tasker. The timer is configured to interrupt every 1ms, which runs the tasker. The task files, task.c/.h are portable and can be reused in other applications. See msp430_tasksigs for an extension on this project, that adds ability for one task to send a message to another task.
