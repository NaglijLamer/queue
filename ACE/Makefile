WOPTIONS=-Wall -Wextra -pedantic -Wno-unused-parameter
OPTIMIZATION_LEVEL=-O3
CPP=clang++

all: base metric base_debug metric_debug
	@true
base:
	$(CPP) *.cpp *.c -std=c++11 $(WOPTIONS) -Wno-unused-but-set-variable -I $$ACE_ROOT/ -L $$ACE_ROOT/lib/ $(OPTIMIZATION_LEVEL) -o ace -lACE -lpthread
metric:
	$(CPP) *.cpp *.c -std=c++11 $(WOPTIONS) -Wno-unused-but-set-variable -D_METRIC -I $$ACE_ROOT/ -L $$ACE_ROOT/lib/ $(OPTIMIZATION_LEVEL) -o metric_ace -lACE -lpthread
base_debug:
	$(CPP) *.cpp *.c -std=c++11 $(WOPTIONS) -D_DEBUG -I $$ACE_ROOT/ -L $$ACE_ROOT/lib/ $(OPTIMIZATION_LEVEL) -o debug_ace -lACE -lpthread
metric_debug:
	$(CPP) *.cpp *.c -std=c++11 $(WOPTIONS) -D_METRIC -D_DEBUG -I $$ACE_ROOT/ -L $$ACE_ROOT/lib/ $(OPTIMIZATION_LEVEL) -o debug_metric_ace -lACE -lpthread
clean:
	rm ace metric_ace debug_ace debug_metric_ace
ace_thread:
	$(CPP) *.cpp *.c -std=c++11 $(WOPTIONS) -D_ACE_MAIN_THREADS -I $$ACE_ROOT/ -L $$ACE_ROOT/lib/ $(OPTIMIZATION_LEVEL) -o ace_thread -lACE -lpthread
