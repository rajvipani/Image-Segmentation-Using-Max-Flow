CXX      := g++
CXXFLAGS := `pkg-config --cflags opencv4`
LDFLAGS  := `pkg-config --libs opencv4`

build:
	$(CXX) $(CXXFLAGS) main.cpp $(LDFLAGS) -o main 


run: build
	./main rabbit.jpg

.PHONY: build run