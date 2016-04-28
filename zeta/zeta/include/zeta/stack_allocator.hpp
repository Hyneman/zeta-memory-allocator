//
//// MIT License
////
//// Copyright © 2016 BY SILENT BYTE <https://silentbyte.com/>.
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
//

#ifndef ZETA_STACK_ALLOCATOR_HPP
#	define ZETA_STACK_ALLOCATOR_HPP

#include <cstddef>
#include <cassert>

#include "defaults.hpp"
#include "memory.hpp"
#include "data.hpp"

namespace zeta
{
	template<std::size_t stack_size, std::size_t stack_alignment = zeta::default_alignment>
	class stack_allocator
	{
		private:
			static_assert(stack_alignment <= stack_size, "Alignment must be smaller than the stack's size.");
			static_assert(stack_alignment > 0, "Alignment must be greater than zero.");

		public:
			constexpr static std::size_t max_size = stack_size;
			constexpr static std::size_t alignment = stack_alignment;

		private:
			alignas(stack_alignment) char _buffer[stack_size];
			char* _pointer;

		public:
			stack_allocator()
				: _pointer {_buffer}
			{
				//
			}

		public:
			data allocate(std::size_t size)
			{
				if(size == 0)
					return {};

				std::size_t aligned = memory::align(stack_alignment, size);

				// Check if stack memory is exhausted.
				if(aligned + this->_pointer > this->_buffer + stack_size)
					return {};

				data d {this->_pointer, aligned};
				this->_pointer += aligned;

				return d;
			}

			void deallocate(data& d)
			{
				if(d.null())
					return;

				assert(this->owns(d));

				if(this->_pointer == static_cast<char*>(d.ptr) + d.size)
					this->_pointer = static_cast<char*>(d.ptr);

				d.clear();
			}

			void collect()
			{
				this->_pointer = this->_buffer;
			}

			std::size_t available() const
			{
				return stack_size - (this->_pointer - this->_buffer);
			}

			bool owns(const data& d) const
			{
				return d.valid()
					&& d.ptr >= this->_buffer
					&& d.ptr < this->_buffer + stack_size;
			}

	};
}

#endif
