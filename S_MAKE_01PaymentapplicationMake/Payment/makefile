
src_dir := ./src
inc_dir := ./inc
build_dir := ./build
bin_dir := ./bin
rm := rm -rf


CC := gcc
flages := -Werror -Wall
INCLUDES := -I $(inc_dir)

src_files := $(wildcard $(src_dir)/*.c)
obj_files := $(patsubst $(src_dir)/%.c, $(build_dir)/%.o, $(src_files))
bin_file  := $(bin_dir)/$(lastword $(subst /, ,$(CURDIR)))

.PHONY: all clean

all: $(obj_files) $(bin_file) clean



$(build_dir)/%.o: $(src_dir)/%.c

	$(CC) $(INCLUDES) $(flages)  -c $< -o $@

$(bin_file): $(obj_files)

	$(CC) $(flages)  $^ -o $@

clean:
	$(rm) $(obj_files) 