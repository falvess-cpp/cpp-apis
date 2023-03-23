
include ../../make_api.inc

CC = /usr/bin/gcc
INCS = -I/home/ubuntu/fabiano/cpp-apis/project/core/src/cpplib
LDFLAGS = -L/usr/lib -lstdc++ -lm -pthread -lpthread\
			-L/home/ubuntu/fabiano/cpp-apis/project/core/lib -lfscore

# Directory to put the objects
OBJ_DIR = obj

# Object files
OBJS = $(OBJ_DIR)/Main.o  \
	$(OBJ_DIR)/threadImpl.o	

MODULE = $(THREAD_IMP)/bin/THREAD_IMP
all: $(MODULE)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(INCS) -c $< -o $@

# link
$(MODULE): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# pull in dependency info for *existing* .o files
-include $($(OBJ_DIR):.o=$(OBJ_DIR)/.d)

clean:
	rm -f $(OBJ_DIR)/*.o $(THREAD_IMP)/bin/THREAD_IMP
	
#Non-File Targets
.PHONY: tes remake clean cleaner resources	
