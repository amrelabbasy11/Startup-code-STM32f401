# 🔌 The Journey of a Microcontroller: From Power-Up to Execution! 🔌

When a microcontroller powers up or resets, it doesn’t just jump straight into action. Instead, it meticulously follows a sequence of operations critical for system initialization. Let’s break down this fascinating process! 🛠️

1️⃣ Bootloader Execution
Upon power-up, some microcontrollers run a bootloader, either from a separate Boot ROM or embedded within the on-chip flash memory. This bootloader is the first line of defense, preparing the microcontroller to execute user programs with integrity and reliability.

2️⃣ Startup Code
Next comes the Reset Handler, part of the startup code. But what exactly is startup code?

Definition: A blend of C and assembly language, the startup code sets up the microcontroller environment before the main application kicks off. Its primary goals include:

System Initialization: Configuring essential parameters and memory areas.
🔍 Steps of Startup Code Execution:
The startup code follows these systematic steps:

Disable Global Interrupts: Prevents any interruptions during critical initialization to maintain consistency.

Initialize the Stack Pointer: Crucial for function calls and local variable storage.

Clear the .bss Section (SRAM): Uninitialized global and static variables are set to zero. This ensures a known state and prevents unpredictable behavior.

Why zero? This design choice ensures consistency and reliability in operation!

Copy the .data Section: Transfers initialized global and static variables from flash memory to their designated SRAM locations.

Initialize the Interrupt Vector Table (IVT): Essential for directing interrupts to the appropriate service routines.

Enable Global Interrupts: Once initialization is complete, interrupts are re-enabled, allowing the microcontroller to respond to events.

Call the main() Function: Finally, the user’s application begins execution! 
