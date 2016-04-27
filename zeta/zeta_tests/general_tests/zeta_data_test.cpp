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

#include <cstddef>
#include <gtest/gtest.h>
#include <zeta/data.hpp>

TEST(ZetaDataTest, CTor)
{
	zeta::data d {};

	EXPECT_EQ(d.ptr, nullptr);
	EXPECT_EQ(d.size, 0);
}

TEST(ZetaDataTest, CTorValue)
{
	void* address = reinterpret_cast<void*>(123456789);
	std::size_t size = 987654321;

	zeta::data d {address, size};

	EXPECT_EQ(d.ptr, address);
	EXPECT_EQ(d.size, size);
}

TEST(ZetaDataTest, Clear)
{
	void* address = reinterpret_cast<void*>(123456789);
	std::size_t size = 987654321;

	zeta::data d {address, size};
	d.clear();

	EXPECT_EQ(d.ptr, nullptr);
	EXPECT_EQ(d.size, 0);
}

TEST(ZetaDataTest, BoolCompare)
{
	void* address = reinterpret_cast<void*>(123456789);
	std::size_t size = 987654321;

	zeta::data d1 {address, size};
	if(!d1)
		ADD_FAILURE();

	zeta::data d2 {};
	if(d2)
		ADD_FAILURE();
}

TEST(ZetaDataTest, Equals)
{
	void* address = reinterpret_cast<void*>(123456789);
	std::size_t size = 987654321;

	zeta::data d1 {address, size};
	zeta::data d2 {address, size};
	zeta::data d3 {};

	EXPECT_EQ(d1, d2);
	EXPECT_NE(d1, d3);
}

TEST(ZetaDataTest, Empty)
{
	void* address = reinterpret_cast<void*>(123456789);
	std::size_t size = 987654321;

	zeta::data d1 {};
	zeta::data d2 {};
	zeta::data d3 {address, size};

	ASSERT_EQ(d1, d2);
	ASSERT_NE(d1, d3);
}
