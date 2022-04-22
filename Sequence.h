#pragma once
#include "DynamicArray.h"
#include "LinkedList.h"
template <class T>
class Sequence {
public:
	virtual size_t length() const = 0;
	virtual T get_first() const = 0;
	virtual T get_last() const = 0;
	virtual Sequence<T>* subseq(const size_t, const size_t) const = 0;
	virtual void append(const T) = 0;
	virtual void clear() = 0;
	virtual void prepend(const T) = 0;
	virtual void insert(const T, const size_t) = 0;
	virtual void erase(const size_t) = 0;
	virtual int find(const T) const = 0;
	/*													operators													*/
	virtual bool operator== (const Sequence<T>*) const = 0;
	bool operator!= (const Sequence<T>* other) const {
		return !(*this == other);
	}
	virtual T& operator[] (const size_t) const = 0;
	virtual Sequence<T>* operator+= (const Sequence<T>*) = 0;
	Sequence<T>* operator+ (const Sequence<T>* other) const {
		Sequence<T> ans = *this;
		return ans += other;
	}
};

#define DECL_(TYPE, TYPE_CLASS, type)  class TYPE##Sequence : public Sequence<T>{			\
private:																																				\
	TYPE_CLASS##<T> arr;																													\
public:																																					\
	TYPE##Sequence() = default;																											\
	template <size_t len> TYPE##Sequence(const T(&items)[len]) {													\
		arr = items;																																	\
	}																																						\
	TYPE##Sequence(const std::initializer_list<T>& items) {																\
		arr = items;																																	\
	}																																						\
	TYPE##Sequence(const Sequence<T>* other) {																			\
		arr = other->arr;																															\
	}																																						\
	size_t length() const override {																										\
		return arr.length();																														\
	}																																						\
	T get_first() const override {																											\
		return arr[0];																																\
	}																																						\
	T get_last() const override {																											\
		return arr[arr.length() - 1];																											\
	}																																						\
	void clear() override {																													\
		arr.clear();																																	\
	}																																						\
	void append(const T value) override {																							\
		return arr.append(value);																											\
	}																																						\
	void prepend(const T value) override {																							\
		return arr.prepend(value);																											\
	}																																						\
	int find(const T value) const override {																							\
		return arr.find(value);																												\
	}																																						\
	Sequence<T>* subseq(const size_t begin, const size_t end) const override {								\
		TYPE##Sequence<T> ans;																											\
		ans.arr = arr.sub##type(begin, end);																							\
		return &ans;																																\
	}																																						\
	void insert(const T value, const size_t index) override {																\
		arr.insert(value, index);																												\
	}																																						\
	void erase(const size_t index) override {																						\
		arr.erase(index);																															\
	}																																						\
	bool operator== (const Sequence<T>* other) const override {														\
		return arr == ((const TYPE##Sequence<T>*)other)->arr;															\
	}																																						\
	T& operator[] (const size_t index) const override {																		\
		return arr[index];																														\
	}																																						\
	Sequence<T>* operator+= (const Sequence<T>* other) override {												\
		arr += ((const TYPE##Sequence<T>*)other)->arr;																	\
		return this;																																	\
	}																																						\
};							
template <class T>
DECL_(Array, DynamicArray, array)
template <class T>
DECL_(List, LinkedList, list)