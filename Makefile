#---------------------------------------------------------------------------------------------------------------------
# Marvel vs. Capcom 2: New Age of Heroes – GBA Fan Edition
# Phase 1 - Core engine, menu, character select, basic combat
#---------------------------------------------------------------------------------------------------------------------

# Target name of the ROM
TARGET       := mvc2_gba_fan

# Build directory
BUILD        := build

# Path to Butano library (adjust if needed; for CI we set this)
# Local: set to relative or absolute path to butano/butano
LIBBUTANO    := ../butano/butano

# Python interpreter
PYTHON       := python3

# Source directories
SOURCES      := src

# Include directories
INCLUDES     := include

# Data directories (if any)
DATA         :=

# Graphics directories
GRAPHICS     := graphics

# Audio directories
AUDIO        := audio

# Audio backend
AUDIOBACKEND := maxmod

# ROM title (max 12 chars)
ROMTITLE     := MVC2 GBA FAN

# ROM code (4 chars)
ROMCODE      := B2FE

# Export absolute butano path
ifndef LIBBUTANOABS
    export LIBBUTANOABS := $(realpath $(LIBBUTANO))
endif

# Include main Butano makefile
include $(LIBBUTANOABS)/butano.mak
