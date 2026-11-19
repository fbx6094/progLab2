CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRCS = main.cpp \
       src/SVGElement.cpp \
       src/Rect.cpp \
       src/Circle.cpp \
       src/Line.cpp \
       src/Polyline.cpp \
       src/Path.cpp \
       src/Use.cpp \
       src/Group.cpp \
       src/SVGDocument.cpp \
       src/SVGDocumentBuilder.cpp \
       src/Validator.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /f /q $(TARGET) main.o src\*.o 2>nul || rm -f $(TARGET) $(OBJS)
