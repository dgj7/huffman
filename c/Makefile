# compile
CC = gcc
CFLAGS = -Wall -g -O0

# build vars
LIBSRCDIR:=src
LIBSRC   :=$(shell find src -name "*.c")
LIBOBJS  :=$(patsubst %.c,target/%.o,$(notdir $(LIBSRC)))
TESTSRC  :=$(LIBSRC) $(shell find test -name "*.c")
DEMOSRC  :=$(shell find examples -name "*.c")
DEMONAMES:=$(notdir $(basename $(DEMOSRC)))
DEMOPROGS:=$(patsubst %,target/%.exe,$(DEMONAMES))
BUILDDIR :=target
LIBNAME  :=huffman
LIBRARY  :=$(BUILDDIR)/lib$(LIBNAME).a
TEST     :=$(BUILDDIR)/test.exe

# tasks
.PHONY: all clean test build print
all: clean test build
build: $(LIBOBJS) $(LIBRARY) $(DEMOPROGS)
test: $(TEST)

# build test program; make halts of fails
$(TEST): $(TESTSRC)
	@echo -n compiling: $@ [$^] ...
	@$(CC) $(CFLAGS) -o $@ $^ -I $(LIBSRCDIR) && echo done!
	@$(TEST)

# build obj files
$(LIBOBJS): $(LIBSRC)
	@echo -n compiling: $@ ...
	@$(CC) $(CFLAGS) -c $< -o $@ && echo done!

# build the library
$(LIBRARY): $(LIBOBJS)
	@echo -n compiling: $@ [$^] ...
	@ar rcs $@ $^ && echo done!

# build the demos
$(DEMOPROGS): $(DEMOSRC)
	@echo compiling: $@ [examples/$(notdir $(basename $@)).c] ...
	@$(CC) -o $@ -I $(LIBSRCDIR) examples/$(notdir $(basename $@)).c -L$(BUILDDIR) -l$(LIBNAME) && done!

# clean out prior build info
clean:
	@echo -n cleaning ...
	@rm -rf $(LIBRARY)
	@rm -rf $(TEST)
	@rm -rf $(LIBOBJS)
	@rm -rf $(DEMOPROGS)
	@echo done!
	@echo -n creating target directory ...
	@mkdir -p target && echo done!

# print task to debug
print:
	@echo BUILDDIR:  $(BUILDDIR)
	@echo LIBSRCDIR: $(LIBSRCDIR)
	@echo LIBNAME:   $(LIBNAME)
	@echo LIBRARY:   $(LIBRARY)
	@echo LIBSRC:    $(LIBSRC)
	@echo LIBOBJS:   $(LIBOBJS)
	@echo DEMOSRC:   $(DEMOSRC)
	@echo DEMONAMES: $(DEMONAMES)
	@echo DEMOPROGS: $(DEMOPROGS)
	@echo TEST:      $(TEST)
	@echo TESTSRC:   $(TESTSRC)
