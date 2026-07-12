# Wiring Guide

This document describes the wiring used in the Simon Says Arduino project.

---

# Arduino Pin Mapping

## LEDs

| LED | Arduino Pin |
|-----|------------:|
| LED 1 | D9 |
| LED 2 | D10 |
| LED 3 | D11 |
| LED 4 | D12 |

---

## Push Buttons

| Button | Arduino Pin |
|--------|------------:|
| Button 1 | D2 |
| Button 2 | D3 |
| Button 3 | D4 |
| Button 4 | D5 |

All buttons use the Arduino's internal pull-up resistors (`INPUT_PULLUP`).

Each button connects:

Arduino Pin → Button → GND

---

## Passive Buzzer

| Device | Arduino Pin |
|---------|------------:|
| Passive Buzzer | D8 |

---

# Shift Registers (74HC595)

Two 74HC595 shift registers are cascaded together to drive the two 7-segment displays.

## Control Pins

| Shift Register Pin | Arduino Pin |
|-------------------|------------:|
| DATA (DS) | A0 |
| LATCH (ST_CP) | A1 |
| CLOCK (SH_CP) | A2 |

---

## Seven Segment Displays

The project uses:

- Two Common Anode 7-Segment Displays
- Two 74HC595 Shift Registers

The displays show the player's current score.

---

# Power Connections

| Device | Connection |
|---------|-----------|
| Arduino | USB |
| LEDs | 5V via resistor |
| Push Buttons | GND |
| Shift Registers | 5V |
| Seven Segment Displays | 5V |
| Passive Buzzer | D8 and GND |

---

# Circuit Diagram

![Final Circuit](../images/final_circuit.png)

---

# Notes

- The project uses `INPUT_PULLUP`, so external pull-up resistors are **not required**.
- The shift registers communicate using the Arduino `shiftOut()` function.
- The score display is updated through the `displayScore()` and `sendData()` functions.
- A passive buzzer is used to generate different tones during gameplay.

---

# Project Pin Summary

| Arduino Pin | Connected Device |
|-------------|------------------|
| D2 | Button 1 |
| D3 | Button 2 |
| D4 | Button 3 |
| D5 | Button 4 |
| D8 | Passive Buzzer |
| D9 | LED 1 |
| D10 | LED 2 |
| D11 | LED 3 |
| D12 | LED 4 |
| A0 | 74HC595 DATA |
| A1 | 74HC595 LATCH |
| A2 | 74HC595 CLOCK |

---