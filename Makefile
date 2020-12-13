CXX      :=  g++ -std=c++11
CXXFLAGS := `pkg-config --cflags opencv4`
LDFLAGS  := `pkg-config --libs opencv4`

CXXFLAGS_SCC := "-I/share/pkg.7/opencv/4.0.1/install/include/opencv4/opencv2 -I/share/pkg.7/opencv/4.0.1/install/include/opencv4"
LDFLAGS_SCC  := "-lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_highgui -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_shape -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_ml -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core"

build:
	cd src && make edk
	cd src && make push
	cd gui && make shared

run: build
	cd gui && python3 gui.py

run_scc:
	cd src && make edk CXXFLAGS=$(CXXFLAGS_SCC) LDFLAGS=$(LDFLAGS_SCC)
	cd src && make push CXXFLAGS=$(CXXFLAGS_SCC) LDFLAGS=$(LDFLAGS_SCC)
	cd gui && make shared CXXFLAGS=$(CXXFLAGS_SCC) LDFLAGS=$(LDFLAGS_SCC)
	cd gui && python3 gui.py

.PHONY: build run