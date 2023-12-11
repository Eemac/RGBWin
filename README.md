# RGBWin!!
A kW-scale RGBW LED controller for indoor effect lighting. I designed this board in my sophomore year of high school because no low-cost, highly-programmable RGBW solution existed at the time. The two TSSOP parts (PCA9685 16ch PWM controllers) were the first SMT parts I soldered. 

<img width="1100" alt="RGB_CTL" src="https://github.com/Eemac/RGBWin/assets/28767801/6c384f1c-3ea0-4cce-a8fe-c2e29c577260">

## Schematic
My second time using Autodesk Eagle. I didn't know pin labels were a thing, so all wires are directly routed from input to output. I'm so sorry! :P Also, an interesting story about the big power MOSFETs: the only ones I could find that were in my budget came from an obscure eBay listing. I ended up waiting about a month just to put the final parts on the board because shipping took so long! 
<img width="1069" alt="Screenshot 2023-12-10 at 8 38 13 PM" src="https://github.com/Eemac/RGBWin/assets/28767801/3c736e16-e352-4de5-9565-e856c31945ce">

## PCB
A fairly decent design, I think. I didn't know about ground pours at the time, so I manually routed large ground traces to all of the power MOSFETs.
<img width="1202" alt="PCB" src="https://github.com/Eemac/RGBWin/assets/28767801/6b74a802-0593-4c2d-a868-0058d82da56c">

## Design Files/Code, should anyone want.
Provided in the `project` folder.
The Arduino code includes two libraries: `Thread` (https://www.arduino.cc/reference/en/libraries/thread/), and `PCA9685` (https://www.arduino.cc/reference/en/libraries/pca9685-16-channel-pwm-driver-module-library/). These two links have installation instructions and are supported by the Arduino Library manager.
