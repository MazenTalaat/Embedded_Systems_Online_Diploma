#Mazen Talaat 26-Nov-2021

# %.x all files end with .x
# $@ replace by name of target
# $< replace by first prerequisite
# $^ replace by all prerequisites

CC     = arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -mthumb -gdwarf-2

SRCDIR = src
OBJDIR = obj
INCDIR = include
BINDIR = bin

LIBS=

INCS = -I $(INCDIR)
SRC  = $(wildcard $(SRCDIR)/*.c)
OBJ  = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

Project   = Project1_Pressure_Controller
P_BIN_DIR = $(BINDIR)/$(Project)

all: $(P_BIN_DIR).bin $(P_BIN_DIR).hex
	@echo "========= Everything Done ========="

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	@echo "========= .C to .O Done ========="
	
$(P_BIN_DIR).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $^ -o $@ -Map=$(BINDIR)/map_file.map
	@echo "========= Linking Done ========="
	
$(P_BIN_DIR).bin: $(P_BIN_DIR).elf
	$(CC)objcopy.exe -O binary $< $@
	@echo "========= Binary Out Done ========="
	
$(P_BIN_DIR).hex: $(P_BIN_DIR).elf
	$(CC)objcopy.exe -O ihex $< $@
	@echo "========= Hex Out Done ========="

clean_all:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*.elf $(BINDIR)/*.bin $(BINDIR)/*.map $(BINDIR)/*.hex
	@echo "========= Cleaned Everything ========="
clean:
	rm -rf $(BINDIR)/*.elf $(BINDIR)/*.bin
	@echo "========= Cleaned .elf and .bin ========="
	