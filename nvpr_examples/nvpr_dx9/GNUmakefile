
TARGET = nvpr_dx9

UNAME := $(shell uname)

CSRCS = $(TARGET:=.c) \
  $(NULL)
CPPSRCS = 
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

ifeq ($(UNAME), Darwin)
  CLINKFLAGS += -framework OpenGL -framework GLUT
else
  ifeq ($(findstring CYGWIN, $(UNAME)), CYGWIN)
    CFLAGS += -D_WIN32 -DGLUT_DISABLE_ATEXIT_HACK
    # Cg Toolkit includes <GL/glut.h>
    CFLAGS += -I"C:\Program Files\NVIDIA Corporation\Cg\include"
    CLINKFLAGS += -lglut32 -lglu32 -lopengl32
    EXE = .exe
  else
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

$(BINARY) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(CLINKFLAGS)

clean:
	$(RM) $(BINARY) $(OBJS)

RMDIR = -rm -rf
clobber: clean
	$(RM) *.bak *.o *~
	$(RMDIR) Release/ Debug/

.PHONY: clean clobber release run
