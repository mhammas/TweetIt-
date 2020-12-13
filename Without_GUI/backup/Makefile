.SUFFIXES:
.SUFFIXES: .o .cpp
#============================================================
TARGET1	=  MapVector
TARGET2	=  UOMapVector

C_SOURCES1 =  MapVector.cpp
C_SOURCES2 =  UOMapVector.cpp

C_OBJS1     =  MapVector.o
C_OBJS2     =  UOMapVector.o

MY_INCLUDES =
# merg.h


CCX = g++
CXXFLAGS = -g -std=c++11
# -Wall

#============================================================
all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) 

.o:.cpp	$(MY_INCLUDES)
	$(CCX)  -c  $(CXXFLAGS) $<  

$(TARGET1) :   $(C_OBJS1)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

$(TARGET2) :   $(C_OBJS2)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

$(TARGET3) :   $(C_OBJS3)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

$(TARGET4) :   $(C_OBJS4)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

# Implicit rules: $@ = target name, $< = first prerequisite name, $^ = name of all prerequisites
#============================================================

ALL_SOURCES = Makefile $(C_SOURCES1) $(C_SOURCES2) $(MY_INCLUDES)

NOTES =
%= otherstuff.np 

clean:
	rm -f $(TARGET1) $(C_OBJS1) $(TARGET2) $(C_OBJS2) core 

tar: $(ALL_SOURCES) $(NOTES)
	tar cvf $(TARGET).tar $(ALL_SOURCES)  $(NOTES)

$(TARGET).ps: $(ALL SOURCES)
	enscript -pcode.ps $(ALL_SOURCES)

