WOPTIONS=-Wall -Wextra -pedantic -Wno-unused-parameter
OPTIMIZATION_LEVEL=-O3

all: base metric base_debug metric_debug
	@true
base:
	clang -std=gnu99 $(WOPTIONS) *.c $(OPTIMIZATION_LEVEL) -o gcd -lpthread -ldispatch
metric:
	clang -std=gnu99 $(WOPTIONS) *.c -D_METRIC $(OPTIMIZATION_LEVEL) -o metric_gcd -lpthread -ldispatch
base_debug:
	clang -std=gnu99 $(WOPTIONS) *.c -D_DEBUG $(OPTIMIZATION_LEVEL) -o debug_gcd -lpthread -ldispatch
metric_debug:
	clang -std=gnu99 $(WOPTIONS) *.c -D_METRIC -D_DEBUG $(OPTIMIZATION_LEVEL) -o debug_metric_gcd -lpthread -ldispatch
clean:
	rm gcd metric_gcd debug_gcd debug_metric_gcd
