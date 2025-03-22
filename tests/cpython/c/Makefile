# main makefile
#
#	@File:      Makefile
#	@Author:    Sam.Nazarov
#   @Note:		This makefile only for use from `pwd` directory with pyenv.

SHELL := /bin/bash
TARGET = cheak__geompy

# Inputs (default values)
build_dir             = $(shell pwd)
debug                 = 0
lib_sitepackages_path = 
py_version            = $(shell python3 -c \
"from sysconfig import get_config_var; print(get_config_var('py_version_nodot'));")

BUILD_DIR := ./build
SRC_DIRS  := ./

SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -type f -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC     := gcc
PYTHON := python$(py_version)

EXT_SUFFIX         = $(shell $(PYTHON) -c \
"from sysconfig import get_config_var; print(get_config_var('EXT_SUFFIX'));")
INSTALLED_PLATBASE = $(shell cygpath -m $(shell $(PYTHON) -c \
"from sysconfig import get_config_var; print(get_config_var('installed_platbase'));"))
PROJECT_SRC_PATH   = $(shell cygpath -m "`pwd`/../../../src")
TESTS_CPYTHON_PATH = $(shell cygpath -m "`pwd`/../")

INCFLAGS    := -I"$(shell $(PYTHON) -c \
"from sysconfig import get_path; print(get_path('include'));")"
CDEBUGFLAGS := $(shell if [[ $(debug) == 1 ]]; then echo \
-g3 -O0 \
; else echo -O0; fi)
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Preprocessor-Options.html#Options-Controlling-the-Preprocessor
CDEFSFLAGS  := \
-D'LIB_SITEPACKAGES_PATH=$(lib_sitepackages_path)' \
-D'PY_PLATBASE=$(INSTALLED_PLATBASE)' \
-D'SRC_PATH=$(PROJECT_SRC_PATH)' \
-D'TESTS_CPYTHON_PATH=$(TESTS_CPYTHON_PATH)'
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS 	    := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-fvisibility=hidden -std=c99 -pedantic $(INCFLAGS)
CGCOVFLAGS   = 

LIBDIRS    	:= -L"$(shell $(PYTHON) -c \
"from sysconfig import get_config_var; print(get_config_var('installed_platbase') + '/libs');")"
LIBNAMES    := check python$(py_version)
LIBNAMES    += $(shell if [[ $(EXT_SUFFIX) =~ .so$ ]]; then echo \
m subunit \
; else echo ; fi)
LDFLAGS    	:= $(LIBDIRS) $(addprefix -l,$(LIBNAMES))
LDGCOVFLAGS := 

$(build_dir)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o "$(build_dir)/$(TARGET)" $(OBJS) $(LDFLAGS) $(LDGCOVFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEFSFLAGS) $(CDEBUGFLAGS) $(CGCOVFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(build_dir)/cheak__geompy
