MCU_name := atmega32		
frquency := 8000000UL
src_file := main.c GPIO.c LCD.c UART.c
project_name := application
programmer := usbasp
MCU_code := m328p
CC := avr-gcc
CC_Format := avr-objcopy
CC_Size := avr-size
CC_Flags := -w -O0 

default: compile

all:
	Test-Path -Path 'C:\Users\MG\Desktop\Makefile\main.c' -PathType Leaf

burn: compile
	@echo "Check Connections"
	@avrdude -c $(programmer) -p $(MCU_code)
	@echo "Start Burning"
	@avrdude -c $(programmer) -p $(MCU_code) -U falsh:w:$(project_name).hex

compile:
	@echo "Starting compiling"
	@$(CC) $(CC_Flags) -mmcu=$(MCU_name) -DF_CPU=$(frquency) $(src_file) -o $(project_name).o
	@$(CC_Format) -O ihex $(project_name).o $(project_name).hex
	@echo "size of program"
	@$(CC_Size) --format=avr --mcu=$(MCU_name)  $(project_name).o

clean:
	@rm -f *.o *.hex
	@echo "Clean done"

.PHONY: compile burn clean all