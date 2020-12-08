CXX      := g++ -std=c++11
CXXFLAGS := -g `pkg-config --cflags opencv4` #-fsanitize=address 
LDFLAGS  := `pkg-config --libs opencv4` #-fsanitize=address 

build:
	$(CXX) $(CXXFLAGS) main.cpp $(LDFLAGS) -o main 


run: build
	./main rabbit.jpg

shared:
	$(CXX) $(CXXFLAGS) -fPIC -shared main.cpp $(LDFLAGS) -o main.so 

.PHONY: build run