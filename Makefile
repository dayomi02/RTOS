ARCH = armv7-a
MCPU = cortex-a8

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./daios.ld
MAP_FILE = build/daios.map

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.os, $(ASM_SRCS))

C_SRCS = $(wildcard boot/*.c)
C_OBJS = $(patsubst boot/%.c, build/%.o, $(C_SRCS))

INC_DIRS = -I include

ios = build/daios.axf
ios_bin = build/daios.bin

.POONY: all clean run debug gdb kill

all: $(ios)

clean:
	@rm -rf build

run: $(ios)
	qemu-system-arm -M realview-pb-a8 -kernel $(ios)

debug: $(ios)
	qemu-system-arm -M realview-pb-a8 -kernel $(ios) -S -gdb tcp::1234,ipv4

gdb:
	gdb-multiarch

kill:
	kill -9 'ps aux | grep 'qemu' | awk 'NR==1{print $$2}''

$(ios) : $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(ios) $(ASM_OBJS) $(C_OBJS) -Map=$(MAP_FILE)
	$(OC) -O binary $(ios) $(ios_bin)

build/%.os: $(ASM_SRCS)
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(INC_DIRS) -c -g -o $@ $<

build/%.o: $(C_SRCS)
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(INC_DIRS) -c -g -o $@ $<

