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
#pragma once

#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <string>
#include <iostream>
#include <vector>

#define GREEN "\e[0;32m"
#define WHITE "\e[0;37m"
#define RED "\e[0;31m"

#define TAB "\t"

namespace Earl {

	struct TestCase {
		std::function<bool()> test;
		std::string description;
		std::vector<std::function<void()>> beforeList, afterList;
	};

	class Test {
	private:
		static int testsFailed, testsRun;
		static bool runAsync;
		// The list of functions run before each test.
		static std::vector<std::function<void()>> beforeEachList;
		// The list of functions run before the next test.
		static std::vector<std::function<void()>> beforeList;
		// The list of functions run after each test.
		static std::vector<std::function<void()>> afterEachList;
		// The list of functions run after the next test.
		static std::vector<std::function<void()>> afterList;
		// The list of tests to be executed.
		static std::vector<TestCase> testList;
		// Stores the descriptions of pending tests
		static std::vector<std::string> pendingTest;

		// Mutex used for protecting stdout
		static std::mutex stdoutMutex;

		/**
		 * Test::runTest
		 * -------------------
		 * Run one component test. Related befores and afters are run in their
		 * respected positions of the test.
		 * @param testCase - The test case which will be run
		 */
		static void runTest(std::shared_ptr<TestCase> testCase);
	public:
		Test();
		~Test();

		/**
		 * Test::initSuite
		 * -------------------
		 * Initialise the test suite, clearing all queued
		 * tests and results.
		 */
		static void initSuite();

		/**
		 * Test::runTests
		 * -------------------
		 * Run all the tests added to the test list with
		 * the Test::it function.
		 */
		static void runTests();

		/**
		 * Test::runAsynchronously
		 * -------------------
		 * Tell Earl to whether to run tests in an asynchronous manner.
		 * @param async - Set to true to run tests asynchronously.
		 */
		static void runAsynchronously(bool);

		/**
		 * Test::describe
		 * -------------------
		 * Describe a set of tests to be executed.
		 * @param description - Describes the set of tests to be run
		 * @param lambda - The function to run, after the description has been printed.
		 */
		static void describe(std::string, std::function<void()>);
		
		/**
		 * Test::it
		 * -------------------
		 * Run one component test. Related befores and afters are run in their
		 * respected positions of the test.
		 * @param description - Describes the function of the test
		 * @param lambda - The test to run. If the test returns true, the test is
		 * 					is said to have passed.
		 */
		static void it(std::string, std::function<bool()>);
		
		/**
		 * Test::it
		 * -------------------
		 * Run one component test(used for pending tests). Related befores and afters are run in their
		 * respected positions of the test.
		 * @param description - Describes the function of the test
		 */
		static void it(std::string);

		/**
		 * Test::beforeEach
		 * -------------------
		 * Add a function to the stack which will run before
		 * each test.
		 * @param lambda - The function which will be run before each
		 * 					'it' test is executed.
		 */
		static void beforeEach(std::function<void()>);

		/**
		 * Test::before
		 * -------------------
		 * Add a function to the stack which will run before
		 * the 'it' test immediately following this function.
		 * The function will not execute again unless Test::before
		 * is called again.
		 * @param lambda - The function which will be run before the next 'it' test.
		 */
		static void before(std::function<void()>);

		/**
		 * Test::afterEach
		 * -------------------
		 * Add a function to the stack which will run after
		 * each test.
		 * @param lambda - The function which will be run after each
		 * 					'it' test is executed.
		 */
		static void afterEach(std::function<void()>);

		/**
		 * Test::after
		 * -------------------
		 * Add a function to the stack which will run after
		 * the 'it' test immediately following this function.
		 * The function will not execute again unless Test::before
		 * is called again.
		 * @param lambda - The function which will be run after the next 'it' test.
		 */
		static void after(std::function<void()>);
		
		/**
		 * Test::getTestsFailed
		 * -------------------
		 * Returns the number of tests that failed.
		 */
		static int getTestsFailed() { return testsFailed; };

		/**
		 * Test::getTestsPassed
		 * -------------------
		 * Returns the number of tests that passed.
		 */
		static int getTestsPassed() { return testsRun - testsFailed; };

		/**
		 * Test::printSummary
		 * -------------------
		 * Print a summary of all the tests that
		 * have been run.
		 */
		static void printSummary();
		
		/**
		 * Test::getTestsPending
		 * -------------------
		 * Returns the number of tests that are 
		 * pending (are unimplemented)
		 */
		static int getTestsPending() { return pendingTest.size(); };
	};

};