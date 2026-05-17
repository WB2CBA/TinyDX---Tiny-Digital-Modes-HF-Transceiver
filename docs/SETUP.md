# TinyDX — Firmware Setup Guide

This guide covers installing the required library and uploading the TinyDX firmware.

**Prerequisite:** The ATmega328P bootloader must already be programmed via ISP.
If you have not done this yet, see [BUILD.md](BUILD.md) — Step 4.

---

## 1 — Install the Required Library

TinyDX requires **exactly one** external library:

> **Etherkit Si5351 v2.1.3** by Jason Mildrum (NT7S)
> https://github.com/etherkit/Si5351Arduino

> ⚠️ **Use v2.1.3 exactly.** Other versions are not compatible with TinyDX.

### Arduino IDE (Library Manager)

1. Open Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for **Si5351**.
4. Find **Etherkit Si5351** by NT7S.
5. Select version **2.1.3** from the dropdown and click **Install**.

### arduino-cli

```bash
arduino-cli lib install "Etherkit Si5351@2.1.3"
```

---

## 2 — Connect TinyDX via FTDI Adapter

Connect a USB-to-TTL FTDI adapter (3.3 V or 5 V switchable) to the FTDI header on
the Main Controller board.

<!-- TODO: photo — FTDI adapter plugged into TinyDX FTDI header, showing cable routing -->
<!-- TODO: verify — confirm voltage level (3.3 V vs 5 V) required for reliable programming -->

FTDI adapter pinout:

| FTDI adapter | TinyDX FTDI header |
|---|---|
| GND | GND |
| CTS | — (not connected) |
| VCC | — (do not power TinyDX via FTDI; use USB instead) |
| TX | RX |
| RX | TX |
| DTR | DTR (reset) |

<!-- TODO: verify — confirm exact pin order on TinyDX FTDI header from silkscreen -->

---

## 3 — Upload Firmware

Open `TinyDX_V1.4/TinyDX_V1.4.ino`.

### Arduino IDE

1. Go to **Tools → Board → Arduino AVR Boards → Arduino Uno**.
2. Go to **Tools → Port** and select the port for your FTDI adapter.
3. Click **Upload** (→).

### arduino-cli

```bash
arduino-cli compile --fqbn arduino:avr:uno TinyDX_V1.4/TinyDX_V1.4.ino
arduino-cli upload  --fqbn arduino:avr:uno --port /dev/ttyUSB0 TinyDX_V1.4/TinyDX_V1.4.ino
```

Replace `/dev/ttyUSB0` with the correct port for your system
(`COMx` on Windows, `/dev/cu.usbserial-*` on macOS).

---

## 4 — Verify the Upload

After uploading, connect TinyDX to a USB host (phone, tablet, or PC).
The device should enumerate as **USB Audio Device** in the operating system's
audio settings within a few seconds.

<!-- TODO: verify — describe any LED or indicator behaviour that confirms a successful upload -->

---

## 5 — Default Band Configuration

Out of the box, TinyDX is configured for:

| Switch position | Band | FT8 frequency | FT4 frequency |
|---|---|---|---|
| B1 | 20 m | 14.074 MHz | 14.080 MHz |
| B2 | 15 m | 21.074 MHz | 21.140 MHz |

Additional bands (20 / 17 / 15 / 12 / 10 m) can be configured by editing the
frequency constants in the firmware source before uploading.

<!-- TODO: verify — confirm exact frequency constants and variable names from source -->

The **MODE** switch on the Main board selects FT8 or FT4.

---

## What's Next

- [OPERATING.md](OPERATING.md) — connecting TinyDX to WSJT-X, IFTX, and FT8TW
- [BUILD.md](BUILD.md) — hardware build guide
