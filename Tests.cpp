#include "pch.h"
#include "CppUnitTest.h"
#include "../Лаба2/Set.h"
#include "../Лаба2/TestClasses.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LabTest2
{
	TEST_CLASS(LabTest2)
	{
	public:
		//creation and output of sets
		TEST_METHOD(BlockTest1) {
			Set<int, ArrayType> array_int = {1, 2, 3, 4, 4, 5};
			Set<int, ListType> list_int = { 1, 2, 3, 4, 5, 5 };
			double a[4] = { 1.1, 2.2, 3.3, 4.4 };
			Set<double, ArrayType> array_double = a;
			Set<complex, ListType> array_complex = { complex(1, 5.5), complex(2, 4.3) };
			Set<Teacher, ListType> list_teacher = { Teacher("Ivanova Natalya Anatolyevna", 45, 40), Teacher("Roslovtsev Vladimir Vladimirovich", 30, 22) };
			Assert::AreEqual(array_int.size(), 5U, L"Block 1 Test #1 failed: wrong size of arrayset of integer numbers");
			Assert::AreEqual(list_int.size(), 5U, L"Block 1 Test #2 failed: wrong size of listset of integer numbers");
			Assert::AreEqual(array_double.size(), 4U, L"Block 1 Test #3 failed: wrong size of arrayset of double numbers");
			Assert::AreEqual(array_complex.size(), 2U, L"Block 1 Test #4 failed: wrong size of arrayset of complex numbers");
			Assert::AreEqual(list_teacher.size(), 2U, L"Block 1 Test #5 failed: wrong size of listset of teachers");
			std::stringstream test_stream;
			test_stream << array_int << '\n' << list_int << '\n' << array_double << '\n' << array_complex;
			std::string array_int_output, list_int_output, array_double_output, array_complex_output;
			std::getline(test_stream, array_int_output);
			std::getline(test_stream, list_int_output);
			std::getline(test_stream, array_double_output);
			std::getline(test_stream, array_complex_output);
			Assert::AreEqual(array_int_output, (std::string)"{ 1, 2, 3, 4, 5 }", L"Block 1 Test #6 failed: wrong output or content of arrayset of integer numbers");
			Assert::AreEqual(list_int_output, (std::string)"{ 1, 2, 3, 4, 5 }", L"Block 1 Test #7 failed: wrong output or content of listset of integer numbers");
			Assert::AreEqual(array_double_output, (std::string)"{ 1.1, 2.2, 3.3, 4.4 }", L"Block 1 Test #8 failed: wrong output or content of arrayset of real numbers");
			Assert::AreEqual(array_complex_output, (std::string)"{ 1 + 5.5 * i, 2 + 4.3 * i }", L"Block 1 Test #9 failed: wrong output or content of arrayset of integer numbers");
			
		}
		//intersection, combining and difference of the sets, subsets
		TEST_METHOD(BlockTest2) {
			Set<std::pair<int, int>, ListType> list1 = {std::pair<int, int>(1, 2), std::pair<int, int>(2, 2), std::pair<int, int>(5, 1)};
			Set<std::pair<int, int>, ListType> list2 = {std::pair<int, int>(2, 2), std::pair<int, int>(5, 3), std::pair<int, int>(2, 1), std::pair<int, int>(1, 2)};
			Set<std::pair<int, int>, ListType> comb1 = { std::pair<int, int>(1, 2), std::pair<int, int>(2, 2), std::pair<int, int>(5, 1), std::pair<int, int>(5, 3), std::pair<int, int>(2, 1) };
			Set<std::pair<int, int>, ListType> differ1 = { std::pair<int, int>(5, 1) };
			Set<std::pair<int, int>, ListType> intersect1 = { std::pair<int, int>(1, 2), std::pair<int, int>(2, 2) };
			Set<char, ArrayType> array1 = "Hello there";
			Set<char, ArrayType> array2 = "Hello world";
			Set<char, ArrayType> comb2 = "Hello there Hello world";
			Set<char, ArrayType> differ2 = { 't', 'h' };
			Set<char, ArrayType> intersect2 = "Hello r";
			Assert::IsTrue(list1 + list2 == comb1, L"Block 2 Test #1 failed: incorrect combining of sets");
			Assert::IsTrue(list1 - list2 == differ1, L"Block 2 Test #2 failed: incorrect difference of sets");
			Assert::IsTrue(list1 * list2 == intersect1, L"Block 2 Test #3 failed: incorrect intersection of sets");
			Assert::IsTrue(array1 + array2 == comb2, L"Block 2 Test #4 failed: incorrect combining of sets");
			Assert::IsTrue(array1 - array2 == differ2, L"Block 2 Test #5 failed: incorrect difference of sets");
			Assert::IsTrue(array1 * array2 == intersect2, L"Block 2 Test #6 failed: incorrect intersection of sets");
			Assert::IsTrue(list1.find(std::pair<int, int>(5, 1)), L"Block 2 Test #7 failed: an element that should be in the set cannot be found");
			Assert::IsFalse(list2.find(std::pair<int, int>(5, 1)), L"Block 2 Test #8 failed: an element that shouldn't be in the set was found");
			Assert::IsTrue(array1.issubset(intersect2), L"Block 2 Test #9 failed: intersection of the sets must be a subset for these sets");
			Assert::IsFalse(Set<char, ArrayType>("bcdefghijk").issubset(Set<char, ArrayType>("abcdefghijk")), L"Block 2 Test #10 failed: the set cannot be a subset of another set");
		}
		//map(), where() and cartesian_prod()
		TEST_METHOD(BlockTest3) {
			Set<int, ArrayType> set1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			Set<Student, ListType> set2 = {
				Student("Klinov Nikita Andreevich", 17, 514),
				Student("Ivanov Ivan Ivanich", 19, 312),
				Student("Kostyaev Artem Sergeevich", 18, 514),
				Student("Matyashov Andrey Alexandrovich", 18, 514),
				Student("Kurinnoy Andrey Igorevich", 18, 503)
			};
			Set<int, ArrayType> set3 = { 1, 2 };
			Set<int, ArrayType> set4 = { 2, 3, 4 };
			Set<int, ArrayType> result1 = set1.map([](int a)->int {return a * a; });
			set1 = set1.where([](int a)->bool {return a % 2 == 0; });
			Set<Student, ListType> result2 = set2.map([](Student st) {return Student(st.name().substr(0, st.name().find(' ')), st.age(), st.group()); });
			set2 = set2.where([](Student a) {return a.group() == 514; });
			Set<int, ArrayType> expected_result_1 = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
			Set<int, ArrayType> expected_result_2 = { 2, 4, 6, 8, 10 };
			Set<Student, ListType> expected_result_3 = {
				Student("Klinov", 17, 514),
				Student("Ivanov", 19, 312),
				Student("Kostyaev", 18, 514),
				Student("Matyashov", 18, 514),
				Student("Kurinnoy", 18, 503)
			};
			Set<Student, ListType> expected_result_4 = {
				Student("Klinov Nikita Andreevich", 17, 514),
				Student("Kostyaev Artem Sergeevich", 18, 514),
				Student("Matyashov Andrey Alexandrovich", 18, 514)
			};
			Set<std::pair<int, int>, ArrayType> expected_result_5 = {
				std::pair<int, int>(1, 2),
				std::pair<int, int>(1, 3),
				std::pair<int, int>(1, 4),
				std::pair<int, int>(2, 2),
				std::pair<int, int>(2, 3),
				std::pair<int, int>(2, 4)
			};
			Assert::IsTrue(result1 == expected_result_1, L"Block 3 Test #1 failed: map() doesn't work as it must");
			Assert::IsTrue(set1 == expected_result_2, L"Block 3 Test #2 failed: where() doesn't work as it must");
			Assert::IsTrue(result2 == expected_result_3, L"Block 3 Test #3 failed: map() doesn't work as it must");
			Assert::IsTrue(set2 == expected_result_4, L"Block 3 Test #4 failed: where() doesn't work as it must");
			Assert::IsTrue(cartesian_prod(set3, set4) == expected_result_5, L"Block 3 Test #5 failed: cartesian production doesn't work as it must");
		}
		//weird cases
		TEST_METHOD(BlockTest4) {
			Set<std::string, ArrayType> a, b, c = {"String"};
			Assert::IsTrue(a.issubset(b), L"Block 4 Test #1 failed: empty set must be a subset of itself");
			Assert::IsFalse(a.issubset(c), L"Block 4 Test #2 failed: non-empty set isn't a subset of the empty set");
			Assert::IsTrue(c == c - a, L"Block 4 Test #3 failed: difference between the set and the empty set should be equal to the set");
			Assert::IsTrue(c == c + b, L"Block 4 Test #4 failed: combining of the set and the empty set should be equal to the set");
			Assert::IsTrue(b == b - c, L"Block 4 Test #5 failed: difference between the empty set and any set should be equal to the empty set");
			Assert::IsTrue(a.map([](std::string s) {return s.substr(0, s.size() / 2); }) == a, L"Block 4 Test #6 failed: map of the empty set should be empty");
			
		}
		//arraytest
		TEST_METHOD(BlockTest5) {
			DynamicArray<int> arr1 = { 1, 2, 3, 4, 5, 6 };
			int arr_for_constructor[6] = { 5, 2, 4, 1, -3, 5 };
			DynamicArray<int> arr2 = arr_for_constructor;
			DynamicArray<int> arr3 = arr2;
			DynamicArray <double> arr4 = { 4.5, 3.1, 3.2, -2.44 };
			DynamicArray <double> arr5 = { -43.2, 53, 0, -3.141592 };
			DynamicArray<int> expected_result1 = { 1, 2, 3, 4, 5, 6, 7 };
			DynamicArray<int> expected_result2 = { 5, 2, 4, 1, -3, 10 };
			DynamicArray<int> expected_result3 = { 0, 5, 2, 4, 1, -3, 10 };
			DynamicArray<double> expected_result4 = { 4.5, 3.1, 3.2, -96.5, -2.44 };
			DynamicArray<double> expected_result5 = { -43.2, 0, -3.141592 };
			DynamicArray <int> expected_result6 = { 5, 2, 4, 1, -3, 5, 0, 5, 2, 4, 1, -3, 10 };
			arr1.append(7);
			Assert::IsTrue(arr3 == arr2, L"Block 5 Test #1 failed: assignment operator does not work as it must");
			Assert::IsTrue(arr1 == expected_result1, L"Block 5 Test #2 failed: append() does not work as it must");
			Assert::IsTrue(arr2[3] == 1, L"Block 5 Test #3 failed: operator [] doesn't work as it must");
			arr2[5] = 10;
			Assert::IsTrue(arr2 == expected_result2, L"Block 5 Test #4 failed: operator [] does not allow changing values in the array");
			Assert::ExpectException<DynamicArray<double>::DAException>([&arr4]() {arr4[4] = 0; }, L"Block 5 Test #4 failed: expected throwing DAException");
			arr2.prepend(0);
			Assert::IsTrue(arr2 == expected_result3, L"Block 5 Test #5 failed: prepend() does not work as it must");
			arr4.insert(-96.5, 3);
			Assert::IsTrue(arr4 == expected_result4, L"Block 5 Test #6 failed: insert() does not work as it must");
			Assert::IsTrue(arr5.find(53) == 1, L"Block 5 Test #7 failed: find() does not work as it must");
			arr5.erase(1);
			Assert::IsTrue(arr5 == expected_result5, L"Block 5 Test #8 failed: erase() does not work as it must");
			arr3 += arr2;
			Assert::IsTrue(arr3 == expected_result6, L"Block 5 Test #9 failed: concatenation of arrays does not work as it must");
			arr3.clear();
			Assert::IsTrue(arr3 == DynamicArray<int>(), L"Block 5 Test #10 failed: clear() does not work as it must");
		}
		//listtest
		TEST_METHOD(BlockTest6) {
			LinkedList<complex> arr1 = { complex(1, 3.8), complex(-2.5, 2), complex(0), complex(9.43, -3.2) };
			LinkedList<complex> arr2 = { complex(4.3, -7), complex(0, -8.78), complex(1.1, -5.3), complex(7.3, -9.21) };
			LinkedList<complex> arr3 = arr2;
			LinkedList<char> arr4 = "BgiFmcOEae\nsf";
			LinkedList<char> arr5 = "JGokOmverq";
			LinkedList<complex> expected_result1 = { complex(1, 3.8), complex(-2.5, 2), complex(0), complex(9.43, -3.2), complex(1, 3.8) };
			LinkedList<complex> expected_result2 = { complex(1, 3.8), complex(-2.5, 2), complex(23.313, -54.2), complex(9.43, -3.2), complex(1, 3.8) };
			LinkedList<char> expected_result3 = "tBgiFmcOEae\nsf";
			LinkedList<char> expected_result4 = "JGokOmYverq";
			LinkedList<complex> expected_result5 = { complex(4.3, -7), complex(1.1, -5.3), complex(7.3, -9.21) };
			LinkedList<complex> expected_result6 = { complex(4.3, -7), complex(1.1, -5.3), complex(7.3, -9.21), complex(1, 3.8), complex(-2.5, 2), complex(23.313, -54.2), complex(9.43, -3.2), complex(1, 3.8) };
			Assert::IsTrue(arr3 == arr2, L"Block 6 Test #1 failed: assignment operator does not work as it must");
			arr1.append(complex(1, 3.8));
			Assert::IsTrue(arr1 == expected_result1, L"Block 6 Test #2 failed: append() does not work as it must");
			Assert::IsTrue(arr2[3] == complex(7.3, -9.21), L"Block 6 Test #3 failed: operator [] doesn't work as it must");
			arr1[2] = complex(23.313, -54.2);
			Assert::IsTrue(arr1 == expected_result2, L"Block 6 Test #4 failed: operator [] does not allow changing values in the array");
			Assert::ExpectException<LinkedList<char>::LLException>([&arr4]() {arr4[20] = 'P'; }, L"Block 5 Test #4 failed: expected throwing LLException");
			arr4.prepend('t');
			Assert::IsTrue(arr4 == expected_result3, L"Block 6 Test #5 failed: prepend() does not work as it must");
			Assert::IsTrue(arr5.find('a') == -1, L"Block 6 Test #6 failed: find() does not work as it must");
			arr5.insert('Y', 6);
			Assert::IsTrue(arr5 == expected_result4, L"Block 6 Test #7 failed: insert() does not work as it must");
			arr3.erase(1);
			Assert::IsTrue(arr3 == expected_result5, L"Block 5 Test #8 failed: erase() does not work as it must");
			arr3 += arr1;
			Assert::IsTrue(arr3 == expected_result6, L"Block 5 Test #9 failed: concatenation of arrays does not work as it must");
			arr4.clear();
			Assert::IsTrue(arr4 == LinkedList<char>(), L"Block 5 Test #10 failed: clear() does not work as it must");
		}
	};
}
