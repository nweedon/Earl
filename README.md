Earl
==================
[![Build Status](https://travis-ci.org/nweedon/Earl.svg)](https://travis-ci.org/nweedon/Earl)

Earl is a [Mocha](http://visionmedia.github.io/mocha/)-inspired testing framework for C++11, designed to make writing tests as easy as possible. 
Earl leverages the lambda functionality of C++11 to make tests as readable as possible.

####Compiler Compatibility (Automatically Tested)
* __Linux on Travis-CI:__ g++ 4.6, clang++ 3.4 (requires libc++)

####Compiler Compatibility (Manually Tested)
* __Ubuntu:__ g++ 4.6.3, clang++ 3.4 (requires libc++)
* __Windows (Cygwin):__ g++ 4.8.3
* __Windows:__ Visual Studio 2012 Version 11.0.60315.01 Update 2

####Example
```
// Describe the set of tests to be run
Test::describe("Example", []() {
	// Test against one part of the specification
	Test::it("Should conform to mathematical principles", []() -> bool {
		return (0 == 0);
	});
});

// Run the suite of tests
Test::runTests();
```

For API information and more examples, please view the wiki!
