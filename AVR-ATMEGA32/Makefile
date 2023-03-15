#@copyright : Ahmed Maged

#Our Device
DEVICE=atmega32

CC=avr-gcc
#gcc
#avr-gcc.exe
#arm none-eabi

CFLAGS= -gdwarf-2

# The headers files needed for building the application ex -I<dir1> -I<dir2> !!!no space between I & dir!!! 
#--> dot "." means current directory ".." back one folder 
INCLUDE= -I.
#INCLUDE += -I../Math/
#INCLUDE += -I<dir2>

#If all Sources File in The Same Location 
SRC =$(wildcard *.c)
#else (src) in different locations 
SRC += $(wildcard ./*/*/*.c)
#SRC += src/file1.c
#SRC += src/file2.c

#For Generate .o File From .c
OBJ =$(SRC:.c=.o)

OBJCOPY = avr-objcopy
CCSIZE = avr-size

#optimizations Options {1, 2, 3(fastest), s(smallest), g(for debugging only)}
OPT = -Os

#For Generate Hex_File
HFLAGS = -j .text -j .data -O ihex

#My Project Name
project_name = DIO
Firmware = DIO
all: $(Firmware).hex $(Firmware).elf size
	
%.o:%.c
	$(CC) $(INCLUDE) $(OPT) $(CFLAGS) -mmcu=$(DEVICE) -c $< -o $@
	
$(Firmware).elf:$(OBJ)
	$(CC) $(INCLUDE) $(OPT) $(OBJ) -mmcu=$(DEVICE) -o $@
	
%.hex:%.elf
	$(OBJCOPY) $(HFLAGS) $< $@
	
size : $(Firmware).elf
	$(CCSIZE) --format=avr --mcu=$(DEVICE) $< 
	
clean_all:
	rm $(OBJ) *.elf *.hex
	@echo "Everything clean successfully"
	
clean:
	rm *.elf *.hex
	@echo "Clean Done Successfully"
	
	
	
	
	
	
	
	
	
	
#Note if src is not in the same location so i should give it to generator of .o like this 
#%.o:$(SRC)
#	$(CC) $^ $(INCLUDE) $(OPT) $(CFLAGS) -mmcu=$(DEVICE) -o $@


