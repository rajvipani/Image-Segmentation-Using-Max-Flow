CXX      := g++ -std=c++11
CXXFLAGS := `pkg-config --cflags opencv4`
LDFLAGS  := `pkg-config --libs opencv4`

build:
	$(CXX) $(CXXFLAGS) main.cpp ImageData.cpp EdmondKarp.cpp $(LDFLAGS) -o main 

shared:
	$(CXX) $(CXXFLAGS) -fPIC -shared EdmondK.cpp ImageData.cpp EdmondKarp.cpp $(LDFLAGS) -o main.so 

run: build
	./main rabbit.jpg

.PHONY: build run