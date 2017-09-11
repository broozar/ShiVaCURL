#################################################################
#   ShiVa Extension Plugin Makefile for Android
#################################################################

ANDROID_NDK_ROOT    = @@AndroidNDKPath@@
TEMP_DIR       		= ../../Temp/Android
TEMP_DIR_ARM5       = $(TEMP_DIR)/arm5
TEMP_DIR_ARM7       = $(TEMP_DIR)/arm7
TEMP_DIR_X86        = $(TEMP_DIR)/x86
SRCROOT             = ../../Sources
FRAMEWORKSROOT      = ../../Frameworks/Android
BUILT_PRODUCTS_DIR  = ../../Contents/Android
PRODUCT_NAME_ARM5   = arm_v5te/ScURL2.a
PRODUCT_NAME_ARM7   = arm_v7a/ScURL2.a
PRODUCT_NAME_X86    = x86_32/ScURL2.a

#################################################################
SOURCES				= \
Plugin.cpp \
scurl.cpp

#################################################################
#  Compiler executables
#
CC_ARM5      		= 
CPP_ARM5     		= 
AR_ARM5  			= 

CC_ARM7      		= $(CC_ARM5)
CPP_ARM7     		= $(CPP_ARM5)
AR_ARM7  			= $(AR_ARM5)

CC_X86      		= 
CPP_X86     		= 
AR_X86  			= 

####################################################################"
#  Includes
#
SYSROOT_ARM5        = $(ANDROID_NDK_ROOT)/platforms/android-9/arch-arm
SYSROOT_ARM7        = $(SYSROOT_ARM5)
SYSROOT_X86         = $(ANDROID_NDK_ROOT)/platforms/android-9/arch-x86
SYSTEM_INCLUDES		= 

####################################################################"
#  Compiler flags
#
CFLAGS_Arch_ARM5 	= -march=armv5te -msoft-float
CFLAGS_Arch_ARM7 	= -march=armv7-a -mfloat-abi=softfp -mfpu=vfp
CFLAGS_Arch_X86 	= 
CFLAGS_Common		= -Os -Wno-unknown-pragmas -fPIC -fsigned-char -fno-strict-aliasing -fno-short-enums -fno-exceptions -D__ANDROID__ -DANDROID_NDK -DANDROID -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H -D__ANDROID__ -DANDROID_NDK -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H
INCLUDES			= -I"$(SRCROOT)" -I$(SRCROOT)/Platforms/Android -I../../Sources/S3DX -I../../Sources/S3DX  -I../../Frameworks/Android/include
CFLAGS_ARM5      	= --sysroot="$(SYSROOT_ARM5)" $(CFLAGS_Arch_ARM5) $(CFLAGS_Common) $(SYSTEM_INCLUDES) -I$(INCLUDES) -I"$(SYSROOT_ARM5)/usr/include"
CFLAGS_ARM7      	= --sysroot="$(SYSROOT_ARM7)" $(CFLAGS_Arch_ARM7) $(CFLAGS_Common) $(SYSTEM_INCLUDES) -I$(INCLUDES) -I"$(SYSROOT_ARM7)/usr/include"
CFLAGS_X86       	= --sysroot="$(SYSROOT_X86)"  $(CFLAGS_Arch_X86)  $(CFLAGS_Common) $(SYSTEM_INCLUDES) -I$(INCLUDES) -I"$(SYSROOT_X86)/usr/include"
CPPFLAGS    		= -fno-rtti 


####################################################################"
#  Objects
#
OBJECTS  			= \
	$(patsubst %.c,%.o,$(filter %.c,$(SOURCES))) \
	$(patsubst %.cc,%.o,$(filter %.cc,$(SOURCES))) \
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES)))

OBJECTS_ABS_ARM5	= $(addprefix $(TEMP_DIR_ARM5)/,$(OBJECTS))
OBJECTS_ABS_ARM7	= $(addprefix $(TEMP_DIR_ARM7)/,$(OBJECTS))
OBJECTS_ABS_X86 	= $(addprefix $(TEMP_DIR_X86)/,$(OBJECTS))
PRODUCT_ABS_ARM5    = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME_ARM5)
PRODUCT_ABS_ARM7    = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME_ARM7)
PRODUCT_ABS_X86     = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME_X86)

####################################################################"
#  Rules
#

$(TEMP_DIR_ARM5)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC_ARM5) $(CFLAGS_ARM5) -c $< -o $@

$(TEMP_DIR_ARM5)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_ARM5) $(CFLAGS_ARM5) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_ARM5)/%.o: $(SRCROOT)/%.cc
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_ARM5) $(CFLAGS_ARM5) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_ARM7)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC_ARM7) $(CFLAGS_ARM7) -c $< -o $@

$(TEMP_DIR_ARM7)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_ARM7) $(CFLAGS_ARM7) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_ARM7)/%.o: $(SRCROOT)/%.cc
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_ARM7) $(CFLAGS_ARM7) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_X86)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC_X86) $(CFLAGS_X86) -c $< -o $@

$(TEMP_DIR_X86)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_X86) $(CFLAGS_X86) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_X86)/%.o: $(SRCROOT)/%.cc
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_X86) $(CFLAGS_X86) $(CPPFLAGS) -c $< -o $@

####################################################################"
#  Targets
#
all: $(PRODUCT_ABS_ARM5) $(PRODUCT_ABS_ARM7) $(PRODUCT_ABS_X86) 
	@echo Done.

$(PRODUCT_ABS_ARM5): $(OBJECTS_ABS_ARM5)
	@echo Creating ARM5 archive
	@mkdir -p $(BUILT_PRODUCTS_DIR)/arm_v5te/
	@chmod -R 775 $(BUILT_PRODUCTS_DIR)/arm_v5te/
	@$(AR_ARM5) rcs $(PRODUCT_ABS_ARM5) $(OBJECTS_ABS_ARM5)
	@find $(FRAMEWORKSROOT)/arm_v5te/lib -name "*.a" -type f -exec cp {} $(BUILT_PRODUCTS_DIR)/arm_v5te \;
	@cp -rp $(FRAMEWORKSROOT)/arm_v5te/bin/. $(BUILT_PRODUCTS_DIR)/arm_v5te

$(PRODUCT_ABS_ARM7): $(OBJECTS_ABS_ARM7)
	@echo Creating ARM7 archive
	@mkdir -p $(BUILT_PRODUCTS_DIR)/arm_v7a/
	@chmod -R 775 $(BUILT_PRODUCTS_DIR)/arm_v7a/
	@$(AR_ARM7) rcs $(PRODUCT_ABS_ARM7) $(OBJECTS_ABS_ARM7)
	@find $(FRAMEWORKSROOT)/arm_v7a/lib -name "*.a" -type f -exec cp {} $(BUILT_PRODUCTS_DIR)/arm_v7a \;
	@cp -rp $(FRAMEWORKSROOT)/arm_v7a/bin/. $(BUILT_PRODUCTS_DIR)/arm_v7a

$(PRODUCT_ABS_X86): $(OBJECTS_ABS_X86)
	@echo Creating X86 archive
	@mkdir -p $(BUILT_PRODUCTS_DIR)/x86_32/
	@chmod -R 775 $(BUILT_PRODUCTS_DIR)/x86_32/
	@$(AR_X86) rcs $(PRODUCT_ABS_X86) $(OBJECTS_ABS_X86)
	@find $(FRAMEWORKSROOT)/x86_32/lib -name "*.a" -type f -exec cp {} $(BUILT_PRODUCTS_DIR)/x86_32 \;
	@cp -rp $(FRAMEWORKSROOT)/x86_32/bin/. $(BUILT_PRODUCTS_DIR)/x86_32

clean:
	@echo Cleaning
	@rm -fR $(BUILT_PRODUCTS_DIR)/arm_v5te/
	@rm -fR $(BUILT_PRODUCTS_DIR)/arm_v7a/
	@rm -fR $(BUILT_PRODUCTS_DIR)/x86_32/
	@rm -f $(PRODUCT_ABS_ARM5) $(OBJECTS_ABS_ARM5) $(PRODUCT_ABS_ARM7) $(OBJECTS_ABS_ARM7) $(PRODUCT_ABS_X86) $(OBJECTS_ABS_X86)
	@echo Done.

####################################################################"
