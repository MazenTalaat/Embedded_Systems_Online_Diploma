#Mazen Talaat U3 L3 14-Nov-2021
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project=learn_in_depth_cortexM3

all: $(Project).bin
	@echo "========= Everything Done ========="

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	@echo "========= .S to .O Done ========="

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	@echo "========= .C to .O Done ========="
	
$(Project).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	@echo "========= Linking Done ========="
	
$(Project).bin: $(Project).elf
	$(CC)objcopy.exe -O binary $< $@
	@echo "========= Binary Out Done ========="
	
clean_all:
	rm -rf *.o *.elf *.bin *.map
	@echo "========= Cleaned Everything ========="
clean:
	rm -rf *.elf *.bin
	@echo "========= Cleaned .elf and .bin ========="