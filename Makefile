all:
	g++ main.cpp GUI.cxx LIQR_Layer.cpp LIQR_Receiver.cpp LIQR_Spectroscope.cpp SpectreDrawer.cpp -o LIQR -lrtlsdr -lsdl2 -lfftw3 -lfltk
	./LIQR
