TEST_MAIN = pa3

OBJS_TRITREE = tritree.o tritree-given.o
OBJS_MAIN = main.o
OBJS_UTILS  = lodepng.o RGBAPixel.o PNG.o

INCLUDE_TRITREE = tritree.h
INCLUDE_UTILS = cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -lpthread -lm

all: $(TEST_MAIN) $(TEST_TRITREE)

$(TEST_MAIN) : $(OBJS_UTILS) $(OBJS_TRITREE) $(OBJS_MAIN)
	$(LD) $^ $(LDFLAGS) -o $@

main.o : main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Pattern rules for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp $(INCLUDE_UTILS)
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean:
	rm -rf $(TEST_MAIN) $(OBJS_DIR) *.o
