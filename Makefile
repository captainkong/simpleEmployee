TARGET = emp
SOURCE = emp.cpp
CFLAGS = -std=c++11 
CC = g++

$(TARGET):$(SOURCE)
	$(CC) $(SOURCE) -o $(TARGET) $(CFLAGS)
	
clean:
	rm -fr $(TARGET)
	