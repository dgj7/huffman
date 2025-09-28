# compile
CC = gcc
CFLAGS = -Wall -g -pedantic

# vars: source
LIBSRCDIR:=src
LIBSRC   :=$(shell find src -name "*.c")
TESTSRC  :=$(LIBSRC) $(shell find test -name "*.c")
DEMOSRC  :=$(shell find examples -name "*.c")

# vars: intermediary
DEMONAMES:=$(notdir $(basename $(DEMOSRC)))

# vars: build
LIBOBJS  :=$(patsubst %.c,target/%.o,$(notdir $(LIBSRC)))
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
	@echo -n [TEST___]: compiling: $@ [$^] ...
	@$(CC) $(CFLAGS) -o $@ $^ -I $(LIBSRCDIR) && echo done!
	@$(TEST)

# build obj files
$(LIBOBJS): $(LIBSRC)
	@echo -n [LIBOJB_]: compiling: $@ [src/$(notdir $(basename $@)).c] ...
	@$(CC) $(CFLAGS) -c src/$(notdir $(basename $@)).c -o $@ && echo done!

# build the library
$(LIBRARY): $(LIBOBJS)
	@echo -n [LIBRARY]: compiling: $@ [$^] ...
	@ar rcs $@ $^ && echo done!

# build the demos
$(DEMOPROGS): $(DEMOSRC)
	@echo -n [DEMO___]: compiling: $@ [examples/$(notdir $(basename $@)).c] ...
	@$(CC) $(CFLAGS) -o $@ -I $(LIBSRCDIR) examples/$(notdir $(basename $@)).c -L$(BUILDDIR) -l$(LIBNAME) && echo done!

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
	@echo LIBSRCDIR: $(LIBSRCDIR)
	@echo LIBSRC:    $(LIBSRC)
	@echo TESTSRC:   $(TESTSRC)
	@echo DEMOSRC:   $(DEMOSRC)
	@echo DEMONAMES: $(DEMONAMES)
	@echo LIBOBJS:   $(LIBOBJS)
	@echo DEMOPROGS: $(DEMOPROGS)
	@echo BUILDDIR:  $(BUILDDIR)
	@echo LIBNAME:   $(LIBNAME)
	@echo LIBRARY:   $(LIBRARY)
	@echo TEST:      $(TEST)
