all: tt.cpp
	g++ -fPIC -c tt.cpp
	g++ -shared -fPIC -o libtt.so tt.o
	rm -f tt.o

.PHONY: clean
clean:
	rm -f libtt.so tt.o
