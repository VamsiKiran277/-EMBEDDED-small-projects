
## Project: ZX-8080 Embedded Thermal Controller & LED Toggler

This repository contains a bare-metal C implementation for the **ZX-8080**, a custom 32-bit RISC-V based microcontroller. The project demonstrates low-level hardware abstraction by interfacing with an onboard 12-bit SAR ADC for thermal monitoring and utilizing a General Purpose Timer for precise LED toggling. Furthermore, the entire hardware environment is successfully virtualized and tested using the Renode simulation framework.

## Technology Stack
* **Target Hardware:** ZX-8080 (RISC-V 32-bit Architecture)
* **Clock Speed:** 80 MHz System Frequency
* **Language:** C (Bare-Metal)
* **Toolchain:** RISC-V GCC (`riscv64-unknown-elf-gcc`)
* **Simulation:** Renode (Antmicro)
* **Key Peripherals:** * **Timer 1:** Used for frequency division and event timing.
    * **12-bit ADC:** Used for temperature sensor data acquisition.
    * **GPIO:** Used for status indication (Thermal Alarm and Blink).

## System Logic & Implementation

The application performs two concurrent tasks within a super-loop:

### 1. Precision Timing (LED Toggle)
To achieve a human-readable **0.5s blink rate** from an **80 MHz** system clock, I implemented a two-stage clock division:
* **Prescaler (PSC):** Set to `7999`. This reduces the timer clock to $10\text{ kHz}$.
    $$f_{clk} = \frac{80,000,000}{7999 + 1} = 10,000\text{ Hz}$$
* **Auto-Reload Register (ARR):** Set to `4999`. The timer counts 5000 ticks before setting the Update Interrupt Flag (UIF).
    $$Delay = \frac{(PSC + 1) \times (ARR + 1)}{f_{sys}} = \frac{8000 \times 5000}{80,000,000} = 0.5\text{s}$$

### 2. Thermal Monitoring (ADC Polling)
The code interacts with a 12-bit SAR ADC (Scale: 0–4095).
* **Trigger:** Hardware conversion is initiated by software.
* **Polling:** The CPU waits for the `START_CONV` bit to be cleared by hardware, ensuring data integrity.
* **Hysteresis Logic:** * If `current_temp > 3000`: Activate Alarm (Pin 0 HIGH).
    * If `current_temp < 1500`: Deactivate Alarm (Pin 0 LOW).

---

## Bare-Metal Compilation & Linker Script
Because this project runs without an Operating System, the standard C library is excluded using the `-nostdlib` flag. To tell the compiler exactly how to map the code to the ZX-8080's physical memory, a custom linker script (`link.ld`) was authored.

* **Flash Memory (`0x0`):** Mapped for the executable code (`.text` sections) and read-only data (`.rodata`).
* **SRAM (`0x20000000`):** Mapped for initialized variables (`.data`) and uninitialized variables (`.bss`).
The resulting output is a raw `.elf` (Executable and Linkable Format) file that can be loaded directly onto the silicon.

---

## Virtual Hardware Simulation (Renode)
To test the firmware without physical silicon, the ZX-8080 environment was built from scratch using **Renode**. 

* **Platform Definition (`zx8080.repl`):** Defines the memory map, attaching the CPU, Flash, SRAM, and Memory-Mapped I/O (MMIO) to the system bus at their exact datasheet addresses.
* **Hardware Injection (`gpio.py` & `timer.py`):** Custom Python peripherals act as the virtual silicon. They intercept the CPU's memory reads/writes to inject mock ADC thermal values and assert Timer Interrupt flags in real-time, allowing the C code to process logic identically to physical hardware.
* **Execution Script (`zx8080.resc`):** Initializes the machine, loads the `.elf` file, sets the Stack Pointer (`SP`) and Program Counter (`PC`), and hooks into the bus to log GPIO outputs directly to the console.

---

## Key Learnings

### Hardware Abstraction via Structs
Instead of using raw pointer arithmetic for every register access, I utilized **Memory-Mapped Structures**. This approach maps a C `struct` directly to the peripheral's register offsets, making the code more readable and maintainable.

### The `volatile` Keyword is Critical
A major debugging breakthrough involved compiler optimization. Without the `volatile` keyword on the hardware structs, the RISC-V GCC compiler optimized away the hardware polling loops (assuming the memory never changed). Adding `volatile` forced the CPU to fetch fresh data from the memory bus on every cycle, allowing the software to successfully synchronize with the hardware.

### Clock Management
I learned how to manipulate high-frequency system clocks into usable time domains. Understanding the relationship between the **Prescaler** and **Auto-Reload** is fundamental for PWM, communication baud rates, and standard delays.

### Register-Level Synchronization
By implementing a **Polling Method**, I practiced how software must synchronize with asynchronous hardware events—checking status flags (like the `UIF` bit in `TIM_STAT`) and clearing them manually to acknowledge the event.

---

## Code Structure
* `main.c`: Primary logic including clock calculations and the main control loop.
* `main.h`: Definition of memory-mapped structures (e.g., `SYS_CNTL_t`, `ADX_CNF_t`) and volatile pointer definitions.
* `link.ld`: Linker script defining the memory layout for Flash and RAM.
* `zx8080.repl`: Renode platform description file building the virtual hardware.
* `zx8080.resc`: Renode startup script.
* `gpio.py` / `timer.py`: Python scripts defining the behavior of the virtual peripherals.
* `ZX8080_Microcontroller_Datasheet.pdf` : Datasheet for Reference
 
---

## How to Run the Simulation

**1. Compile the Firmware:**
Ensure you have the RISC-V GNU Toolchain installed. Run the following command to generate the executable:
```bash
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -nostdlib -T link.ld main.c -o zx8080_project.elf
```

**2. Launch Renode:**
Open your terminal and start the Renode framework:
```bash
renode
```

**3. Run the Simulation Script:**
In the Renode monitor console, load and start the environment:
```bash
s @zx8080.resc
```
*You should immediately see console outputs showing the GPIO registers toggling (`0x1L` for the thermal alarm and `0x20L` for the LED blink), proving the firmware is correctly driving the virtual hardware!*

***
