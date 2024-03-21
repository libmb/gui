TARGET := gui
PHONY_TARGETS := all clean

SRCS := $(shell find src -type f -name \*.c)
OBJS := $(patsubst src/%.c,tmp/obj/%.o,$(SRCS))

CPPFLAGS := -Iinclude -Iexternal/include -DNDEBUG
LDFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -Lexternal/lib -lglfw3 -lmb_core -lmb_real_float -lmb_colorizer_basic
CFLAGS := -O

$(PHONY_TARGETS):
.PHONY: $(PHONY_TARGETS)

external:
	sh ./init.sh

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

./tmp/obj/%.o: ./src/%.c external
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean_obj
clean: clean_obj
clean_obj:
	rm -rf ./tmp/obj

.PHONY: clean_output
clean: clean_output
clean_output:
	rm -f $(TARGET)
