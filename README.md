# -EMBEDDED-small-projects

A collection of bare-metal firmware implementations focused on low-level hardware abstraction, register-level programming, and hardware-in-the-loop (HIL/SIL) simulation.

## Project Directory

### 1. [ZX-8080 Embedded Thermal Controller](./ZX_8080_MCU)
**Target:** RISC-V 32-bit (80MHz)
* **Core:** Precision timing and analog data acquisition using memory-mapped structures.
* **Tech:** SAR ADC polling, Timer-driven 0.5s blinking logic, and thermal hysteresis control.
* **Highlight:** Manual clock division calculations ($f_{sys}$ to $f_{clk}$) for human-readable event timing.

### 2. [STM32F4 Bare-Metal LED Toggle](./LED_TOGGLE_BITFIELD)
**Target:** ARM Cortex-M4 (STM32F407)
* **Core:** High-performance peripheral control via direct bit-field manipulation (AHB1 Bus).
* **Tech:** C Bit-field structures for type-safe register access, Renode SIL validation.
* **Validation:** Automated memory-access tracing to audit GPIO register writes (ODR/MODER) without physical hardware.

---

## 🛠 Skills & Tools
* **Languages:** Bare-Metal C, RISC-V/ARM Assembly (Startup code).
* **Hardware Knowledge:** MMIO, Clock Trees, ADC SAR logic, Interrupt Handling, GPIO Multiplexing.
* **Simulation & Toolchains:** Renode (SIL), GCC Toolchains (arm-none-eabi / riscv64-unknown-elf), STM32CubeIDE.

##  How to Navigate
Each folder contains its own specialized documentation, source code (`/Src`), and verification logs demonstrating hardware-software synchronization. 
