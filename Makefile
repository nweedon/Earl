BUILDDIR=./build
EARL_MAJOR=0
EARL_MINOR=1
EARL_REVISION=0

all: clean build

.PHONY: all build clean

build:
	@mkdir $(BUILDDIR)
	@echo '> Building...'
	@$(CXX) -c -fPIC -std=c++0x *.cpp -Wall -lpthread -o $(BUILDDIR)/Earl.o
	@$(CXX) $(BUILDDIR)/Earl.o -shared -o $(BUILDDIR)/libEarl_$(EARL_MAJOR)_$(EARL_MINOR)_$(EARL_REVISION).so
	@rm $(BUILDDIR)/Earl.o
	@echo '> Complete!'

clean:
	@rm -rf $(BUILDDIR)