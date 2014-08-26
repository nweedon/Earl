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

#ifdef _MSC_VER
 	#define WHITE ""
#else
 	#define WHITE "\e[0;37m"
#endif

namespace Earl {
	class Print {
	private:
		static std::mutex stdoutMutex;
		/**
		 * Print::base
		 * -------------------
		 * Base printing function. Will acquire lock to stdout, print,
		 * then release the lock.
		 * @param s - String to print
		 * @param colour - An ansi colour code used to colour the output
		 * @param flush - Flush output instead of ending the line
		 */
		static void base(std::string s, std::string colour = WHITE, bool flush = false);
	public:
		Print() { };
		~Print() { };
		/**
		 * Print::line
		 * -------------------
		 * Print a line of text.
		 * @param s - String to print
		 * @param colour - An ansi colour code used to colour the output
		 */
		static void line(std::string s, std::string colour = WHITE);
		/**
		 * Print::fragment
		 * -------------------
		 * Print some text. The line printed on is not terminated.
		 * @param s - String to print
		 * @param colour - An ansi colour code used to colour the output
		 */
		static void fragment(std::string s, std::string colour = WHITE);
	};
};