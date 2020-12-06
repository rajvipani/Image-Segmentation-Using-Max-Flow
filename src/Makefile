CXX      := g++ -std=c++11
CXXFLAGS := `pkg-config --cflags opencv4`
LDFLAGS  := `pkg-config --libs opencv4`

build:
	$(CXX) $(CXXFLAGS) main.cpp ImageData.cpp EdmondKarp.cpp $(LDFLAGS) -o main 


run: build
	./main apple.png

shared:
	$(CXX) $(CXXFLAGS) -fPIC -shared EdmondK.cpp ImageData.cpp EdmondKarp.cpp $(LDFLAGS) -o main.so

.PHONY: build run