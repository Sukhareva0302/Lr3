#include "pch.h"
#include "CppUnitTest.h"
#include"..\ConsoleApplication1\ConsoleApplication1.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_Insert_and_Search)
		{
			Tree head;
			head.insert(8);
			head.insert(3);
			head.insert(6);
			head.insert(2);
			head.insert(10);
			head.insert(1);
			head.insert(14);
			head.insert(7);
			Assert::IsTrue(head.search(1));
			Assert::IsTrue(head.search(2));
			Assert::IsTrue(head.search(3));
			Assert::IsTrue(head.search(6));
			Assert::IsTrue(head.search(7));
			Assert::IsTrue(head.search(8));
			Assert::IsTrue(head.search(10));
			Assert::IsTrue(head.search(14));
			Assert::IsFalse(head.search(666));
			Assert::IsFalse(head.search(11));
		}
		TEST_METHOD(Test_Remove_and_Search)
		{
			Tree head;
			head.insert(8);
			head.insert(3);
			head.insert(6);
			head.insert(2);
			head.insert(10);
			head.insert(1);
			head.insert(14);
			head.insert(7);
			head.remove(3);
			head.remove(8);
			head.remove(14);
			head.remove(6);
			head.remove(1);
			bool check_invalid_argurent = false;
			try
			{
				head.remove(77);
			}
			catch (invalid_argument)
			{
				check_invalid_argurent = true;
			}
			Assert::IsTrue(check_invalid_argurent);
			Assert::IsFalse(head.search(1));
			Assert::IsTrue(head.search(2));
			Assert::IsFalse(head.search(3));
			Assert::IsFalse(head.search(6));
			Assert::IsTrue(head.search(7));
			Assert::IsFalse(head.search(8));
			Assert::IsTrue(head.search(10));
			Assert::IsFalse(head.search(14));
			Assert::IsFalse(head.search(666));
			Assert::IsFalse(head.search(11));
		}
		TEST_METHOD(Test_Iterators)
		{
			int dft_array[8];
			int bft_array[8];
			Tree head;
			head.insert(8);
			head.insert(3);
			head.insert(6);
			head.insert(2);
			head.insert(10);
			head.insert(1);
			head.insert(14);
			head.insert(7);
			Iterator* dft;
			Iterator* bft;
			dft = head.create_dft_iterator();
			bft = head.create_bft_iterator();
			int counter_dft = 0;
			int counter_bft = 0;
			while (dft->has_next())
			{
				dft_array[counter_dft]= dft->next();
				counter_dft++;
			}
			while (bft->has_next())
			{
				{
					bft_array[counter_bft] = bft->next();
					counter_bft++;
				}
			}
			Assert::AreEqual(dft_array[0], 8);
			Assert::AreEqual(dft_array[1], 3);
			Assert::AreEqual(dft_array[2], 2);
			Assert::AreEqual(dft_array[3], 1);
			Assert::AreEqual(dft_array[4], 6);
			Assert::AreEqual(dft_array[5], 7);
			Assert::AreEqual(dft_array[6], 10);
			Assert::AreEqual(dft_array[7], 14);

			Assert::AreEqual(bft_array[0], 8);
			Assert::AreEqual(bft_array[1], 3);
			Assert::AreEqual(bft_array[2], 10);
			Assert::AreEqual(bft_array[3], 2);
			Assert::AreEqual(bft_array[4], 6);
			Assert::AreEqual(bft_array[5], 14);
			Assert::AreEqual(bft_array[6], 1);
			Assert::AreEqual(bft_array[7], 7);
		}
	};
}
