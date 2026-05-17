# TinyDX — Operating Guide

This guide covers connecting TinyDX to a host device and configuring compatible
applications for FT8 and FT4 operation.

**Prerequisites:**
- Firmware uploaded (see [SETUP.md](SETUP.md))
- Antenna connected to the SMA connector
- TinyDX connected to your host device via USB

---

## How TinyDX Appears to the Host

TinyDX uses the CM108B USB audio codec chip. When connected via USB it appears as
a standard **USB Audio Device** — no driver installation is required on any
supported operating system (Windows, macOS, Linux, Android, iOS).

The device provides:
- **Audio input** (microphone) — received I-signal from the quadrature detector
- **Audio output** (speaker) — TX audio from the host application drives the PA

PTT (push-to-talk) is triggered by **VOX** — when the host application sends audio
above a threshold, TinyDX switches from receive to transmit automatically.

---

## Controls

| Control | Location | Function |
|---------|----------|---------|
| BAND switch (B1/B2) | Main board edge | Select Band 1 (20 m) or Band 2 (15 m) |
| MODE switch (FT8/FT4) | Main board edge | Select FT8 or FT4 mode |
| AUDIO LED | Main board | Lights during USB audio activity |
| TX LED | Main board | Lights during transmit |

<!-- TODO: photo — top view of assembled TinyDX showing switch and LED locations -->
<!-- TODO: verify — confirm LED colours from a built unit -->

> **Note:** Set the band switch *before* launching your application. The SI5351
> frequency is set at startup; changing the switch while the application is running
> requires a power cycle to take effect.
>
> <!-- TODO: verify — confirm whether a power cycle is required or if re-tuning happens dynamically -->

---

## WSJT-X (PC, Mac, Linux)

<!-- TODO: photo — WSJT-X audio settings dialog showing TinyDX selected -->

1. Open WSJT-X.
2. Go to **File → Settings → Audio** tab.
3. Set **Soundcard Input** to **USB Audio Device** (the TinyDX).
4. Set **Soundcard Output** to **USB Audio Device** (the TinyDX).
5. Go to **File → Settings → Radio** tab.
6. Set **Rig** to **None**.
7. Set **PTT Method** to **VOX**.
8. Click **OK**.

The waterfall should begin showing received signals immediately. FT8 decodes appear
at the start of each 15-second slot; FT4 decodes at the start of each 7.5-second slot.

<!-- TODO: verify — confirm any audio level adjustments needed (input gain, output level) -->

---

## IFTX (iOS)

<!-- TODO: photo — IFTX audio device selection screen showing TinyDX -->

1. Connect TinyDX to your iPhone or iPad using a USB Lightning/USB-C to USB-A adapter
   (Camera Connection Kit or equivalent).
2. Open IFTX.
3. In audio settings, select **USB Audio Device** (the TinyDX) as the input and output.
4. Select the band and mode to match your TinyDX switch positions.

IFTX: https://apps.apple.com/us/app/iftx/id6446093115

<!-- TODO: verify — confirm exact menu path in IFTX for audio device selection -->

---

## FT8TW (Android)

<!-- TODO: photo — FT8TW audio settings showing TinyDX selected -->

1. Connect TinyDX to your Android phone or tablet using a USB OTG adapter.
2. Open FT8TW.
3. Go to **Settings → Audio**.
4. Select **USB Audio Device** (TinyDX) as the audio input and output.
5. Set band and mode in the app to match your TinyDX switch positions.

> **USB Audio on Android:** Android's USB audio implementation varies by device and
> OS version. If TinyDX is not detected, try a different OTG adapter or USB cable.
> TinyDX is USB class-compliant and does not require a driver.

<!-- TODO: verify — confirm USB audio detection behaviour on Android 13+ and Android 16 -->
<!-- TODO: verify — confirm exact menu path in FT8TW for audio device selection -->

---

## Portable Operation Tips

TinyDX draws ≤ 350 mA on TX and ≤ 100 mA on RX from a 5 V USB source — well within
USB power management limits. This means it can be powered directly from a phone or
tablet's USB port, with no separate battery or power supply required.

For SOTA and POTA activations:
- A modern smartphone with USB OTG and FT8TW provides a complete self-contained station
- A 10,000 mAh USB power bank runs TinyDX for many hours on RX; TX duty cycle is
  low in FT8 (typically 50% or less during a QSO)
- Keep the USB cable short to minimise RF noise pickup from the data lines

<!-- TODO: verify — add any RF interference mitigation tips found in practice (ferrite chokes, etc.) -->

---

## Changing Bands

TinyDX supports 20 / 17 / 15 / 12 / 10 m. The default firmware configures
Band 1 = 20 m and Band 2 = 15 m.

To use a different pair of bands, edit the frequency constants in the firmware
source and re-upload. Changing bands also requires fitting the correct low-pass
filter for the new band — the LPF is part of the TX board.

<!-- TODO: verify — identify which LPF components correspond to which band -->
<!-- TODO: verify — confirm whether LPF swap is achievable without desoldering the TX board from the stack -->

---

## What's Next

- [SETUP.md](SETUP.md) — firmware upload if not done yet
- [BUILD.md](BUILD.md) — hardware build guide
- [BOM.md](BOM.md) — full bill of materials
- [TECHNICAL_PAPER.md](TECHNICAL_PAPER.md) — system architecture and design details
