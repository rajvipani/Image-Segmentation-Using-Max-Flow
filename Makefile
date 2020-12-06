CXX      :=  g++ -std=c++11
CXXFLAGS := `pkg-config --cflags opencv4`
LDFLAGS  := `pkg-config --libs opencv4`

build:
	cd src && make shared
	cd gui && make shared

run: build
	cd gui && python3 gui.py

.PHONY: build run