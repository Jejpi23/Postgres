# Kompilator
CXX = g++

# Flagi kompilatora
CXXFLAGS = -std=c++11 -Wall -Wextra

# Biblioteki do linkowania
LDLIBS = -lpq

# Nazwa pliku wykonywalnego
TARGET = app

# Ścieżka do pliku źródłowego
SRC = src/main.cpp

# Reguła domyślna
all: $(TARGET)

# Reguła kompilacji pliku wykonywalnego
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

# Czyszczenie pliku wykonywalnego
clean:
	rm -f $(TARGET)

# Phony targets (cele, które nie są plikami)
.PHONY: all clean