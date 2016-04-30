## A Makefile for FlashPhoto
# Created by CSCI3081W Guru
# Copyright (c) CSCI3081W Guru. All rights reserved.

UNAME = $(shell uname)
CC 		= g++
CFLAGS 	= -g -c -Wall
LDFLAGS = -g



ifeq ($(UNAME), Darwin) # Mac OSX 
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = FlashPhoto
else # LINUX
	LINK_LIBS +=  -lglut -lGL -lGLU
	EXECUTABLE = FlashPhoto
endif

GLUI = glui
PNG = png
JPEG = jpeg

GLUI_PATH = ./glui
JPEG_PATH = ./jpeg-9a
PNG_PATH = ./libpng-1.6.16

GLUI_LIB = $(GLUI_PATH)/lib/lib$(GLUI).a
PNG_LIB = $(PNG_PATH)/lib/lib$(PNG).a
JPEG_LIB = $(JPEG_PATH)/lib/lib$(JPEG).a


INCLUDE += -I$(GLUI_PATH)/include 
INCLUDE += -I$(PNG_PATH)/include
INCLUDE += -I$(JPEG_PATH)/include


OBJECT_DIR = object_files
SOURCE_DIR = src

LINK_LIBS +=  -L$(GLUI_PATH)/lib/ -l$(GLUI) 
LINK_LIBS +=  -L$(PNG_PATH)/lib/ -l$(PNG)
LINK_LIBS +=  -L$(JPEG_PATH)/lib/ -l$(JPEG) 
LINK_LIBS +=  -lz

# Include nvidia drivers if necessary:
#NVIDIA_LIB =  /usr/lib/nvidia-304 #or whichever nvidia number shows up in that dir
ifneq ($(NVIDIA_LIB), )
	LINK_LIBS += -L$(NVIDIA_LIB)
endif

OBJECTS = $(addprefix $(OBJECT_DIR)/,  $(FILENAMES:.cpp=.o)) 
CPPFILES = $(wildcard $(SOURCE_DIR)/*.cpp)
FILENAMES =  $(notdir $(CPPFILES))







build: setup $(EXECUTABLE)

rebuild: clean build

# Create the object_files directory only if it does not exist. 
setup: | $(OBJECT_DIR)

$(OBJECT_DIR): 
	mkdir -p $(OBJECT_DIR)

$(EXECUTABLE): $(GLUI_LIB) $(PNG_LIB) $(JPEG_LIB) $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINK_LIBS) -o $@

# Explicitly defined build targets because of dependancy on other header files
$(OBJECT_DIR)/FlashPhoto.o: $(SOURCE_DIR)/FlashPhoto.cpp $(SOURCE_DIR)/FlashPhoto.h $(SOURCE_DIR)/ColorData.h $(SOURCE_DIR)/PixelBuffer.h
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/PixelBuffer.o: $(SOURCE_DIR)/PixelBuffer.cpp $(SOURCE_DIR)/PixelBuffer.h $(SOURCE_DIR)/ColorData.h 
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/ToolFactory.o: $(SOURCE_DIR)/ToolFactory.cpp $(SOURCE_DIR)/ToolFactory.h \
	$(SOURCE_DIR)/ColorData.h $(SOURCE_DIR)/Tool.h  $(SOURCE_DIR)/TPen.h $(SOURCE_DIR)/TEraser.h  \
	$(SOURCE_DIR)/TCalligraphyPen.h $(SOURCE_DIR)/THighlighter.h $(SOURCE_DIR)/TSprayCan.h 
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

# Pattern build targets
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.h
	#'Compiling arbitrary .cpp file with .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	#'Compiling arbitrary .cpp file without .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

clean:
	\rm -rf $(OBJECT_DIR) $(EXECUTABLE) 

cleanall: clean cleanglui cleanjpeg cleanpng

cleanglui:	
	$(MAKE)  -C ./$(GLUI_PATH)/ clean

cleanjpeg:
	$(MAKE) -C ./$(JPEG_PATH) distclean
	cd $(JPEG_PATH); \
	rm -rf lib bin include share

cleanpng:
	$(MAKE) -C ./$(PNG_PATH) distclean
	cd $(PNG_PATH); \
	rm -rf lib bin include share

$(GLUI_LIB): 
	$(MAKE) -C $(GLUI_PATH) all

$(PNG_LIB):
	cd $(PNG_PATH); \
	./configure --enable-shared=no  --prefix=$(abspath $(PNG_PATH))
	$(MAKE) -C $(PNG_PATH)
	$(MAKE) -C $(PNG_PATH) check
	$(MAKE) -C $(PNG_PATH) install

$(JPEG_LIB): 
	cd $(JPEG_PATH); \
	./configure --enable-shared=no --prefix=$(abspath $(JPEG_PATH))
	$(MAKE) -C $(JPEG_PATH)
	$(MAKE) -C $(JPEG_PATH) check
	$(MAKE) -C $(JPEG_PATH) install
