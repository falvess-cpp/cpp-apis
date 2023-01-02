
include ../../cfg/make_core.inc

CC = /usr/bin/gcc
 
# Directory to put the objects
OBJ_DIR = obj

# Object files
OBJS = $(OBJ_DIR)/fsdate.o \
	$(OBJ_DIR)/fsexc.o \
	$(OBJ_DIR)/fslog.o	

MODULE = libfscore.so
all: $(MODULE)

# Convert cpp code to Object file
$(OBJ_DIR)/%.o: %.cpp
	$(CC) -c -fPIC $*.cpp -o $(OBJ_DIR)/$*.o
	
# pull in dependency info for *existing* .o files
-include $($(OBJ_DIR):.o=$(OBJ_DIR)/.d)	
	
# Create shared .SO library
$(MODULE): $(OBJS)
	$(CC) $(OBJS) -shared -o $(LIB_COREDIR)/$(MODULE)

clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_COREDIR)/*.so
	
#Non-File Targets
.PHONY: tes remake clean cleaner resources	
	