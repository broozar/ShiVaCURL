#################################################################
#   ShiVa Extension Plugin Makefile for HTML5
#################################################################


TEMP_DIR       		= ../../Temp/HTML5
SRCROOT             = ../../Sources
BUILT_PRODUCTS_DIR  = ../../Contents/HTML5
PRODUCT_NAME        = ScURL2.bc
FRAMEWORKSROOT      = ../../Frameworks/HTML5

EMSCRIPTEN_PATH		= $(EMSCRIPTEN)

#################################################################
SOURCES				= \
Plugin.cpp\
scurl.cpp

####################################################################
#  Compiler flags
#

INCLUDES			= -I"$(SRCROOT)" -I$(SRCROOT)/Platforms/HTML5 -I../../Sources/S3DX -I$(FRAMEWORKSROOT)/include
EMCC_FLAGS			= -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -W -fno-strict-aliasing -Wno-unused-parameter -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -D__HTML5__ -DHAVE_DLFCN_H -D_GNU_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H
EMCC_CC_OPT_FLAGS	=  -O0 --llvm-opts "[ '-constprop', '-deadargelim', '-prune-eh', '-memdep', '-licm', '-die', '-dse', '-adce', '-gvn', '-globalopt', '-globaldce', '-loop-unswitch', '-no-aa', '-tbaa', '-targetlibinfo', '-basicaa', '-domtree', '-simplifycfg', '-sroa', '-early-cse', '-lower-expect', '-loops', '-loop-simplify', '-constmerge', '-functionattrs', '-instcombine', '-verify']"
EMCC_LD_OPT_FLAGS	=  -O2

#################################################################
#  Compiler executables
#
CC                  = "$(EMSCRIPTEN_PATH)/emcc" $(EMCC_FLAGS) $(EMCC_CC_OPT_FLAGS) $(INCLUDES)
CPP                 = "$(EMSCRIPTEN_PATH)/emcc" $(EMCC_FLAGS) $(EMCC_CC_OPT_FLAGS) $(INCLUDES) -std=c++98
LD                  = "$(EMSCRIPTEN_PATH)/emcc" $(EMCC_FLAGS) $(EMCC_LD_OPT_FLAGS)


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
	$(CC) -c $< -o $@

$(TEMP_DIR)/%.o: $(SRCROOT)/%.cc
	mkdir -p `dirname $@`
	@echo Compiling $<
	$(CC) -c $< -o $@

$(TEMP_DIR)/%.o: $(SRCROOT)/%.cpp
	mkdir -p `dirname $@`
	@echo Compiling $<
	$(CPP) -c $< -o $@

####################################################################
#  Targets
#
all: $(PRODUCT_ABS)
	@cp -rp $(FRAMEWORKSROOT)/bin/. $(BUILT_PRODUCTS_DIR)
	chmod 755 $(PRODUCT_ABS)
	@echo Done.

$(PRODUCT_ABS): $(OBJECTS_ABS)
	mkdir -p $(BUILT_PRODUCTS_DIR)
	$(LD)  -o $(PRODUCT_ABS) $(OBJECTS_ABS)

clean:
	rm -f $(PRODUCT_ABS) $(OBJECTS_ABS)
	@echo Done.
####################################################################
