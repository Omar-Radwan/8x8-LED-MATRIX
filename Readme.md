# 8x8 LED Matrix
8x8 LED Matrix built using MAX7219 modules and arduino
## Components Used
1. MAX7219 8x8 matrix modules
2. HC05 bluetooth module
3. Arduino board (Uno)
4. 1 PCB 10x10 board, 2 PCB 20x20 boards

## Commands
1. /mode_append: default writing mode, when new message is written it’s appended to the already written message on the screen.
2. /mode_clear: when a new message it replaces the message which is already written on the screen.
3. /clear: removes the message written on the screen.
4. /invert: switches between active low and active high mode.
5. /scroll: starts the scrolling mode (if the message is static).
6. /hold: stops the scrolling mode (if the message is scrolling).
7. /left: makes scrolling direction to the left.
8. /right: makes scrolling direction to the right.
9. /si: increases the scrolling speed (makes scrolling faster).
10. /sd: decreases the scrolling speed (makes scrolling slower ).
11. Typing text without “/” in the beginning won’t be considered as command
and message will be shown on the screen
##Android App Used
Android Bluetooth control


Link: <https://play.google.com/store/apps/details?id=com.broxcode.arduinobluetoothfree&hl=en>
![](./led.gif)