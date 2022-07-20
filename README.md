# Blast B4 Macro Pad
This is project is a macro pad/ button board for sending keyboard key presses to a pc from an atmega32u4 using the Arduino framework and NicoHood's [HID-Project](https://github.com/NicoHood/HID) library.

Most of my code is handling button states and debouncing.
I wanted to keep all the state detection and setting out of the button keypress code to make editing macros less of a mess in the future.
As for the button states themselves, they are stored in a single uint8_t variable to be interpreted in binary for and is One-Hot Encoded. This means that each button corresponds to a single bit out of eight present, allowing up to eight buttons currently. 
Adding more buttons than that simply requires changing the uint8_t to uint16_t for 16 buttons, for example.

Because the states are One-Hot Encoded, I handle checking and setting them using bit-wise operations.
Overall, this saves a few of bytes of storage and might

I have created functions for getting info on whether a particular button has been pressed, released, or hold.
A library will be made of all this button handling code and those three functions make up the public interface.



### Note:
Rather than using the Arduino IDE, this was created using the PlatformIO plugin on VSCode.
Because of this, the code is not stored in a .ino file.