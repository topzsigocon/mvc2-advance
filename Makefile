# Butano project Makefile (based on the official Butano template layout)
TARGET := mvc2_gba_fan_edition
BUILD := build
LIBBUTANO := butano/butano
PYTHON := python3

SOURCES := src
INCLUDES := include
DATA :=
GRAPHICS :=
AUDIO :=
AUDIOBACKEND := maxmod
AUDIOTOOL :=
DMGAUDIO :=
DMGAUDIOBACKEND := default

ROMTITLE := MVC2 GBA FAN
ROMCODE := M2GF

USERFLAGS :=
USERCXXFLAGS := -std=gnu++17
USERASFLAGS :=
USERLDFLAGS :=
USERLIBDIRS :=
USERLIBS :=
DEFAULTLIBS :=
STACKTRACE :=
USERBUILD :=
EXTTOOL :=

ifndef LIBBUTANOABS
export LIBBUTANOABS := $(realpath $(LIBBUTANO))
endif

include $(LIBBUTANOABS)/butano.mak
