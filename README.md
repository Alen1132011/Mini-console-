# Mini Console v1

Mini Console v1 is a small DIY retro gaming console built completely from scratch. The idea was to make a fun little device to kill some boredom, designed in KiCad and programmed for the ESP32-C3.

## Features
- **Two Games**: Currently features built-in classic versions of *Flappy Bird* and *Snake*.
- **Menu & Settings**: Simple menu system to select games and toggle sound on or off.
- **Portable Power**: Uses a TP4056 lithium battery charger and MT3608 boost module so the console runs on battery.
- **Mechanical Controls**: Six push buttons for movement, jumps, and selections.

## Hardware & Bill of Materials (BOM)

| Component | Quantity | Description |
| :--- | :--- | :--- |
| ESP32-C3 SuperMini | 1 | Microcontroller |
| 0.96" I2C OLED Display | 1 | Screen for graphics rendering |
| THT Push Buttons (6mm) | 6 | Mechanical controls |
| TP4056 Battery Charger Module | 1 | Lithium battery charging |
| MT3608 Boost Module | 1 | 5V voltage step-up |
| Buzzer | 1 | Sound output |
| Ceramic Capacitors (100nF) | 2 | Decoupling / Filtering |
| Electrolytic Capacitor (10µF) | 1 | Power filtering |
| Slide Switch (SPST) | 1 | Power toggle switch |
| JST XH Connectors | Multiple | Cable connections |
| Custom Double-Sided PCB | 1 | Circuit board designed in KiCad |

## Software & Code
- Written in the Arduino IDE environment using the `Adafruit_GFX` and `Adafruit_SSD1306` libraries for screen rendering.
- Uses straightforward logic for switching between menus, games, and sound settings.

## Note: 
The project is not fully completed yet. There are only two games right now, but as soon as the physical product arrives and I run tests, I plan to add more games and further polish the project setup.

> <img width="1888" height="1178" alt="Screenshot 2026-10-10 161812" src="https://github.com/user-attachments/assets/5511048f-c52f-4e3c-b99b-eb0c26031570" />
 <img width="1806" height="1197" alt="Screenshot 2026-10-10 161758" src="https://github.com/user-attachments/assets/56a1c083-0350-4996-bcee-923a132c7071" />
<img width="1640" height="969" alt="Screenshot 2026-10-10 161839" src="https://github.com/user-attachments/assets/a7cf09c3-6395-4481-94b7-2ab0f3fe66e3" />
<img width="1456" height="1042" alt="Screenshot 2026-10-10 161822" src="https://github.com/user-attachments/assets/7b9b4d30-1396-44e7-9276-91c7f53142e8" />
