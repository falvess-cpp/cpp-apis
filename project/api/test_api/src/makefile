
include ../../make_api.inc

CC = /usr/bin/gcc
INCS = -I/home/falvess/FABIANO/repo/cpp-apis/project/core/src/cpplib
LDFLAGS = -L/usr/lib -lstdc++ -lm \
			-L/home/falvess/FABIANO/repo/cpp-apis/project/core/lib -lfscore

# Directory to put the objects
OBJ_DIR = obj

# Object files
OBJS = $(OBJ_DIR)/testMain.o \
	$(OBJ_DIR)/testImpl.o \
	$(OBJ_DIR)/testProcessor.o	
#OBJS = $(OBJ_DIR)/testMain.o testImpl.o testProcessor.o

MODULE = $(TESTAPI)/bin/TEST
all: $(MODULE)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(INCS) -c $< -o $@

# link
$(MODULE): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# pull in dependency info for *existing* .o files
-include $($(OBJ_DIR):.o=$(OBJ_DIR)/.d)

clean:
	rm -f $(OBJ_DIR)/*.o $(TESTAPI)/bin/TEST
	
#Non-File Targets
.PHONY: tes remake clean cleaner resources	
