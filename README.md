# MULTI-LEVEL SECURITY ACCESS SYSTEM

## 📌 AIM

The aim of this project is to ensure **high-level security** by implementing a **three-level authentication system** using:

1. **RFID Verification**  
2. **Password Verification (Keypad)**  
3. **Fingerprint Verification (R305 Module)**  

Only users who successfully pass all three stages can access the protected device or system.

---

## 📦 BLOCK DIAGRAM

<img width="1028" height="716" alt="image" src="https://github.com/user-attachments/assets/cdb1bb2a-a1a0-4b14-b382-4f3698a6d0a9" />

---

## 🧰 REQUIREMENTS

### 🔌 Hardware Requirements
- LPC2148 Microcontroller  
- RFID Reader + RFID Cards  
- R305 Fingerprint Module  
- 16x2 LCD  
- AT24C256 EEPROM  
- 4x4 Keypad  
- L293D Motor Driver  
- DC Motor  
- Switch  
- USB-to-UART Converter  

### 💻 Software Requirements
- Embedded C  
- KEIL µVision IDE  
- Flash Magic  

---

## 🧪 PROJECT DEVELOPMENT STEPS

### ✅ 1. Project Structure Creation
Include all required drivers:
- lcd.c / lcd.h  
- uart.c / uart.h  
- delay.c / delay.h  
- keypad.c / keypad.h  
- i2c.c / i2c.h  

---

### 🧩 2. Test Individual Modules

#### LCD Test
Display characters, strings, integers.

#### Keypad Test
Show pressed key on LCD.

#### EEPROM Test
- Write N bytes  
- Read back and display  

#### UART Test
- TX/RX using interrupts  
- Verify using HyperTerminal  

---

### 🆔 3. RFID MODULE TEST

Connect RFID → USB UART → PC Terminal.

**Example Output**  
For card number 12345678:

---


---

### ✋ 4. PASSWORD TEST (Keypad)
- Enter password via keypad.  
- Compare with stored EEPROM value.  
- LCD Output Example:

Enter Password:
Access Granted

## ✋ 5. FINGERPRINT TEST (R305 MODULE)
Steps:
1. Capture finger image  
2. Convert to template  
3. Search template in module memory  

**Output**
Place Finger
Scanning...
Securely Verified
---
## 🖼️ PROJECT IMAGES
### KEIL µVision Project Screenshot

<img width="1919" height="1020" alt="image" src="https://github.com/user-attachments/assets/83f8655f-89d3-44df-b2ef-e9c2016ae3c4" />

### Hardware Setup

# ⭐ PROJECT IMPROVEMENTS
![WhatsApp Image 2025-12-06 at 21 16 41_98df45b4](https://github.com/user-attachments/assets/31a0d5a1-aa0e-4b53-b624-99d471e73783)


## 🎥 Project Demo Video
[▶ Watch Multi-Level Security Access System Demo]("media/multi_level_security_system.mp4")


### ✔ Advantages
- High security with **3-level authentication**  
- Low-cost components  
- Accurate fingerprint matching  
- EEPROM stores permanent user credentials  

### ❌ Drawbacks
- If any single sensor fails → system access fails  
- Fingerprint module needs clean finger surface  
- RFID cards can be lost or stolen  
- More hardware increases project size  

---


# 🏁 CONCLUSION
This project successfully demonstrates a **three-level secure access system** using RFID, Password, and Fingerprint authentication.  
It ensures **robust security** suitable for lockers, labs, offices, and industrial applications.

# 👤 AUTHOR  
**Jahnavi Tammina**  
Embedded Systems Developer  

---


