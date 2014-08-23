BUILDDIR=./build
EARL_MAJOR=1
EARL_MINOR=0

all: clean build test

.PHONY: all build clean test

build:
	@mkdir $(BUILDDIR)
	@echo '> Building library...'

ifeq ($(CXX),g++)
	@$(CXX) -c Earl.cpp EarlAssert.cpp EarlPrint.cpp -fPIC -std=c++0x -Wall -lpthread 
	@mv *.o $(BUILDDIR)
else
	@$(CXX) -c Earl.cpp EarlAssert.cpp EarlPrint.cpp -fPIC -std=c++11 -stdlib=libc++ -pthread -Wall
	@mv *.o $(BUILDDIR)
endif
	
	@$(CXX) $(BUILDDIR)/*.o -shared -o $(BUILDDIR)/libEarl.so.$(EARL_MAJOR).$(EARL_MINOR)
	@rm $(BUILDDIR)/*.o
	@echo '> Building test code...'

ifeq ($(CXX),g++)
	@$(CXX) -std=c++0x test.cpp $(BUILDDIR)/libEarl.so.$(EARL_MAJOR).$(EARL_MINOR) -Wall -lpthread -o$(BUILDDIR)/test-Earl
else
	@$(CXX) -std=c++11 test.cpp $(BUILDDIR)/libEarl.so.$(EARL_MAJOR).$(EARL_MINOR) -stdlib=libc++ -Wall -pthread -o$(BUILDDIR)/test-Earl
endif

	@echo '> Complete!'

test:
	@echo '> Testing Earl...'
	@$(BUILDDIR)/test-Earl
	@echo '> Tests completed!'

clean:
	@rm -rf $(BUILDDIR)