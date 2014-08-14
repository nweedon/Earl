/*******************************************************************************
 * Copyright (c) 2014, Niall Frederick Weedon and other Contributors
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this 
 * list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation and/or 
 * other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 * be used to endorse or promote products derived from this software without 
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/ 
#include "Earl.h"
#include <iostream>
#include <string>
#include <chrono>

using namespace Earl;

bool runTests(bool async, int threads) {
	if(async) {
		std::cout << std::endl << "Running suite in asynchronous mode. (" << threads << " threads)" << std::endl;
	} else {
		std::cout << std::endl << "Running suite in synchronous mode." << std::endl;
	}

	// Clear the suite of any previous tests.
	Test::initSuite();
	Test::runAsynchronously(async);
	Test::setMaxConcurrency(threads);

	// Run a suite of output tests (make sure
	// Earl returns what we expect)
	Test::describe("Earl Output Tests", []() {
		
		Test::it("Should pass a test", []() -> bool {
			return (0 == 0);
		});

		Test::it("Should fail a test", []() -> bool {
			return (0 == 1);
		});

		Test::it("Should wait for all tests to complete", []() -> bool {
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return true;
		});

		Test::it("Should handle potential race condition with asynchronous tests", []() -> bool {
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return true;
		});
		
		Test::it("Should store a pending test");
	});

	Test::describe("Earl Assertions API", []() {

		Test::it("isTruthy -> Returns true when parameter is true", []() -> bool {
			bool result = Assert::isTruthy(true) ;
			result &= Assert::isTruthy(true, "isTruthyTest");
			return result;
		});

		Test::it("isTruthy -> Returns false when parameter is false", []() -> bool {
			bool result = Assert::isTruthy(false);
			result &= Assert::isTruthy(false, "isTruthyTest (falsy)");
			return !result;
		});

		Test::it("isFalsy -> Returns true when parameter is false", []() -> bool {
			bool result =-Assert::isFalsy(false);
			result &= Assert::isFalsy(false, "isFalsyTest");
			return result;
		});

		Test::it("isFalsy -> Returns false when parameter is true", []() -> bool {
			bool result = Assert::isFalsy(true);
			result &= Assert::isFalsy(true, "isFalsyTest (truthy)");
			return !result;
		});

		Test::it("isEqual -> Returns true when pointers are equal", []() -> bool {
			bool result;
			int* a = new int;
			int* b = a;

			result = Assert::isEqual<int>(a, b);
			result &= Assert::isEqual<int>(a, b, "isEqualTest");

			delete a;

			return result;
		});

		Test::it("isEqual -> Returns false when pointers are inequal", []() -> bool {
			bool result;
			int* a = new int;
			int* b = new int;

			result = Assert::isEqual<int>(a, b);
			result &= Assert::isEqual<int>(a, b, "isEqualTest");

			delete a;
			delete b;

			return !result;
		});

		Test::it("isEqualDeep -> Returns true when pointer values are equal", []() -> bool {
			bool result;
			int* a = new int;
			int* b = new int;
			*a = 10;
			*b = 10;
			
			result = Assert::isEqualDeep<int>(a, b);
			result &= Assert::isEqualDeep<int>(a, b, "isEqualDeepTest");

			delete a;
			delete b;

			return result;
		});

		Test::it("isEqualDeep -> Returns false when pointer values are inequal", []() -> bool {
			bool result;
			int* a = new int;
			int* b = new int;
			*a = 10;
			*b = 5;
			
			result = Assert::isEqualDeep<int>(a, b);
			result &= Assert::isEqualDeep<int>(a, b, "isEqualDeepTest");

			delete a;
			delete b;

			return !result;
		});

	});

	// Run the suite of tests and return the
	// truthiness of the results we expect
	Test::runTests();
	return (Test::getTestsPassed() == 11) && (Test::getTestsFailed() == 1) && (Test::getTestsPending() == 1);
}

int main() {
	bool passed = runTests(false, 1);
	passed &= runTests(true, -1);
	passed &= runTests(true, 2);
	passed &= runTests(true, 4);
	return passed ? 0 : 1;
}