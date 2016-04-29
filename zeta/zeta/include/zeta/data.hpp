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

#ifndef ZETA_DATA_HPP
#	define ZETA_DATA_HPP

#include <cstddef>
#include <utility>
#include <ostream>
#include <iomanip>

namespace zeta
{
	class data
	{
		public:
			void* ptr;
			std::size_t size;

		public:
			data()
				: ptr {nullptr}, size {0}
			{
				//
			}

			data(void* ptr, std::size_t size)
				: ptr {ptr}, size {size}
			{
				//
			}

			data(const data& d)
				: ptr {d.ptr}, size {d.size}
			{
				//
			}

			data(data&& d)
			{
				*this = std::move(d);
			}

		public:
			bool valid() const
			{
				return !this->null();
			}

			bool null() const
			{
				return this->ptr == nullptr;
			}

			void clear()
			{
				this->ptr = nullptr;
				this->size = 0;
			}

		public:
			data& operator=(const data& d) = default;

			data& operator=(data&& d)
			{
				this->ptr = d.ptr;
				this->size = d.size;

				d.clear();
				return *this;
			}

			bool operator==(const data& rhs) const
			{
				return this->ptr == rhs.ptr
					&& this->size == rhs.size;
			}

			bool operator!=(const data& rhs) const
			{
				return !(*this == rhs);
			}

			explicit operator bool() const
			{
				return this->valid();
			}
	};

	inline std::ostream& operator<<(std::ostream& os, const data& d)
	{
		std::ios::fmtflags flags(os.flags());
		os << std::hex << d.ptr << std::dec << " (" << d.size << ")";
		os.flags(flags);
		return os;
	}
}

#endif
