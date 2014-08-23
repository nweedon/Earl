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

#include <string>
#include <iostream>
#include <mutex>
#include "EarlPrint.h"

#ifdef _MSC_VER
 	#define GREY ""
 	#define WHITE ""
#else
 	#define GREY "\e[1;30m"
 	#define WHITE "\e[0;37m"
#endif

#define ASSERT_OUTPUT "\tassert => "

namespace Earl {
	class Assert {
		public:
			static bool isTruthy(bool);
			static bool isTruthy(bool, std::string);
			static bool isFalsy(bool);
			static bool isFalsy(bool, std::string);

			template <typename T>
			static bool isEqual(T*, T*);
			template <typename T>
			static bool isEqual(T*, T*, std::string);

			template <typename T>
			static bool isEqualDeep(T*, T*);
			template< typename T>
			static bool isEqualDeep(T*, T*, std::string);
	};

	/**
	 * Assert::isEqual
	 * -------------------
	 * Compare whether the two pointer values are equal.
	 * @param first - First value to compare
	 * @param second - Second value to compare
	 */
	template <typename T>
	bool Assert::isEqual(T* first, T* second) {
		return first == second;
	}

	/**
	 * Assert::isEqual
	 * -------------------
	 * Compare whether the two pointer values are equal,
	 * adding a comment to the assertion.
	 * @param first - First value to compare
	 * @param second - Second value to compare
	 * @param outputMessage - The comment to print when making the assertion
	 */
	template <typename T>
	bool Assert::isEqual(T* first, T* second, std::string outputMessage) {
		Print::line(ASSERT_OUTPUT + outputMessage, GREY);
		return isEqual(first, second);
	};

	/**
	 * Assert::isEqualDeep
	 * -------------------
	 * Compare whether the two pointed-to data values are equal.
	 * @param first - First value to compare
	 * @param second - Second value to compare
	 */
	template <typename T>
	bool Assert::isEqualDeep(T* first, T* second) {
		if(first && second) {
			return *first == *second;
		}
		return false;
	}

	/**
	 * Assert::isEqualDeep
	 * -------------------
	 * Compare whether the two pointed-to data values are equal,
	 * adding a comment to the assertion.
	 * @param first - First value to compare
	 * @param second - Second value to compare
	 * @param outputMessage - The comment to print when making the assertion
	 */
	template <typename T>
	bool Assert::isEqualDeep(T* first, T* second, std::string outputMessage) {
		Print::line(ASSERT_OUTPUT + outputMessage, GREY);
		return isEqualDeep(first, second);
	}
}