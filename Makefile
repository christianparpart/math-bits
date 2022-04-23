
all: Q

Q: Q.cpp
	$(CXX) -o $@ $^ -std=c++20 -Wall -Werror

clean:
	rm -vf Q

.PHONY: all clean
