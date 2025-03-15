# main makefile
#
#	@File:      Makefile
#	@Author:    Sam.Nazarov
#   @Note:		This makefile only for use from `pwd` directory with pyenv.

SHELL := /bin/bash
TARGET = test__geompy

# Inputs (default values)
build_dir  = $(shell pwd)
coverage   = 0
debug      = 0
py_version = $(shell python3 -c \
"from sysconfig import get_config_var; print(get_config_var('py_version_nodot'));")
src_path   = .

PY_PLATBASE=$(shell cygpath -m $(shell $(PYTHON_V) -c \
"from sysconfig import get_config_var; print(get_config_var('installed_platbase'));"))
PYTHON_V := python$(py_version)

BUILD_DIR := ./build
SRC_DIRS  := ./

SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -type f -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC := gcc

INCFLAGS    := -I"$(shell $(PYTHON_V) -c \
"from sysconfig import get_path; print(get_path('include'));")"
# INCFLAGS    += -I"`pwd`/../../../src/_geompy/include"
CDEBUGFLAGS := $(shell if [[ $(debug) == 1 ]]; then echo \
-g3 -O0 \
; else echo ; fi)
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Preprocessor-Options.html#Options-Controlling-the-Preprocessor
CDEFSFLAGS  := \
-D'SRC_PATH="$(src_path)"' \
-D'TESTS_CPYTHON_PATH="$(tests_cpython_path)"' \
-D'LIB_SITEPACKAGES_PATH="$(lib_sitepackages_path)"' \
-D'PY_PLATBASE="$(PY_PLATBASE)"'
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS 	    := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-fvisibility=hidden -std=c99 -pedantic -O2 $(INCFLAGS)
CGCOVFLAGS   = $(shell if [[ $(coverage) == 1 ]]; then echo \
-fprofile-arcs -ftest-coverage -fprofile-abs-path -O0 \
; else echo ; fi)

LIBDIRS    	:= -L"$(shell $(PYTHON_V) -c \
"from sysconfig import get_config_var; print(get_config_var('installed_platbase') + '/libs');")"
# LIBDIRS     += -L"$(shell find "$(build_dir)" -maxdepth 1 -type f -name "_geompy.*$(py_version)*.pyd")"
# PYDBASENAME := $(shell baseName $(shell find "$(build_dir)" -maxdepth 1 -type f -name "_geompy.*$(py_version)*.pyd"))
# PYDBASENAME := $(PYDBASENAME:%.pyd=%)
LIBNAMES    := python$(py_version)
LDFLAGS    	:= $(LIBDIRS) $(addprefix -l,$(LIBNAMES))
LDGCOVFLAGS := $(shell if [[ $(coverage) == 1 ]]; then echo \
--coverage \
; else echo ; fi)

$(build_dir)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o "$(build_dir)/$(TARGET)" $(OBJS) $(LDFLAGS) $(LDGCOVFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEFSFLAGS) $(CDEBUGFLAGS) $(CGCOVFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(build_dir)/test__geompy
