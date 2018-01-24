WOPTIONS=-Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-but-set-variable
OPTIMIZATION_LEVEL=-O3
CC=g++
STANDARD=-std=c++11

all: base metric base_debug metric_debug
	@true
base:
	$(CC) $(STANDARD) $(WOPTIONS) *.c *.cpp $(OPTIMIZATION_LEVEL) -o custom -lpthread
metric:
	$(CC) $(STANDARD) $(WOPTIONS) *.c *.cpp -D_METRIC $(OPTIMIZATION_LEVEL) -o metric_custom -lpthread
base_debug:
	$(CC) $(STANDARD) $(WOPTIONS) *.c *.cpp -D_DEBUG $(OPTIMIZATION_LEVEL) -o debug_custom -lpthread
metric_debug:
	$(CC) $(STANDARD) $(WOPTIONS) *.c *.cpp -D_METRIC -D_DEBUG $(OPTIMIZATION_LEVEL) -o debug_metric_custom -lpthread 
clean:
	rm custom metric_custom debug_custom debug_metric_custom
