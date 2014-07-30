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

bool runTests(bool async) {
	if(async) {
		std::cout << "Running suite in asynchronous mode." << std::endl;
	} else {
		std::cout << "Running suite in synchronous mode." << std::endl;
	}

	// Clear the suite of any previous tests.
	Test::initSuite();
	Test::runAsynchronously(async);

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

	// Run the suite of tests and return the
	// truthiness of the results we expect
	Test::runTests();
	return (Test::getTestsPassed() == 3) && (Test::getTestsFailed() == 1) && (Test::getTestsPending() == 1);
}

int main() {
	return (runTests(false) && runTests(true)) ? 0 : 1;
}