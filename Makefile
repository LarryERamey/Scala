TARGET = hikerTest

CPP = g++
LD = g++

CPPFLAGS = -g -fPIC
LDFLAGS += -lyaml-cpp

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

OBJS_PATH = $(patsubst %.cpp,%.o,$(wildcard $(SRC_DIR)/*.cpp))
OBJ_FILES = $(foreach file, $(OBJS_PATH),$(notdir ${file}))
OBJECTS = $(foreach file, $(OBJ_FILES),$(addprefix $(OBJ_DIR)/,${file}))

.PHONY: default all clean

default: build $(TARGET)

all: build $(SOURCES) $(OBJS) $(TARGET)

build:
	-@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -c $< $(LIBS) -o $@
	@echo "CPP   -------------------- $<"

$(TARGET): $(OBJECTS)
	@echo $(OBJECTS)
	$(LD) $(OBJECTS) -g $(LIBS) $(LDFLAGS) -o $@
	@echo "LINK -------------------- $@"


clean:
	-@rm -f $(OBJ_DIR)/*.o
	-@rm -f $(TARGET)
	-@rm -f $(SRC_DIR)/*~
	-@rm -f $(INC_DIR)/*~
	-@rm -f core
	-@rm -f *.log



