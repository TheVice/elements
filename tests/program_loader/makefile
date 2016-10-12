all: test

# Source files for target test
SOURCES = \
	../../elements/assets/asset_xml.cpp \
	../../elements/assets/assets_storage.cpp \
	../../elements/rendering/core/program.cpp \
	../../elements/rendering/core/shader.cpp \
	../../elements/rendering/utils/program_loader.cpp \
	test_program_loader.cpp

# Object files for target test
OBJECTS = \
	asset_xml.o \
	assets_storage.o \
	program.o \
	shader.o \
	program_loader.o \
	test_program_loader.o

test: test_objects
	g++ -o test $(OBJECTS) -lGL -lGLU -lpugixml

test_objects:
	g++ -I../../elements -std=c++14 -Wall -Wextra -Werror -c $(SOURCES)

clean:
	 rm $(OBJECTS) test

