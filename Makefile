BUILDDIR=./build
EARL_MAJOR=1
EARL_MINOR=0
SRC=Earl.cpp EarlAssert.cpp EarlPrint.cpp
LIB_OUT=$(BUILDDIR)/libEarl.so.$(EARL_MAJOR).$(EARL_MINOR)

all: clean build test

.PHONY: all build clean test

build:
	@mkdir $(BUILDDIR)

# > Build library
# Compile object files
ifeq ($(CXX),g++)
	@$(CXX) -c $(SRC) -fPIC -std=c++0x -Wall -lpthread
else
	@$(CXX) -c $(SRC) -fPIC -std=c++11 -stdlib=libc++ -Wall -pthread
endif
	
	# Move object files to build directory
	@mv *.o $(BUILDDIR)
	# Create shared library
	@$(CXX) $(BUILDDIR)/*.o -shared -o $(LIB_OUT)
	@rm $(BUILDDIR)/*.o

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