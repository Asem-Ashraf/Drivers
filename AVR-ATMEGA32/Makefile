
#Our Device
DEVICE=atmega32

CC=avr-gcc
#avr-gcc.exe
#arm none-eabi
#gcc


CFLAGS = -gdwarf-2
CFLAGS+= -g
CFLAGS+= -MMD -MP

#optimizations Options {1, 2, 3(fastest), s(smallest), g(for debugging only)}
OPT = -Os

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
OBJ = $(SRC:.c=.o)

#For Generate .d File From .o
DEP = $(OBJ:.o=.d)

#For Generate .elf File From APP/*.c
mainSRC =$(wildcard ./APP/*.c)
mainOBJ =$(mainSRC:.c=.o)
mainDEP =$(mainOBJ:.o=.d)
mainELF =$(mainSRC:.c=.elf)
mainHEX =$(mainSRC:.c=.hex)

OBJCOPY = avr-objcopy
CCSIZE = avr-size


#For Generate Hex_File
HFLAGS = -j .text -j .data -O ihex

all:  $(mainHEX) $(mainELF) size
	@echo "Build Done Successfully"

-include $(DEP)

$(SRC):$(wildcard ./LIB/*.h)
	touch -m $@

%.o:%.c
	$(CC) $(INCLUDE) $(OPT) $(CFLAGS) -mmcu=$(DEVICE) -c $< -o $@
	
APP/%.elf: APP/%.o $(OBJ)
	$(CC) $(INCLUDE) $(OPT) $(OBJ) $< -mmcu=$(DEVICE) -o $@
	
%.hex:%.elf
	$(OBJCOPY) $(HFLAGS) $< $@
	
size : $(mainELF)
	$(CCSIZE) --format=avr --mcu=$(DEVICE) $< 
	
ca:
	rm $(mainDEP) $(mainELF) $(mainHEX) $(OBJ) $(DEP) 
	@echo " "
	@echo " "
	@echo "Everything clean successfully"
	
clean:
	rm $(mainDEP) $(mainELF) $(mainHEX)
	@echo " "
	@echo " "
	@echo "Clean Done Successfully"
	
	
	

