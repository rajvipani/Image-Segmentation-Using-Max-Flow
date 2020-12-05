CXX      := g++
CXXFLAGS := `pkg-config --cflags opencv4`
LDFLAGS  := `pkg-config --libs opencv4`

build:
	$(CXX) $(CXXFLAGS) main.cpp $(LDFLAGS) -o main 


run: build
	./main rabbit.jpg

shared:
	$(CXX) $(CXXFLAGS) -fPIC -shared main.cpp $(LDFLAGS) -o main.so 

.PHONY: build run