## Project: ZX-8080 Embedded Thermal Controller & LED Toggler

This repository contains a bare-metal C implementation for the **ZX-8080**, a 32-bit RISC-V based microcontroller. The project demonstrates low-level hardware abstraction by interfacing with an onboard 12-bit SAR ADC for thermal monitoring and utilizing a General Purpose Timer for precise LED toggling.

## Technology Stack
* **Target Hardware:** ZX-8080 (RISC-V 32-bit Architecture)
* **Clock Speed:** 80 MHz System Frequency
* **Language:** C (Bare-Metal)
* **Toolchain:** RISC-V GCC / Memory-Mapped I/O (MMIO)
* **Key Peripherals:** * **Timer 1:** Used for frequency division and event timing.
    * **12-bit ADC:** Used for temperature sensor data acquisition.
    * **GPIO:** Used for status indication (Thermal Alarm and Blink).

##  System Logic & Implementation

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

## Key Learnings

### Hardware Abstraction via Structs
Instead of using raw pointer arithmetic for every register access, I utilized **Memory-Mapped Structures**. This approach maps a C `struct` directly to the peripheral's register offsets, making the code more readable and maintainable.

### Clock Management
I learned how to manipulate high-frequency system clocks into usable time domains. Understanding the relationship between the **Prescaler** and **Auto-Reload** is fundamental for PWM, communication baud rates, and standard delays.

### Register-Level Synchronization
By implementing a **Polling Method**, I practiced how software must synchronize with asynchronous hardware events—checking status flags (like the `UIF` bit in `TIM_STAT`) and clearing them manually to acknowledge the event.

---

##  Code Structure
* `main.c`: Primary logic including clock calculations and the main control loop.
* `main.h`: Definition of memory-mapped structures (e.g., `SYS_CNTL_t`, `ADX_CNF_t`) and volatile pointer definitions.
* **ZX-8080 Datasheet**: Reference for base addresses (`0x40001000`, `0x40002000`) and bit-field definitions.
