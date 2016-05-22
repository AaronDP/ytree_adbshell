LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
NCURSESDIR=/data/local/tmp/lib
REGEXDIR=./find
LOCAL_SRC_FILES:= \
arc.c archive.c chgrp.c chmod.c chown.c clock.c color.c copy.c delete.c \
dirwin.c disp.c edit.c error.c execute.c filespec.c filewin.c freesp.c global.c \
group.c hex.c history.c init.c input.c keyhtab.c lha.c login.c main.c match.c mkdir.c \
mktime.c move.c passwd.c pipe.c print.c profile.c quit.c rar.c readtree.c rename.c rmdir.c \
rpm.c sort.c stat.c system.c tar.c termcap.c tilde.c usermode.c util.c view.c xmalloc.c \
zip.c zoo.c regex.c
LOCAL_C_INCLUDES += $(LOCAL_PATH) $(NCURSESDIR)/include 
LOCAL_CFLAGS += -O -DVI_KEYS -DCOLOR_SUPPORT -D_GNU_SOURCE -UHAVE_LOCALE_H
LOCAL_LDLIBS := -llog $(NCURSESDIR)/libncurses.a
LOCAL_STATIC_LIBRARIES += ncurses 
LOCAL_MODULE := ytree
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
DESTDIR     = /data/local/tmp
BINDIR      = $(DESTDIR)/xbin
MANDIR      = $(DESTDIR)/lib/share/man/man1
MANESDIR    = $(DESTDIR)/lib/share/man/es/man1
include $(BUILD_EXECUTABLE)

all:

#$(info $(shell (adb push ../libs/armeabi/ytree /data/local/tmp/xbin)))
