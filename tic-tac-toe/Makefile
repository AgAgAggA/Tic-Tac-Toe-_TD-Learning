CXX := g++ 
TARGET := main
CXXFLAGS := -std=c++11 -O3 -Wall -Wextra
INCLUDE := src/include
SRC_DIRS := src\
			src/lib\
      src/lib/Game\
      src/lib/Agent\
	  src/lib/Play\
   src/lib/Train
      
SRCS := $(wildcard $(SRC_DIRS:=/*.cpp))
OBJS := $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDE) -MMD -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS) $(DEPS)

.PHONY: all clean
-include $(DEPS)