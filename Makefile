SRC= \
  src/*.cpp \
  src/Components/*.cpp \
  src/Core/*.cpp \
  src/Utils/*.cpp  

EXE_NAME=engine.exe
# Directories
EXTERNAL_FILES=dependencies

LIB_FILES=$(EXTERNAL_FILES)\libs
DLL_FILES=$(EXTERNAL_FILES)\dlls
INCLUDE_FILES=$(EXTERNAL_FILES)\includes
EXTERN_FILES=$(EXTERNAL_FILES)\extern\*.cpp
MODEL_FILES=$(EXTERNAL_FILES)\Models

OUT_FOLDER=out
RELEASE_FOLDER=Release

#Flags
CFLAGS=/DGLEW_STATIC /MD /I$(INCLUDE_FILES) /Isrc\Headers /EHsc  
LDFLAGS=opengl32.lib $(LIB_FILES)\SDL2maind.lib $(LIB_FILES)\SDL2d.lib $(LIB_FILES)\glew32s.lib $(LIB_FILES)\SOIL.lib
LINKFLAGS=/NODEFAULTLIB:LIBCMTD /SUBSYSTEM:CONSOLE /NODEFAULTLIB:MSVCRTD /NODEFAULTLIB:LIBCMT 
DEBUGFLAGS=/DDEBUGMODE /DEBUG:FULL /ZI

all: engine.exe

engine.exe: copy
	cl $(CFLAGS) $(DEBUGFLAGS) $(EXTERN_FILES) $(SRC) $(LDFLAGS) /Fo$(OUT_FOLDER)\ /Fe$(OUT_FOLDER)\$(EXE_NAME) /link $(LINKFLAGS)

copy:
	if not exist $(OUT_FOLDER)\NUL mkdir $(OUT_FOLDER)\ 
	
	copy /y $(DLL_FILES)\* $(OUT_FOLDER)\ 

#makelib:
#	if not exist LIBOUT\NUL mkdir LIBOUT\ 
#
#	LIB.EXE /OUT:LIBOUT\gameEngine.lib Release\*.obj
clean:
	rd /q /s out