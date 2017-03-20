### Definitions Section ###

# Name of the executable to create
SOURCE_DIR = src
OBJECT_DIR = build
LIB_DIR    = lib 
PHOTOLIB_INCLUDE = include


# Define the list of files to compile for this project. Defaults to all
# of the .cpp files in the source directory.
CPPFILES = $(wildcard $(SOURCE_DIR)/*.cpp)

# For each of the .cpp files found above, determine the name of the 
# corresponding .o file to create.
OBJFILES = $(addprefix $(OBJECT_DIR)/,  $(notdir $(CPPFILES:.cpp=.o)))

# The command to run for the C++ compiler and linker
CC = g++

# Basic C++ compiler arguments
CFLAGS = -g -c -Wall

# Basic C++ linker arguments
LDFLAGS = -g

# We use the GLUI library for our graphical user interface.  So, we
# also need to add compiler and linker arguments for GLUI.
GLUI_PATH = ../glui
INCLUDE += -I$(GLUI_PATH)/include
GLUI_LIB = $(GLUI_PATH)/lib/libglui.a

LIBPNG_PATH =  ../libpng
INCLUDE += -I$(LIBPNG_PATH)/include
PNG_LIB  = $(LIBPNG_PATH)/lib/libpng.a

LIBJPEG_PATH =  ../libjpeg
INCLUDE += -I$(LIBJPEG_PATH)/include
JPEG_LIB  = $(LIBJPEG_PATH)/lib/libjpeg.a

PHOTO_LIB = lib/libphoto.a
INCLUDE += -I$(PHOTOLIB_INCLUDE)

# For graphics support, we also need to link with the Glut and OpenGL libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX 
	LINK_LIBS += -framework glut -framework opengl
else # LINUX
	LINK_LIBS += -lglut -lGL -lGLU
endif

# On some lab machines the glut and opengl libraries are located in the directory
# where the nvidia graphics driver was installed rather than the default /usr/lib
# directory.  In this case, we need to tell the linker to search this nvidia directory
# for libraries as well.  Uncomment the line below.
#NVIDIA_LIB =  /usr/lib/nvidia-304  #or whichever nvidia driver number shows up in that dir
ifneq ($(NVIDIA_LIB), )
	LINK_LIBS += -L$(NVIDIA_LIB)
endif



### Rules Section ###

# Note, other than each .o depending upon a corresponding .cpp there is no automatic 
# dependency checking here.  You can add individual dependency rules for .h files
# (e.g., build/ColorData.o:  src/ColorData.h src/SomethingElse.h) by hand if you want
# or just remember to run "make rebuild" if you change a .h file.

all:$(GLUI_LIB) $(JPEG_LIB) $(PNG_LIB) setup $(PHOTO_LIB)

rebuild: clean all

# Create the object_files directory only if it does not exist. 
setup: | $(OBJECT_DIR)

$(OBJECT_DIR): 
	mkdir -p $(OBJECT_DIR)
	mkdir -p $(LIB_DIR)

$(PHOTO_LIB): $(OBJFILES) 
	ar rcs $(PHOTO_LIB) $(OBJFILES) 

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(GLUI_LIB): 
	$(MAKE) -C $(GLUI_PATH) all

$(JPEG_LIB):
	cd $(LIBJPEG_PATH); ./configure --prefix=$(abspath $(LIBJPEG_PATH)) --enable-shared=no
	$(MAKE) -C $(LIBJPEG_PATH) 
	$(MAKE) -C $(LIBJPEG_PATH) check
	$(MAKE) -C $(LIBJPEG_PATH) install

$(PNG_LIB):
	cd $(LIBPNG_PATH); ./configure --prefix=$(abspath $(LIBPNG_PATH)) --enable-shared=no
	$(MAKE) -C $(LIBPNG_PATH) 
	$(MAKE) -C $(LIBPNG_PATH) check
	$(MAKE) -C $(LIBPNG_PATH) install
	$(MAKE) clean
	$(MAKE)

clean:
	\rm -rf $(OBJECT_DIR) $(LIB_DIR)



