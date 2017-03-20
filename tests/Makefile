# Name of the executable to create
EXECUTABLE = TestingSuiteDeluxe
SOURCE_DIR = src
OBJECT_DIR = build

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

LIB_PHOTO_PATH = ../libphoto
INCLUDE += -I$(LIB_PHOTO_PATH)/include
LINK_LIBS += -L$(LIB_PHOTO_PATH)/lib/ -lphoto
PHOTO_LIB = $(LIB_PHOTO_PATH)/lib/libphoto.a

GLUI_PATH = ../glui
INCLUDE += -I$(GLUI_PATH)/include
LINK_LIBS +=  -L$(GLUI_PATH)/lib/ -lglui -lpthread
GLUI_LIB = $(GLUI_PATH)/lib/libglui.a

LIBPNG_PATH =  ../libpng
INCLUDE += -I$(LIBPNG_PATH)/include
LINK_LIBS += -L$(LIBPNG_PATH)/lib/ -lpng -lz
PNG_LIB  = $(LIBPNG_PATH)/lib/libpng.a

LIBJPEG_PATH =  ../libjpeg
INCLUDE += -I$(LIBJPEG_PATH)/include
LINK_LIBS += -L$(LIBJPEG_PATH)/lib/ -ljpeg
JPEG_LIB  = $(LIBJPEG_PATH)/lib/libjpeg.a

# For graphics support, we also need to link with the Glut and OpenGL libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX 
	LINK_LIBS += -framework glut -framework opengl
else # LINUX
	LINK_LIBS += -lglut -lGL -lGLU
endif

ifneq ($(NVIDIA_LIB), )
	LINK_LIBS += -L$(NVIDIA_LIB)
endif


# Testing makefile
# Comments above targets indicate the desired behavior

all: start help comparefail1 comparefail2 comparesucceed1 comparesucceed2 filterfailure1 filtersuccess1 convertsuccess test_directory test_sharpen test_edgedetect test_quantize test_thresh test_saturate test_blur test_multrgb setup $(EXECUTABLE) test_pen test_calligraphy test_highlighter test_eraser test_blurtool test_spraycan test_specialtool test_stamptool

#all: setup $(EXECUTABLE)

rebuild: clean all

start:
	echo "Beginning command line testing..."

# Create the object_files directory only if it does not exist. 
setup: | $(OBJECT_DIR)

# Display help menu
help:
	echo "Test 1: mia -h ..."
	cd ../Mia; ./mia -h

$(OBJECT_DIR): 
	mkdir -p $(OBJECT_DIR)

$(EXECUTABLE): $(OBJFILES) $(PHOTO_LIB) $(GLUI_LIB) $(JPEG_LIB) $(PNG_LIB) 
	$(CC) $(LDFLAGS) $(OBJFILES) $(LINK_LIBS) -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

clean:
	\rm -rf $(OBJECT_DIR) $(EXECUTABLE)

# Failed to execute command: Invalid image in.jpg
comparefail1:
	echo "Test 2: mia -compare with invalid image (Expected: Failed to execute command: invalid image in.jpg)"
	cd ../Mia; ./mia in.jpg -compare out.jpg

# 0
comparefail2:
	echo "Test 3: mia -compare with different images (Expected: 0)"
	cd ../Mia; ./mia ../tests/nat.jpg -compare ../tests/nat_multrgb_test.jpg

# 1
comparesucceed1:
	echo "Test 4: mia -compare with same image (Expected: 1)"
	cd ../Mia; ./mia ../tests/nat.jpg -compare ../tests/nat.jpg

# 1
comparesucceed2:
	echo "Test 5: mia -compare with different images (Expected: 1)"
	cd ../Mia; ./mia ../tests/nat.jpg -compare ../tests/nat_copy.jpg

# Failed to execute command: saturate requires a float amount
filterfailure1:
	echo "Test 6: mia nat.jpg -saturate number nat_filtered.jpg (Expected: Failed to execute command: saturate requires a float amount)"
	cd ../Mia; ./mia ../tests/nat.jpg -saturate number ../tests/nat_wacky_test.jpg

# 1
filtersuccess1:
	echo "Test 7: mia nat.jpg -saturate 0.1 -multrgb 0.75,0.75,0.0 -edgedetect natwacky.jpg"
	cd ../Mia; ./mia ../tests/nat.jpg -saturate 0.1 -multrgb 0.75,0.75,0.0 -edgedetect ../tests/nat_wacky.jpg; ./mia ../tests/nat_wacky.jpg -compare ../tests/nat_wacky_test.jpg

# 1
convertsuccess:
	echo "Test 8: Convert jpg to png (Expected: 1)"
	cd ../Mia; ./mia ../tests/nat.jpg ../tests/nat_new.png; ./mia ../tests/nat_new.png -compare ../tests/nat.png

test_directory:
	echo "Test 9: Filter all files in a directory (Expected: Two 1s)"
	cd ../Mia; ./mia ../tests/directory -saturate 0.75 ../tests/directory_new; ./mia ../tests/nat_saturate_test.jpg -compare ../tests/directory_new/nat1.jpg; ./mia ../tests/nat_saturate_test.jpg -compare ../tests/directory_new/nat2.jpg;

# 1
test_sharpen:
	echo "Filter Tests (Expected Output: 1) ..."
	echo "Filter Test 1: sharpen"
	cd ../Mia; ./mia ../tests/nat.jpg -sharpen 5 ../tests/nat_sharpen.jpg; ./mia ../tests/nat_sharpen.jpg -compare ../tests/nat_sharpen_test.jpg

# 1
test_edgedetect:
	echo "Filter Test 2: edgedetect"
	cd ../Mia; ./mia ../tests/nat.jpg -edgedetect ../tests/nat_edgedetect.jpg; ./mia ../tests/nat_edgedetect.jpg -compare ../tests/nat_edgedetect_test.jpg

# 1
test_quantize:
	echo "Filter Test 3: quantize"
	cd ../Mia; ./mia ../tests/nat.jpg -quantize 3 ../tests/nat_quantize.jpg; ./mia ../tests/nat_quantize.jpg -compare ../tests/nat_quantize_test.jpg

# 1
test_thresh:
	echo "Filter Test 4: thresh"
	cd ../Mia; ./mia ../tests/nat.jpg -thresh 0.5 ../tests/nat_thresh.jpg; ./mia ../tests/nat_thresh.jpg -compare ../tests/nat_thresh_test.jpg

# 1
test_saturate:
	echo "Filter Test 5: saturate"
	cd ../Mia; ./mia ../tests/nat.jpg -saturate 0.75 ../tests/nat_saturate.jpg; ./mia ../tests/nat_saturate.jpg -compare ../tests/nat_saturate_test.jpg

# 1
test_blur:
	echo "Filter Test 6: blur"
	cd ../Mia; ./mia ../tests/nat.jpg -blur 4.0 ../tests/nat_blur.jpg; ./mia ../tests/nat_blur.jpg -compare ../tests/nat_blur_test.jpg

# 1
test_multrgb:
	echo "Filter Test 7: multrgb"
	cd ../Mia; ./mia ../tests/nat.jpg -multrgb 0.1,0.7,0.0 ../tests/nat_multrgb.jpg; ./mia ../tests/nat_multrgb.jpg -compare ../tests/nat_multrgb_test.jpg

test_pen:
	echo "Tool Tests"
	echo "Tool Test 1 - Pen"
	./TestingSuiteDeluxe pen PenCmds.txt pen_base.jpg

test_calligraphy:
	echo "Tool Test 2 - Calligraphy"
	./TestingSuiteDeluxe caligraphy CaligraphyCmds.txt caligraphy_base.jpg

test_highlighter:
	echo "Tool Test 3 - Highlighter"
	./TestingSuiteDeluxe highlighter HighlighterCmds.txt highlighter_base.jpg

test_eraser:
	echo "Tool Test 4 - Eraser"
	./TestingSuiteDeluxe eraser EraserCmds.txt eraser_base.jpg

test_blurtool:
	echo "Tool Test 5 - Blur Tool"
	./TestingSuiteDeluxe blur BlurCmds.txt blur_base.jpg

test_spraycan:
	echo "Tool Test 6 - Spray Can"
	./TestingSuiteDeluxe spray SprayCmds.txt spray_base.jpg

test_specialtool:
	echo "Tool Test 7 - Special Tool"
	./TestingSuiteDeluxe special SpecialCmds.txt special_base.jpg

test_stamptool:
	echo "Tool Test 8 - Blur Tool"
	./TestingSuiteDeluxe stamp StampCmds.txt stamp_base.jpg




