#@copyright : Ahmed Maged

#Our Device
DEVICE=atmega32

CC=avr-gcc
#gcc
#avr-gcc.exe
#arm none-eabi

CFLAGS= -gdwarf-2 -g

# The headers files needed for building the application ex -I<dir1> -I<dir2> !!!no space between I & dir!!! 
#--> dot "." means current directory ".." back one folder 
INCLUDE=
# INCLUDE= -I.
#INCLUDE += -I../Math/
#INCLUDE += -I<dir2>

#If all Sources File in The Same Location 
SRC = $(wildcard ./*/*/*.c)
SRC+= $(wildcard ./SERVICE/*.c)
#For Generate .o File From .c
OBJ =$(SRC:.c=.o)

mainSRC =$(wildcard ./APP/*.c)
mainOBJ =$(mainSRC:.c=.o)

#else (src) in different locations 
#SRC += src/file1.c
#SRC += src/file2.c


OBJCOPY = avr-objcopy
CCSIZE = avr-size

#optimizations Options {1, 2, 3(fastest), s(smallest), g(for debugging only)}
OPT = -Og

#For Generate Hex_File
HFLAGS = -j .text -j .data -O ihex

all:  $(mainSRC:.c=.elf) $(mainSRC:.c=.hex)

$(SRC):$(wildcard ./LIB/*.h)
	touch -m $@

%.o:%.c
	$(CC) $(INCLUDE) $(OPT) $(CFLAGS) -mmcu=$(DEVICE) -c $< -o $@
	
APP/%.elf: ./APP/%.o $(OBJ)
	$(CC) $(INCLUDE) $(OPT) $(OBJ) $< -mmcu=$(DEVICE) -o $@
	
%.hex:%.elf
	$(OBJCOPY) $(HFLAGS) $< $@
	
# size : APP/*.elf
# 	$(CCSIZE) --format=avr --mcu=$(DEVICE) $< 
	
ca:
	rm $(OBJ) ./APP/*.elf ./APP/*.hex
	@echo "Everything clean successfully"
	
clean:
	rm ./APP/*.elf ./APP/*.hex
	@echo "Clean Done Successfully"
	
	
	
	
	
	
	
	
	
	
#Note if src is not in the same location so i should give it to generator of .o like this 
#%.o:$(SRC)
#	$(CC) $^ $(INCLUDE) $(OPT) $(CFLAGS) -mmcu=$(DEVICE) -o $@


