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
#include <zeta/stack_allocator.hpp>

TEST(ZetaStackAllocatorTest, Allocate)
{
	zeta::stack_allocator<100, 8> sa;

	auto d1 = sa.allocate(10);
	EXPECT_NE(d1.ptr, nullptr);
	EXPECT_EQ(d1.size, 16); // Rounded up to alignment.

	auto d2 = sa.allocate(8);
	EXPECT_NE(d2.ptr, nullptr);
	EXPECT_EQ(d2.size, 8);

	EXPECT_EQ(d2.ptr, static_cast<char*>(d1.ptr) + 16);

	sa.collect();
}

TEST(ZetaStackAllocatorTest, AllocateTooMuch)
{
	zeta::stack_allocator<100, 1> sa;

	auto d1 = sa.allocate(90);
	EXPECT_NE(d1.ptr, nullptr);

	auto d2 = sa.allocate(10);
	EXPECT_NE(d2.ptr, nullptr);

	auto d3 = sa.allocate(1);
	EXPECT_EQ(d3.ptr, nullptr);

	sa.collect();
}

TEST(ZetaStackAllocatorTest, Deallocate)
{
	zeta::stack_allocator<100, 8> sa;

	auto d1 = sa.allocate(90);
	sa.deallocate(d1);

	EXPECT_EQ(sa.available(), 100);

	sa.collect();
}

TEST(ZetaStackAllocatorTest, DeallocateInOrder)
{
	zeta::stack_allocator<32, 8> sa;

	auto d1 = sa.allocate(8);
	auto d2 = sa.allocate(8);

	sa.deallocate(d2);
	sa.deallocate(d1);

	EXPECT_EQ(sa.available(), 32);

	sa.collect();
}

TEST(ZetaStackAllocatorTest, DeallocateOutOfOrder)
{
	zeta::stack_allocator<32, 8> sa;

	auto d1 = sa.allocate(8);
	auto d2 = sa.allocate(8);

	sa.deallocate(d1);
	sa.deallocate(d2);

	EXPECT_EQ(sa.available(), 24);

	sa.collect();
}

TEST(ZetaStackAllocatorTest, Collect)
{
	zeta::stack_allocator<100, 8> sa;

	sa.allocate(8);
	sa.allocate(1);
	sa.allocate(27);

	sa.collect();
	EXPECT_EQ(sa.available(), 100);
}

TEST(ZetaStackAllocatorTest, Available)
{
	zeta::stack_allocator<100, 8> sa;

	sa.allocate(8);
	EXPECT_EQ(sa.available(), 92);

	sa.allocate(1);
	EXPECT_EQ(sa.available(), 84);

	sa.collect();
	EXPECT_EQ(sa.available(), 100);
}
