STM32F4 Bare-Metal LED Toggle (Bit-Field & SIL Validation)

A low-level firmware implementation for the STM32F407 (ARM Cortex-M4) that demonstrates peripheral control via direct register manipulation. This project bypasses standard HAL/LL libraries to interface directly with the AHB1 bus matrix using C bit-fields.
🛠 Technical Highlights

    Memory-Mapped I/O (MMIO): Manually mapped the RCC and GPIOD base addresses (Base: 0x40020C00).

    C Bit-Field Structures: Utilized custom struct definitions to map hardware registers, ensuring type-safe access to individual bits.

    Software-in-the-Loop (SIL) Testing: Automated hardware verification using Renode to validate register-level behavior via memory-access tracing.



## Project Structure
```text
.
├── Src/                # Main application logic (main.c)
├── Inc/                # Bit-field register definitions
├── Startup/            # Startup assembly and Vector Table
├── Simulation/         
│   ├── stm32_blink.resc  # Renode verification script
│   └── blink.elf         # Target binary for simulation
├── verification.log    # Auto-generated simulation trace
└── README.md           # Project documentation


How to Run and Verify - 
This project includes a pre-configured Renode simulation environment. You can verify the firmware logic (register writes, timing, and pin toggling) without physical hardware.

1. Prerequisites
    Install Renode (Portable or System version).
    Ensure you are in the project root directory.
    
2. Execution Command
Run the following command in your terminal to launch the headless simulation and pipe the hardware logs directly to a verification file:

    renode --plain --hide-monitor --execute "include @Simulation/stm32_blink.resc" 2>&1 | tee verification.log
    
3. Verification & Output
Let the simulation run for 30–60 seconds, then press Ctrl+C. Open the newly created verification.log in the root directory.
What to look for in verification.log:
The trace proves the software is successfully communicating with the hardware registers:
    Mode Configuration: WriteUInt32 to 0x0 (Mode), value 0x1000000 (Sets Pin 12 to Output).
    LED ON: WriteUInt32 to 0x14 (OutputData), value 0x1000 (Hex 0x1000 = Bit 12 HIGH).
    LED OFF: WriteUInt32 to 0x14 (OutputData), value 0x0 (Pin 12 LOW).
    
Implementation Details
Register Mapping

Instead of manual bit-shifting (e.g., *(GPIO + OFFSET) |= (1 << 12)), I utilized structured bit-fields. This increases code readability and reduces the "magic number" overhead common in bare-metal development.

Simulation Logic

The simulation uses a Watchpoint Hook on the memory address 0x40020C14 (GPIOD_ODR). Every time the firmware updates the LED state, Renode captures the Program Counter (PC) and the value written, providing a cycle-accurate audit trail of the firmware's execution.
