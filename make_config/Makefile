CC = gcc
CFLAGS = -I.
DFLAGS = 

FLAG1 := $(shell grep -w "FLAG1" config.h | cut -d ' ' -f 3)
FLAG2 := $(shell grep -w "FLAG2" config.h | cut -d ' ' -f 3)
FLAG3 := $(shell grep -w "FLAG3" config.h | cut -d ' ' -f 3)
FLAG_STR := $(shell grep -w "FLAG_STR" config.h | awk '{print substr($$0, index($$0, $$3))}' | tr -d '"')
FLAG_SPACE := $(shell awk '/^#define FLAG_SPACE/ { print (NF==2) ? "YES" : "NO"}' config.h)

ifeq ($(FLAG1), 1)
	DFLAGS += -DFLAG1_IS_DEFINED
else
	DFALGS += 
endif

ifeq ($(FLAG2), 1)
	DFLAGS += -DFLAG2_IS_DEFINED
else
	DFALGS += 
endif

ifeq ($(FLAG3), 1)
	DFLAGS += -DFLAG3_IS_DEFINED
else
	DFALGS += 
endif

ifeq ("$(strip $(FLAG_STR))", "RAVEN IS GOD !!!")
	DFLAGS += -DFLAG_STR_IS_DEFINED
else
	DFALGS += 
endif

ifeq ("$(strip $(FLAG_SPACE))", "YES")
	DFLAGS += -DFLAG_SPACE_IS_DEFINED
else
	DFALGS += 
endif

all: compile
compile:
	@echo "flag_str = "$(FLAG_STR)
	@echo "flag_space = ""$(strip $(FLAG_SPACE))"
	# @echo "dflags = "$(DFLAGS)
	$(CC) $(CFLAGS) $(DFLAGS) -o main main.c

clean:
	rm -rf main.o main
