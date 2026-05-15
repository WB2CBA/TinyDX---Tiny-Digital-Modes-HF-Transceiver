# TinyDX — Tiny Digital Modes HF Transceiver

[![Build](https://github.com/WB2CBA/TinyDX---Tiny-Digital-Modes-HF-Transceiver/actions/workflows/build.yml/badge.svg)](https://github.com/WB2CBA/TinyDX---Tiny-Digital-Modes-HF-Transceiver/actions/workflows/build.yml)
[![Platform](https://img.shields.io/badge/platform-Arduino%20Uno%20%28ATmega328P%29-blue?logo=arduino)](https://www.arduino.cc/)
[![Si5351 lib](https://img.shields.io/badge/Si5351%20library-v2.1.3%20(NT7S)-informational)](https://github.com/etherkit/Si5351Arduino)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

TinyDX is a miniaturised two-band HF Digital Modes QRPp Transceiver — USB-powered, fits in a 50 × 25 × 30 mm enclosure, and connects directly to a smartphone, tablet, or PC. No separate battery or computer required.

![TinyDX 2](https://github.com/user-attachments/assets/3910f045-4386-422a-8d2e-bf21e2abec2e)

**TinyDX in action:** https://youtu.be/lumVageEz0A?si=CVWjLaan0oGv8utl

---

## Key Specifications

| Feature | Detail |
|---|---|
| Controller | ATmega328P/AU + CM108B USB audio codec |
| Receiver | Quadrature sampling detector (I/Q) |
| Transmitter | SI5351 PLL VCO + 74ACT244 RF power amplifier |
| RF output | 700–900 mW (QRPp) |
| Default bands | 20 m and 15 m |
| Configurable bands | 20 / 17 / 15 / 12 / 10 m (LPF swap required) |
| Power supply | 5V USB — ≤ 350 mA TX, ≤ 100 mA RX |
| Enclosure | 50 × 25 × 30 mm |
| Compatible apps | WSJT-X (PC/Mac/Linux), IFTX (iOS), FT8TW / TrailDigi (Android) |

---

## Quick Start

1. **Build** — order PCBs from JLCPCB using the Gerber, BOM, and CPL files in this repository; solder the through-hole components by hand.
2. **Flash firmware** — upload `TinyDX_V1.4/TinyDX_V1.4.ino` via the Arduino IDE or `arduino-cli`. See the [Arduino ISP guide](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/) for first-time bootloader programming.
3. **Connect** — plug TinyDX into your phone or PC via USB; it appears as *USB Audio Device*.
4. **Configure your app:**
   - **WSJT-X** — Rig: None · PTT: VOX · Audio device: USB Audio Device
   - **IFTX (iOS)** — select TinyDX from the audio input list
   - **FT8TW / TrailDigi (Android)** — select TinyDX from the audio input list

---

## Firmware

The firmware is a single Arduino sketch: `TinyDX_V1.4/TinyDX_V1.4.ino`

**Required library — install via Library Manager:**

> **Etherkit Si5351 v2.1.3** by Jason Mildrum (NT7S) — [github.com/etherkit/Si5351Arduino](https://github.com/etherkit/Si5351Arduino)
>
> **Important:** use v2.1.3 exactly. Other versions are not compatible with TinyDX.

---

## Documentation

- [Technical Paper](docs/TECHNICAL_PAPER.md) — full design description, system architecture, and theory of operation

---

## Credits

- **Barbaros Asuroglu (WB2CBA)** — project design and firmware
- Initial FSK TX signal generation: Burkhard Kainka (DK7JD) — http://elektronik-labor.de/HF/SDRtxFSK2.html
- Improved FSK TX signal generation: JE1RAV — https://github.com/je1rav/QP-7C
- SI5351 library: Jason Mildrum (NT7S) — https://github.com/etherkit/Si5351Arduino

---

## Licence

MIT. See the licence header in the firmware source file.
