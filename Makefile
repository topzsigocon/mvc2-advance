# Butano template-style Makefile
# CI/local setup clones Butano into ./butano.
LIBBUTANO := butano/butano

TARGET := mvc2_gba_fan_edition
BUILD := build
SOURCES := src
INCLUDES := include

CXXFLAGS := -g -Wall -Wextra -O2 -std=gnu++17 -mcpu=arm7tdmi -mtune=arm7tdmi
CXXFLAGS += -ffunction-sections -fdata-sections
CXXFLAGS += $(foreach dir,$(INCLUDES),-I$(dir))
LDFLAGS := -specs=gba.specs -Wl,--gc-sections

include $(LIBBUTANO)/butano.mak
