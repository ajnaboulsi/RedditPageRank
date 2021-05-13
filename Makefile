# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = 	main.o graph.o springembedder/springembedder.o springembedder/fdgraph.o util/util.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk

# specific target
TMP_OBJ := $(OBJS)
OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
OBJS += pagerank.o

# Purely pagerank target
pagerank: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@