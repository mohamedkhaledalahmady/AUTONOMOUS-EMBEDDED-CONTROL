# _**AUTONOMOUS-EMBEDDED-CONTROL**_
> ## _Project Description_:
   * This project related to Cairo University Eco-Racing team technical test
   * My task to implement embedded system project that contain some of peripherals such as LCD, dc motor, stepper motor and communication protocol. by using **UART-PC** to transfer data to **MCU** in specific format, then if this valid format MCU filter it and make decisions to control speed and direction of dc motor same for stepper but with angle and direction parameters.
> ## _Contents_:
   * _All project files_ (.h & .c)
   * _Makefile_ : Makefile for running application `compile` `burn` `clean`
   
> ## _Project Requirements_
* `avr-gcc` as out tool chain for compiling
* `WinAVR`
* `Protues` as simulator program


> ## _Project Flow_

![data frame](https://user-images.githubusercontent.com/67025780/189889596-feb53074-a8b8-40d1-a58f-cfca5498a2ce.PNG)

> ## _Protues Simulation_

![proteus](https://user-images.githubusercontent.com/67025780/189891336-032759d2-c7c5-4d39-addc-f5924a40d215.PNG)


> ## _Setup_
  * Download all project files `git clone https://github.com/mohamedkhaledalahmady/AUTONOMOUS-EMBEDDED-CONTROL`
  * Open project in `VS Code` or any IDE.
  * Open terminal, just type `make compile` or `make` only for compiling program
  * Now `hex` file is generated, you can use it for simulation
  * `make clean` to delete all objects files and executable file generated
