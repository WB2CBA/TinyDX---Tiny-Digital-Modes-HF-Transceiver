# TinyDX---Tiny-Digital-Modes-HF-Transceiver
TinyDX is a minituarized two band HF Digital Modes QRPp Transceiver
![TinyDX 2](https://github.com/user-attachments/assets/3910f045-4386-422a-8d2e-bf21e2abec2e)


TinyDX in Action:

https://youtu.be/lumVageEz0A?si=CVWjLaan0oGv8utl

TinyDX V1.0, a miniature high-frequency (HF) digital modes transceiver optimized for FT8 and FT4 operation. Developed with an emphasis on extreme portability and USB power efficiency, TinyDX integrates a 

full-featured two-band transceiver within a 50 mm × 25 mm × 30 mm enclosure. The system achieves sub-watt transmission power, 

low current draw, and complete operation from standard 5V USB sources, eliminating the need for separate power supplies or computers in field operation. 

Low-power HF communication, often referred to as QRP operation, has long been valued for its efficiency, minimal equipment footprint, and capacity for long-distance communication under constrained power 

conditions. The TinyDX project was conceived to advance this philosophy, 

focusing on sub-watt (QRPp) operation while maintaining full compatibility with modern digital communication modes such as FT8 and FT4.

Earlier designs, such as the ADX UnO, achieved credit-card-sized form factors but still required external power sources and were less convenient for fully portable use. TinyDX was engineered to address 

these limitations, providing a smaller, USB-powered solution that could operate directly from a mobile phone or tablet.

2. Design Objectives

The primary goal of TinyDX was to achieve a highly compact, energy-efficient digital transceiver capable of operating on USB power. The design objectives included:

- USB-powered operation (5V DC input, ≤350 mA TX, ≤100 mA RX)

- Two-band operation (default 20 m and 15 m, configurable for 20/17/15/12/10 m)

- RF output of 700–900 mW

- Modular PCB architecture enabling vertical stacking within 2″ × 1″ × 1.2″ dimensions

- Minimal external dependencies (no dedicated PC or battery required)

3. System Architecture

TinyDX consists of three primary modules: the Main Controller, Receiver, and Transmitter modules. These modules are interconnected via 2×6 pin headers and sandwiched between two protective PCB plates to 

form a compact stack.

3.1 Main Controller Module

The Main Controller module integrates the CM108B audio codec and the Atmega328P/AU microcontroller. It provides USB input for both DC power and audio interface, along with band and mode selection 

switches. A 2×3 ISP header facilitates initial bootloader programming, after which firmware updates can be performed through a standard FTDI-style USB-to-TTL adapter. This configuration eliminates the 

need for an onboard USB-to-serial IC, saving both space and power.

3.2 Receiver Module

The Receiver module incorporates three main functional blocks:

- TX/RX switching (BSS123 MOSFET)

- 74ACT74 divider for generating I/Q phase signals

- 74CBT3253PWR and LM4562-based Quadrature Sampling Detector (QSD)

A 74ACT74 flip-flop divides the local oscillator frequency by four to generate 90° phase-shifted I and Q signals required by the QSD. The incoming signals are demodulated to baseband and routed to the 

CM108B audio codec. A 3.5 mm audio output connector provides direct access to the I/Q signals for testing or analysis.

3.3 Transmitter Module

The Transmitter module consists of:

- Power supply stage (5V to 3.3V LDO for SI5351 and 5V to 6.5V boost converter for RF PA)

- SI5351 PLL VCO

- 74ACT244-based RF power amplifier with 5-band low-pass filter

Despite the unconventional use of 6.5V on a 5V-rated IC, the 74ACT244 has demonstrated tolerance up to 7V within manufacturer limits, providing reliable output power up to 900 mW on 20 m and 700 mW on 15 

m bands. An optional miniature heatsink may be added for additional thermal stability.

4. Fabrication and Assembly

TinyDX employs 0603-sized SMD components to minimize footprint. Fabrication and component placement were outsourced to JLCPCB, utilizing their pick-and-place service with custom Gerber, BOM, and CPL 

files. The modular boards include the Main, TX, and RX modules, as well as top and bottom cover plates.

Assembly requires manual soldering of select through-hole components, including the FTDI connector, Mini-Circuits T2-613-KK81+ transformer, and SMA antenna connector. The stacked structure is assembled 

using 6 mm M3 spacers, bolts, and nuts.

5. Firmware and Programming

The Atmega328P/AU microcontroller operates with the Arduino Uno bootloader and firmware written in Arduino C. The bootloader can be uploaded using an external Arduino board as ISP, following Arduino’s 

standard programming guide. Once programmed, firmware uploads are conducted via USB-to-TTL adapter within the Arduino IDE.

Firmware and documentation are publicly available on the project’s GitHub repository: https://github.com/WB2CBA/TinyDX---Tiny-Digital-Modes-HF-Transceiver

6. Operation

TinyDX supports FT8 and FT4 modes on the configured bands. Operation involves connecting the device via USB to a host system (PC, iOS, or Android), selecting the correct audio input/output, and ensuring 

mode and band synchronization between the device and application.

For WSJT-X, the configuration should be set to 'Rig: None' and 'PTT: VOX', with the TinyDX recognized as 'USB Audio Device'. For mobile operation, compatible applications include IFTX for iOS and FT8TW 

for Android.

7. Conclusion

TinyDX V1.0 demonstrates the feasibility of a fully functional, sub-watt digital modes HF transceiver within a minimal physical envelope. Through innovative use of modular PCB stacking, efficient power 

management, and compact RF design, the system offers a practical solution for portable FT8 and FT4 operation without external power sources or computers. The design principles established in TinyDX 

provide a foundation for future ultra-compact, energy-efficient HF transceivers.

References
1.TinyDX GitHub Repository – https://github.com/WB2CBA/TinyDX---Tiny-Digital-Modes-HF-Transceiver

2. JLCPCB Component Library – https://jlcpcb.com/parts/componentSearch

3. Mini-Circuits T2-613-KK81+ Datasheet – https://www.minicircuits.com/pdfs/T2-613-1-KK81.pdf

4. Arduino Bootloader Guide – https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/

5. FT8TW Android Application – https://play.google.com/store/apps/details?id=com.ft8.tw

6. IFTX iOS Application – https://apps.apple.com/us/app/iftx/id6446093115

