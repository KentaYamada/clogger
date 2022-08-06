CXX := clang
CFLAGS := -W -O2
APPNAME := clogger_app
SRCS := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
OBJS := $(SRCS:%.c=%.o)

all: clean $(APPNAME)
$(APPNAME): $(OBJS)
	$(CXX) $(CFLAGS) -I $(INCLUDES) -o $@ $^
%.o: %.c
	$(CXX) $(CFLAGS) -o $@ -c $<
clean:
	$(RM) $(APPNAME) $(OBJS)
