########################################	FLASHING section	########################################### 

MCU := atmega32
F_CPU := 8000000
BAUDRATE  := 
FLASHER_TYPE = usbasp
FLASHER_PRO := avrdude
FLASH_FLAGES :=    $(FLASHER_PRO) -c $(FLASHER_TYPE) -p $(MCU)  -U flash:w:

########################################	FLASHING section	########################################### 

########################################		Directories		########################################### 

src_dir := ./src
inc_dir := ./inc
build_dir := ./build
bin_dir := ./bin

########################################		Directories		########################################### 

########################################		Cleaning		########################################### 

rm := rm -rf

########################################		Cleaning		########################################### 

########################################	Compiler section	########################################### 

CC := avr-gcc
flages := -Werror -Wall
INCLUDES := -I$(inc_dir)

src_files := $(wildcard $(src_dir)/*.c)
obj_files := $(patsubst $(src_dir)/%.c, $(build_dir)/%.o, $(src_files))
bin_file  := $(bin_dir)/$(lastword $(subst /, ,$(CURDIR)))

########################################	Compiler section	########################################### 


.PHONY: all clean

all: $(obj_files) $(bin_file) clean


$(build_dir)/%.o: $(src_dir)/%.c

	$(CC) $(INCLUDES) $(flages)  -c $< -o $@


$(bin_file): $(obj_files)

	$(CC) $(flages)  $^ -o  $@.hex


flash: $(bin_file).hex
	$(FLASHER_PRO) $(FLASH_FLAGES) $<

clean:
	$(rm) $(obj_files) 