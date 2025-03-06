# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = car_list
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
