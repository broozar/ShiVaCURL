#################################################################
#   ShiVa Extension Plugin Makefile for Linux
#################################################################

#TARGET_ARCH			= X86_64 #TARGET_ARCH should be passed as command line argument
#################################################################
ifeq ($(TARGET_ARCH), X86_32)
    ARCH_PREFIX                 = x86_32
endif
ifeq ($(TARGET_ARCH), X86_64)
    ARCH_PREFIX                 = x86_64
endif
#################################################################

TEMP_DIR       		= ../../Temp/Linux/$(ARCH_PREFIX)
SRCROOT             = ../../Sources
FRAMEWORKSROOT      = ../../Frameworks/Linux
BUILT_PRODUCTS_DIR  = ../../Contents/Linux/$(ARCH_PREFIX)
PRODUCT_NAME        = ScURL2.so

#################################################################
SOURCES				= \
Plugin.cpp \
scurl.cpp

#################################################################
#  Compiler executables
#
CC      			= gcc
CPP     			= g++
LD					= $(CPP)


####################################################################
#  Compiler flags
#


ifeq ($(TARGET_ARCH), X86_32)
    ARCH_FLAGS      			= -m32 -msse -D__x86_32__
    ARCH_LIBS       			= -L../../Frameworks/Linux/$(ARCH_PREFIX)/lib
endif
ifeq ($(TARGET_ARCH), X86_64)
    ARCH_FLAGS      			= -m64 -fPIC -D__x86_64__ 
    ARCH_LIBS       			= -L../../Frameworks/Linux/$(ARCH_PREFIX)/lib
endif

INCLUDES			= -I"$(SRCROOT)" -I$(SRCROOT)/Platforms/Linux -I../../Sources/S3DX -I../../Frameworks/Linux/include
CFLAGS_Common		= -Os -Wno-unknown-pragmas -fsigned-char -fno-exceptions -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H -DS3DX_DLL -D__LINUX__ -D_GNU_SOURCE -DHAVE_STDINT_H
CFLAGS      		= $(ARCH_FLAGS) $(CFLAGS_Common) $(INCLUDES)
CPPFLAGS    		= 
LDFLAGS    			= $(ARCH_FLAGS) $(ARCH_LIBS)

####################################################################
#  Objects
#
OBJECTS  			= \
	$(patsubst %.c,%.o,$(filter %.c,$(SOURCES))) \
	$(patsubst %.cc,%.o,$(filter %.cc,$(SOURCES))) \
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES)))

OBJECTS_ABS			= $(addprefix $(TEMP_DIR)/,$(OBJECTS))
PRODUCT_ABS         = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME)

####################################################################
#  Rules
#

$(TEMP_DIR)/%.o: $(SRCROOT)/%.c
	mkdir -p `dirname $@`
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

$(TEMP_DIR)/%.o: $(SRCROOT)/%.cpp
	mkdir -p `dirname $@`
	@echo Compiling $<
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

####################################################################
#  Targets
#
all: $(PRODUCT_ABS) 
	@cp -rp $(FRAMEWORKSROOT)/$(ARCH_PREFIX)/bin/. $(BUILT_PRODUCTS_DIR)
	@echo Done.

$(PRODUCT_ABS): $(OBJECTS_ABS)
	mkdir -p $(BUILT_PRODUCTS_DIR)
	@echo Linking $<
	$(LD) -shared -o $(PRODUCT_ABS) $(OBJECTS_ABS) $(LDFLAGS)

clean:
	rm -f $(PRODUCT_ABS) $(OBJECTS_ABS)
	@echo Done.
####################################################################
