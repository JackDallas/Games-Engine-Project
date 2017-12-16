SRC= \
  src/*.cpp\
  src/Components/*.cpp \
  src/Core/*.cpp \
  src/Utils/*.cpp  

CFLAGS=/DGLEW_STATIC /DFREEGLUT_LIB_PRAGMAS=0 /MD /Iinclude /Isrc\Headers
CXXFLAGS=/EHsc
LDFLAGS=opengl32.lib lib\freeglut.lib lib\glew.lib lib\SOIL.lib
LINKFLAGS=/link /NODEFAULTLIB:LIBCMTD
DEBUGFLAGS= /DDEBUGMODE

all: engine.exe

engine.exe: copy
	cl $(CFLAGS) $(DEBUGFLAGS) $(CXXFLAGS) $(SRC) $(LDFLAGS) /FoDebug\ /FeDebug\engine.exe $(LINKFLAGS)

copy:
	if not exist Debug\NUL mkdir Debug\ 

	if not exist Debug\Shaders\NUL mkdir Debug\Shaders\ 

	if not exist Debug\Models\NUL mkdir Debug\Models\ 

	del /q Debug\Shaders\* 
	
	copy /y src\Shaders\* Debug\Shaders\ 
	copy /y dlls\* Debug\ 
	copy /y Models\* Debug\Models\ 

release:
	if not exist Release\NUL mkdir Release\ 

	if not exist Release\Shaders\NUL mkdir Release\Shaders\ 

	if not exist Release\Models\NUL mkdir Release\Models\ 

	del /q Release\Shaders\* 
	
	copy /y src\Shaders\* Release\Shaders\ 
	copy /y dlls\* Release\ 
	copy /y Models\* Release\Models\ 

	cl $(CFLAGS) $(CXXFLAGS) $(SRC) $(LDFLAGS) /FoRelease\ /FeRelease\engine.exe $(LINKFLAGS)

makelib:
	if not exist LIBOUT\NUL mkdir LIBOUT\ 

	LIB.EXE /OUT:LIBOUT\gameEngine.lib Release\*.obj

clean:
	del /q Debug\Shaders\

	del /q Debug\Models\
	
	del /q Debug\*