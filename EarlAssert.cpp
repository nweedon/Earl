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
 #include "EarlAssert.h"

namespace Earl {
	std::mutex Assert::stdoutMutex;

	/**
	 * Assert::isTruthy
	 * -------------------
	 * Return whether the passed argument is true.
	 * @param truthiness - Deteremines whether the return value is true.
	 */
	bool Assert::isTruthy(bool truthiness) {
		return truthiness;
	}

	/**
	 * Assert::isTruthy
	 * -------------------
	 * Return whether the passed argument is true, adding
	 * a comment to the assertion.
	 * @param truthiness - Deteremines whether the return value is true.
	 * @param outputMessage - The comment to be printed to stdout.
	 */
	bool Assert::isTruthy(bool truthiness, std::string outputMessage) {
		//std::lock_guard<std::mutex> g_stdout(stdoutMutex);
		std::cout << GREY << ASSERT_OUTPUT << outputMessage << WHITE << std::endl;
		return isTruthy(truthiness);
	}

	/**
	 * Assert::isFalsy
	 * -------------------
	 * Return whether the passed argument is false.
	 * @param falsiness - Deteremines whether the return value is false.
	 */
	bool Assert::isFalsy(bool falsiness) {
		return !falsiness;
	}

	/**
	 * Assert::isFalsy
	 * -------------------
	 * Return whether the passed argument is false, adding
	 * a comment to the assertion.
	 * @param falsiness - Deteremines whether the return value is false.
	 * @param outputMessage - The comment to be printed to stdout.
	 */
	bool Assert::isFalsy(bool falsiness, std::string outputMessage) {
		std::lock_guard<std::mutex> g_stdout(stdoutMutex);
		std::cout << GREY << ASSERT_OUTPUT << outputMessage << std::endl;
		return isFalsy(falsiness);
	}

};