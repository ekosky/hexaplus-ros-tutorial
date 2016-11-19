CFLAGS =  -I../remoteApi -I../include  -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255

EXTAPI = ../remoteApi/extApi.o ../remoteApi/extApiPlatform.o fuzzy.o HexaPlus.o HexaPlusPanel.o HexaPlusKsMap.o navigation.o HexaPlusOutputPlotData.o

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	CFLAGS += -D__linux
else
	CFLAGS += -D__APPLE__
endif

all: 
	@rm -f bin/*.*
	@rm -f *.o
	gcc $(CFLAGS) -c ../remoteApi/extApi.c -o ../remoteApi/extApi.o
	gcc $(CFLAGS) -c ../remoteApi/extApiPlatform.c -o ../remoteApi/extApiPlatform.o
	gcc $(CFLAGS) -c fuzzy.cpp -o fuzzy.o
	gcc $(CFLAGS) -c HexaPlus.cpp -o HexaPlus.o
	gcc $(CFLAGS) -c HexaPlusPanel.cpp -o HexaPlusPanel.o
	gcc $(CFLAGS) -c HexaPlusKsMap.cpp -o HexaPlusKsMap.o
	gcc $(CFLAGS) -c navigation.cpp -o navigation.o
	gcc $(CFLAGS) -c HexaPlusOutputPlotData.cpp -o HexaPlusOutputPlotData.o
	gcc $(CFLAGS) -c HexaPlusMainCtrl.cpp -o HexaPlusMainCtrl.o
	@mkdir -p bin
	g++ $(EXTAPI) HexaPlusMainCtrl.o -o bin/HexaPlusMainCtrl -lpthread

surface:
	@rm -f bin/HexaPlus_CTL_SURFACE
	@rm -f fuzzy.o HexaPlusCS.o HexaPlus_CTL_SURFACE.o
	gcc -c $(CFLAGS) fuzzy.cpp -o fuzzy.o
	gcc -c $(CFLAGS) HexaPlusCS.cpp -o HexaPlusCS.o 
	gcc -c $(CFLAGS) HexaPlus_CTL_SURFACE.cpp -o HexaPlus_CTL_SURFACE.o
	g++ fuzzy.o HexaPlusCS.o HexaPlus_CTL_SURFACE.o -o bin/HexaPlus_CTL_SURFACE -lpthread
membership:
	@rm -f bin/HexaPlus_MEMBERSHIP
	@rm -f fuzzy.o HexaPlusCS.o HexaPlus_MEMBERSHIP.o
	gcc -c $(CFLAGS) fuzzy.cpp -o fuzzy.o
	gcc -c $(CFLAGS) HexaPlusCS.cpp -o HexaPlusCS.o 
	gcc -c $(CFLAGS) HexaPlus_MEMBERSHIP.cpp -o HexaPlus_MEMBERSHIP.o
	g++ fuzzy.o HexaPlusCS.o HexaPlus_MEMBERSHIP.o -o bin/HexaPlus_MEMBERSHIP -lpthread
