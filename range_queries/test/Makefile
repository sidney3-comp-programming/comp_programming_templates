CC = clang++

SRC = rmq_test.cpp range_query_test.cpp
OBJS = $(SRC:.cpp=.o)

DEPS = rmq_test.hpp

OUTPUT = range_query_test
all: $(OUTPUT)

$(OUTPUT) : $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT)
%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $<
