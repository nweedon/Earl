# Output Directory
BUILDDIR=./build
# Version Information
EARL_MAJOR=1
EARL_MINOR=0
# Source files for Shared Library
SRC=Earl.cpp EarlAssert.cpp EarlPrint.cpp
# Shared Library output location
LIB_OUT=$(BUILDDIR)/libEarl.so.$(EARL_MAJOR).$(EARL_MINOR)
# Coverage arguments and flag
COV_ARGS=-lgcov -coverage
COVERAGE=true

ifeq ($(COVERAGE), true)
	args=$(COV_ARGS)
else
	args=
endif

all: clean build test

.PHONY: all build clean test

build:
	@mkdir $(BUILDDIR)

# > Build library
# Compile object files
ifeq ($(CXX),g++)
	@$(CXX) -c $(SRC) -fPIC -std=c++0x -Wall -lpthread $(args)
	@$(CXX) *.o -shared $(args) -o $(LIB_OUT)
else
	@$(CXX) -c $(SRC) -fPIC -std=c++11 -stdlib=libc++ -Wall -pthread
	@$(CXX) *.o -shared -o $(LIB_OUT)
endif

	@rm *.o

	# > Build Test Code

# Compile executable, using shared library
ifeq ($(CXX),g++)
	@$(CXX) -std=c++0x test.cpp $(LIB_OUT) -Wall -lpthread -o$(BUILDDIR)/test-Earl
else
	@$(CXX) -std=c++11 test.cpp $(LIB_OUT) -stdlib=libc++ -Wall -pthread -o$(BUILDDIR)/test-Earl
endif

test:
	@echo '> Testing Earl...'
	@$(BUILDDIR)/test-Earl
	@echo '> Tests completed!'

clean:
	@rm -rf $(BUILDDIR)