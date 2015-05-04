CXXFLAGS =	-O2 -g -Wall -std=c++11 -fmessage-length=0

OBJS =		Functions.o

LIBS =

TARGET =	Functions

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
