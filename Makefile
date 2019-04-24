
MAINC=main.cpp
OUT=main
OBJ1=show.o
OBJ2=readsenior.o
CPP2=readsenior.cpp
OBJ3=facedetect.o
CPP3=facedetect.cpp
OBJ4=eyedetect.o
CPP4=eyedetect.cpp
#默认
default: $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) victor.h
	g++ -g -std=c++11  $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(MAINC)  `pkg-config --cflags --libs opencv` -o $(OUT) -lpthread
	rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

#文件生成规则
$(OBJ2) :$(CPP2) Makefile victor.h
	g++ -c -std=c++11 $(CPP2) -o $(OBJ2) -g `pkg-config --cflags --libs opencv` 

cut :cutting.cpp Makefile
	g++ -std=c++11 cutting.cpp -o cut -g `pkg-config --cflags --libs opencv`

test :test.cpp Makefile
	g++ -std=c++11 test.cpp -o test -g `pkg-config --cflags --libs opencv`

show.o:show.cpp Makefile victor.h
	g++ -c -std=c++11 show.cpp -o show.o -g `pkg-config --cflags --libs opencv`

$(OBJ3): $(CPP3) victor.h
	g++ -c -std=c++11 $(CPP3) -o $(OBJ3) -g `pkg-config --cflags --libs opencv`
$(OBJ4): $(CPP4) Makefile victor.h
	g++ -c -std=c++11 $(CPP4) -o $(OBJ4) -g `pkg-config --cflags --libs opencv`

www:	victor.h Makefile www.cpp
	g++ -std=c++11 www.cpp -o www -g `pkg-config --cflags --libs opencv`
	 


#命令



