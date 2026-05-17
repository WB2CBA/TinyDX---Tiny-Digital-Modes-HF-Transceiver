# TinyDX — Bill of Materials

This document lists the SMD components ordered via JLCPCB pick-and-place for each
board. LCSC part codes (C-prefixed) are used by JLCPCB's component library.

Parts can be searched at: https://jlcpcb.com/parts/componentSearch

The through-hole components soldered by hand (FTDI header, Mini-Circuits T2-613-KK81+
transformer, SMA connector) are listed separately at the end.

---

> ⚠️ **Known BOM issue — Main Board R8/R9:**
> Issue [#10](https://github.com/WB2CBA/TinyDX---Tiny-Digital-Modes-HF-Transceiver/issues/10)
> documents that R8 and R9 are transposed in the schematic and BOM. The values below
> reflect the current BOM files; verify against the schematic before ordering.

---

## Main Controller Board

*Contains: ATmega328P/AU microcontroller, CM108B USB audio codec, USB Mini-B connector,
BAND and MODE slide switches, oscillator crystals, LEDs.*

| Value | Designator(s) | Package | LCSC |
|---|---|---|---|
| 100 nF | C1, C2, C18, C23, C25, C28, C29 | 0603 | C24452 |
| 10 uF | C11, C12, C13, C14 | 0603 | C19702 |
| 22 pF | C15, C22 | 0603 | C1653 |
| 22 pF | C16, C21 | 0603 | C1653 |
| 10 uF / 16 V | C17, C24 | Tantalum EIA-3528-21 | C110050 |
| 100 uF / 16 V | C27 | Tantalum EIA-3528-21 | C16133 |
| 10 nF | C30, C31 | 0603 | C57112 |
| LED (AUDIO indicator) | D1 | 0805 | C108412 |
| LED (TX indicator) | D2 | 0805 | C84256 |
| USB Mini-B connector | J4 | Horizontal (Lumberg 2486-01) | C91144 |
| 100 uH | L1, L4, L5, L6, L7, L10 | 0805 | C223143 |
| 10 k | R1, R10, R11, R19 | 0603 | C25804 |
| 1 M | R2, R4 | 0603 | C22935 |
| 1 k | R3, R6 | 0603 | C21190 |
| 1.5 k | R5 | 0603 | C22843 |
| 470 k | R8 ⚠️ | 0603 | C23178 |
| 4.7 k | R9 ⚠️ | 0603 | C23162 |
| Slide switch (MODE) | SW1 | THD | C319020 |
| Slide switch (BAND) | SW2 | THD | C319020 |
| ATmega328P-AU | U1 | TQFP-32 7×7 mm | C14877 |
| CM108AH | U3 | LQFP-48 7×7 mm | C371347 |
| 16 MHz crystal | Y1 | SMD FA238 3.2×2.5 mm | C13738 |
| 12 MHz crystal | Y4 | SMD FA238 3.2×2.5 mm | C9002 |

⚠️ R8 (470 k) and R9 (4.7 k) are reported as transposed in the schematic vs. the BOM
(issue #10). Verify against the schematic PDF before ordering.

---

## Transmitter Board

*Contains: SI5351A PLL VCO, 74ACT244 RF power amplifier, 5-band LPF, AMS1117-3.3 LDO,
MT3608 boost converter (5 V → 6.5 V for PA), 26 MHz crystal.*

| Value | Designator(s) | Package | LCSC |
|---|---|---|---|
| 100 nF | C39, C40, C41, C43, C44, C53, C54 | 0603 | C24452 |
| 100 pF | C45 | 0603 | C71664 |
| 12 pF | C46 | 0603 | C38523 |
| 180 pF | C47 | 0603 | C107041 |
| 150 pF | C49 | 0603 | C37298 |
| 39 pF | C50 | 0603 | C107049 |
| 56 pF | C48, C51 | 0603 | C107053 |
| 100 uF / 16 V | C52 | Tantalum EIA-3528-21 | C16133 |
| 10 uF / 16 V | C55 | Tantalum EIA-3528-21 | C110050 |
| 22 uF | C56, C57 | 0603 | C84419 |
| 1N4148 | D3, D6 | SOD-123 | C81598 |
| 1N5817 | D4 | SOD-123 | C727113 |
| 100 uH | L11 | 0805 | C223143 |
| 22 uH | L12 | Power inductor (SubW) | C497873 |
| 330 nH | L3 | 1210 | C295307 |
| 270 nH | L8, L9 | 1008 | C295305 |
| 4.7 k | R17, R18 | 0603 | C23162 |
| 3.9 k | R20 | 0603 | C23018 |
| 12 k | R21 | 0603 | C22790 |
| 1.1 k | R22 | 0603 | C22764 |
| SI5351A | U5 | MSOP-10 3×3 mm | C504891 |
| 74ACT244 | U7 | TSSOP-20 4.4×6.5 mm | C6930 |
| AMS1117-3.3 | U8 | SOT-223 | C6186 |
| MT3608 (boost) | U9 | SOT-23-6 | C84817 |
| 26 MHz crystal | Y2 | SMD FA238V 3.2×2.5 mm | C213404 |

> **Hand-soldered (not in JLCPCB pick-and-place order):**
> - Mini-Circuits T2-613-KK81+ RF transformer — [datasheet](https://www.minicircuits.com/pdfs/T2-613-1-KK81.pdf)
> - SMA antenna connector

---

## Receiver Board

*Contains: TX/RX switch (BSS123 MOSFET), 74ACT74 I/Q divider, 74CBT3253 / LM4562
quadrature sampling detector, 3.5 mm audio output jack.*

| Value | Designator(s) | Package | LCSC |
|---|---|---|---|
| 470 nF | C20, C26, C32, C33 | 0603 | C1623 |
| 1 nF | C34, C35 | 0603 | C1588 |
| 1 uF | C37, C38 | 0603 | C15849 |
| 100 uF / 16 V | C4 | Tantalum EIA-3528-21 | C16133 |
| 10 nF | C3, C5, C7 | 0603 | C57112 |
| 100 nF | C6, C8, C10, C19, C36, C42 | 0603 | C24452 |
| 10 uF / 16 V | C9 | Tantalum EIA-3528-21 | C110050 |
| 3.5 mm audio jack (I/Q out) | J8 | SMT horizontal | C22355831 |
| 100 uH | L2 | 0805 | C223143 |
| BSS123 MOSFET (TX/RX switch) | Q1 | SOT-23-3 | C85107 |
| 1 k | R7, R12 | 0603 | C21190 |
| 10 k | R13, R14 | 0603 | C25804 |
| 3 k | R15, R16 | 0603 | C4211 |
| 74CBT3253 (QSD) | U2 | TSSOP-16 4.4×5 mm | C424399 |
| LM4562 op-amp | U4 | SOIC-8 3.9×4.9 mm | C57367 |
| SN74ACT74DR (I/Q divider) | U6 | SOIC-14 3.9×8.7 mm | C6933 |

---

## Cover Plates

Two identical cover plates (top and bottom). Order using
`TinyDX Fabrication Files/GERBER TINY DX COVER.zip` as a standard PCB order
with no SMT assembly. No BOM or CPL files required.

<!-- TODO: verify — confirm whether top and bottom covers are identical or mirrored -->

---

## Through-hole Components (all boards)

These are **not** supplied by JLCPCB and must be sourced and hand-soldered.

| Component | Board | Notes |
|---|---|---|
| 6-pin 2.54 mm male header | Main | FTDI programming interface |
| Mini-Circuits T2-613-KK81+ | TX | RF transformer — [datasheet](https://www.minicircuits.com/pdfs/T2-613-1-KK81.pdf) · [order](https://www.minicircuits.com/WebStore/dashboard.html?model=T2-613-1-KK81%2B) |
| SMA connector (50 Ω) | TX | Antenna connection |

---

## Hardware (fasteners)

| Item | Quantity |
|---|---|
| M3 spacers, 6 mm | 4 |
| M3 bolts | 4 |
| M3 nuts | 4 |

<!-- TODO: verify — confirm spacer length and count from a completed build -->
