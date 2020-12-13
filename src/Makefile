CXX      ?= g++ -std=c++11
CXXFLAGS ?= `pkg-config --cflags opencv4`
LDFLAGS  ?= `pkg-config --libs opencv4`

build:
	$(CXX) $(CXXFLAGS) main.cpp ImageData.cpp PushRelabel.cpp EdmondKarp.cpp $(LDFLAGS) -o main 


push:
	$(CXX) $(CXXFLAGS)  -fPIC -shared PushR.cpp ImageData.cpp PushRelabel.cpp EdmondKarp.cpp $(LDFLAGS) -o pushr.so 

edk:
	$(CXX) $(CXXFLAGS) -fPIC -shared EdmondK.cpp ImageData.cpp EdmondKarp.cpp $(LDFLAGS) -o edk.so 

run: build
	./main rabbit.jpg

.PHONY: build run