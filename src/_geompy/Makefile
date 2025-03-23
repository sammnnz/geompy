# main makefile
#
#	@File:      Makefile
#	@Author:    Sam.Nazarov
#   @Note:		This makefile only for use from root directory.

SHELL  := /bin/bash
TARGET  = _geompy$(shell $(PYTHON) -c \
"from sysconfig import get_config_var; print(get_config_var('EXT_SUFFIX'));")

# Inputs (default values)
build_dir  = $(shell pwd)
coverage   = 0
debug      = 0
py_version = $(shell python3 -c \
"from sysconfig import get_config_var; print(get_config_var('py_version_nodot'));")

BUILD_DIR := $(shell pwd)/build
SRC_DIRS  := ./ ./objects

SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -type f -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC     := gcc
PYTHON := python$(py_version)

INCFLAGS    := -I"$(shell $(PYTHON) -c \
"from sysconfig import get_path; print(get_path('include'));")"
INCFLAGS    += -I"./include"
CDEBUGFLAGS := $(shell if [[ $(debug) == 1 ]]; then echo \
-g3 -O0\
; else echo \
-DNDEBUG -O3\
; fi)
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS 	    := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-fvisibility=hidden -std=c99 -pedantic -fPIC $(INCFLAGS) $(CDLLFLAGS)
CGCOVFLAGS   = $(shell if [[ $(coverage) == 1 ]]; then echo \
-fprofile-arcs -ftest-coverage -O0 \
; else echo ; fi)

LIBDIRS    	 = -L"$(shell $(PYTHON) -c \
"from sysconfig import get_config_var; print(get_config_var('installed_platbase') + '/libs');")"
LDFLAGS    	:= $(LIBDIRS) -lpython$(py_version) -shared
LDGCOVFLAGS := $(shell if [[ $(coverage) == 1 ]]; then echo \
--coverage \
; else echo ; fi)


.PHONY: clean, build_ext, build_ext_gcc_pyd
build_ext_gcc_pyd: $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o "$(build_dir)/$(TARGET)" $(OBJS) $(LDFLAGS) $(LDGCOVFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(CGCOVFLAGS) -c $< -o $@

build_ext:
	# https://setuptools.pypa.io/en/latest/deprecated/distutils/configfile.html
	cd `pwd`/../../ && $(PYTHON) setup.py build_ext --build-lib=$(build_dir) --build-temp=$(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(build_dir)/$(TARGET)
