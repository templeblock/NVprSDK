
TARGET = nvpr_warp_tiger

UNAME := $(shell uname)

CSRCS = \
  ../common/nvpr_glew_init.c \
  ../common/tiger.c \
  ../common/showfps.c \
  ../common/request_vsync.c \
  ../glew/src/glew.c \
  $(NULL)
CPPSRCS = $(TARGET:=.cpp) \
  ../common/cg4cpp_xform.cpp \
  ../cg4cpp/src/inverse.cpp \
  $(NULL)
OBJS = $(CSRCS:.c=.o) $(CPPSRCS:.cpp=.o)

CC = gcc
CXX = g++
CFLAGS += -Wall
ifdef RELEASE
CFLAGS += -O2
else
CFLAGS += -g
endif
CFLAGS += -I../common
CFLAGS += -I../cg4cpp/include
CFLAGS += -I../glew/include

ifeq ($(UNAME), Darwin)
  CLINKFLAGS += -framework OpenGL -framework GLUT
else
  GLUT_DIR := ../glut/lib/glut
  GLUT_LIB := $(GLUT_DIR)/libglut.a
  ifeq ($(findstring CYGWIN, $(UNAME)), CYGWIN)
    CFLAGS += -D_WIN32 -DGLUT_DISABLE_ATEXIT_HACK -DGLEW_STATIC
    # Cg Toolkit includes <GL/glut.h>
    CFLAGS += -I"C:\Program Files\NVIDIA Corporation\Cg\include"
    CLINKFLAGS += -lglut32 -lglu32 -lopengl32
    EXE = .exe
  else
    CLINKFLAGS += -L$(GLUT_DIR)
    CLINKFLAGS += -L/usr/X11R6/lib64 -L/usr/X11R6/lib
    CLINKFLAGS += -lglut -lGLU -lGL -lXi -lXmu -lX11 -lm -lpthread
  endif
endif

CXXFLAGS=$(CFLAGS)

BINARY := $(TARGET:=$(EXE))

all: $(BINARY)

run: $(TARGET)$(EXE)
	./$(TARGET)$(EXE)

release:
	$(MAKE) RELEASE=1

$(BINARY) : $(GLUT_LIB) $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS) $(CLINKFLAGS)

clean:
	$(RM) $(BINARY) $(OBJS)

RMDIR = -rm -rf
clobber: clean
	$(RM) *.bak *.o *~
	$(RMDIR) Release/ Debug/

$(GLUT_LIB): FORCEglut
	$(MAKE) -C '$(GLUT_DIR)' -f GNUmakefile

.PHONY: clean clobber release run FORCEglut
