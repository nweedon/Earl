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

namespace Earl {
	int Test::testsRun = 0;
	int Test::testsFailed = 0;
	bool Test::runAsync = false;

	// The list of functions run before the next test.
	std::vector<std::function<void()>> Test::beforeList;
	// The list of functions run before each test.
	std::vector<std::function<void()>> Test::beforeEachList;
	// The list of functions run before the next test.
	std::vector<std::function<void()>> Test::afterList;
	// The list of functions run after each test.
	std::vector<std::function<void()>> Test::afterEachList;
	// The list of tests to be executed.
	std::vector<TestCase> Test::testList;
	// Stores the descriptions of pending tests
	std::vector<std::string> Test::pendingTest;

	// Mutex used for protecting stdout
	std::mutex Test::stdoutMutex;

	/**
	 * Test::initSuite
	 * -------------------
	 * Initialise the test suite, clearing all stacked
	 * tests and results.
	 */
	void Test::initSuite(void) {
		// Clear all befores and afters
		beforeList.clear();
		beforeEachList.clear();
		afterList.clear();
		afterEachList.clear();
		// Remove all the tests
		testList.clear();
		// Initialise the results.
		testsRun = 0;
		testsFailed = 0;
		pendingTest.clear();
	}

	/**
	 * Test::describe
	 * -------------------
	 * Describe a set of tests to be executed.
	 * @param description - Describes the set of tests to be run
	 * @param lambda - The function to run, after the description has been printed.
	 */
	void Test::describe(std::string description, std::function<void()> lambda) {
			std::cout << "# " << description << std::endl;
			lambda();
	}

	/**
	 * Test::it
	 * -------------------
	 * Add one test to the list of tests to be run when 
	 * Test::runTests function is called.
	 * @param description - Describes the function of the test
	 * @param lambda - The test to run. If the test runs true, the test is
	 * 					is said to have passed.
	 */
	void Test::it(std::string description, std::function<bool()> lambda) {
		TestCase test { lambda, description, beforeList, afterList };
		beforeList.clear();
		afterList.clear();
		testList.push_back(test);
	}

	void Test::it(std::string description){
		pendingTest.push_back(description);
	}
	
	/**
	 * Test::runAsynchronously
	 * -------------------
	 * Tell Earl to whether to run tests in an asynchronous manner.
	 * @param async - Set to true to run tests asynchronously.
	 */
	void Test::runAsynchronously(bool async) {
		runAsync = async;
	}

	/**
	 * Test::runTest
	 * -------------------
	 * Run one component test. Related befores and afters are run in their
	 * respected positions of the test.
	 * @param testCase - The test case which will be run
	 */
	void Test::runTest(TestCase testCase) {
		// Process before functions. These are removed
		// after one use.
		for(auto f : testCase.beforeList) {
			f();
		}

		// Process beforeEach list. These are not removed
		// after one use.
		for(auto f : beforeEachList) {
			f();
		}

		bool passed = testCase.test();

		// Process after functions. These are removed
		// after one use.
		for(auto f : testCase.afterList) {
			f();
		}

		// Process afterEach list. These are not removed
		// after one use.
		for(auto f : afterEachList) {
			f();
		}
		
		// Mutex will be unlocked when the lock
		// guard goes out of scope. The mutex also
		// implicitly guards Test::testsRun and
		// Test::testsFailed
		std::lock_guard<std::mutex> g_stdout(stdoutMutex);

		testsRun++;

		if(passed) {
			std::cout << GREEN << "PASS " << WHITE << std::flush;
		} else {
			std::cout << RED << "FAIL " << WHITE << std::flush;
			testsFailed++;
		}

		std::cout << testCase.description << std::endl;
	}

	/**
	 * Test::runTests
	 * -------------------
	 * Run all the tests added to the test list with
	 * the Test::it function.
	 */
	void Test::runTests() {
		std::vector<std::shared_ptr<std::thread>> taskList;

		for(auto test : testList) {
			if(runAsync) {
				taskList.push_back(std::make_shared<std::thread>(runTest, test));
			} else {
				runTest(test);
			}			
		}

		// Wait for all tasks to complete. The thread
		// shared_ptr will delete itself after it goes
		// out of scope.
		for(auto task : taskList) {
			task->join();
		}
		
		// print out the pending tests
		for(auto task : pendingTest) {
			std::cout << "PEND " << task << std::endl;
		}
	}

	/**
	 * Test::beforeEach
	 * -------------------
	 * Add a function to the stack which will run before
	 * each test.
	 * @param lambda - The function which will be run before each
	 * 					'it' test is executed.
	 */
	void Test::beforeEach(std::function<void()> lambda) {
		beforeEachList.push_back(lambda);
	}

	/**
	 * Test::before
	 * -------------------
	 * Add a function to the stack which will run before
	 * the 'it' test immediately following this function.
	 * The function will not execute again unless Test::before
	 * is called again.
	 * @param lambda - The function which will be run before the next 'it' test.
	 */
	void Test::before(std::function<void()> lambda) {
		beforeList.push_back(lambda);
	}

	/**
	 * Test::afterEach
	 * -------------------
	 * Add a function to the stack which will run after
	 * each test.
	 * @param lambda - The function which will be run after each
	 * 					'it' test is executed.
	 */
	void Test::afterEach(std::function<void()> lambda) {
		afterEachList.push_back(lambda);
	}

	/**
	 * Test::after
	 * -------------------
	 * Add a function to the stack which will run after
	 * the 'it' test immediately following this function.
	 * The function will not execute again unless Test::before
	 * is called again.
	 * @param lambda - The function which will be run after the next 'it' test.
	 */
	void Test::after(std::function<void()> lambda) {
		afterList.push_back(lambda);
	}

	/**
	 * Test::printSummary
	 * -------------------
	 * Print a summary of all the tests that
	 * have been run.
	 */
	void Test::printSummary() {
		std::cout << std::endl;
		std::cout << "Summary: " << std::endl;
		std::cout << "---------------" << std::endl;
		std::cout << testsRun << " tests run, " << (testsRun - testsFailed) << " tests passed." << std::endl;
	}
}