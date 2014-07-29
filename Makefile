BUILDDIR=./build
EARL_MAJOR=0
EARL_MINOR=1
EARL_REVISION=0

all: clean build test

.PHONY: all build clean test

build:
	@mkdir $(BUILDDIR)
	@echo '> Building library...'
	@$(CXX) -c -fPIC -std=c++0x Earl.cpp -Wall -lpthread -o $(BUILDDIR)/Earl.o
	@$(CXX) $(BUILDDIR)/Earl.o -shared -o $(BUILDDIR)/libEarl_$(EARL_MAJOR)_$(EARL_MINOR)_$(EARL_REVISION).so
	@rm $(BUILDDIR)/Earl.o
	@echo '> Building test code...'
	@$(CXX) -std=c++0x *.cpp -Wall -lpthread -o$(BUILDDIR)/test-Earl
	@echo '> Complete!'

test:
	@echo '> Testing Earl...'
	@$(BUILDDIR)/test-Earl
	@echo '> Tests completed!'

clean:
	@rm -rf $(BUILDDIR)