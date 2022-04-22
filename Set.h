#pragma once
#include "Sequence.h"
#include <ostream>
enum choosable_type {
	ListType, ArrayType
};
template <class T, choosable_type container>
class Set {
	Sequence<T>* cont;
	void clean() {
		for (size_t i = 0; i < size(); i++) {
			for (size_t j = 0; j < i; j++) {
				if ((*cont)[j] == (*cont)[i]) { //1 2 1 3
					cont->erase(i);
					i--;
					break;
				}
			}
		}
	}
	
public:
	class SetException {
	private:
		size_t id;
	public:
		SetException(size_t id) { this->id = id; }
		const char* message() {
			if (id == 1) return "Error 1: Bad allocation of memory.";
			if (id == 2) return "Error 2: set subscript out of range.";
		}
	};
	Set() {
		try {
			if (container) cont = new ArraySequence<T>;
			else cont = new ListSequence<T>;
		}
		catch (std::bad_alloc) {
			throw SetException(1);
		}
	}
	Set(Sequence<T>* other) : Set(){
		*cont = *other;
		clean();
	}
	template <size_t len>
	Set(const T(&items)[len]) : Set() {
		if (container) *((ArraySequence<T>*)cont) = items;
		else *((ListSequence<T>*)cont) = items;
		clean();
	}
	Set(const std::initializer_list<T>& items) : Set() {
		if (container) *((ArraySequence<T>*)cont) = items;
		else *((ListSequence<T>*)cont) = items;
		clean();
	}
	Set(const Set<T, container>& other) : Set() {
		if (container) *((ArraySequence<T>*)cont) = *((ArraySequence<T>*)other.cont);
		else *((ListSequence<T>*)cont) = *((ListSequence<T>*)other.cont);
	}
	Set(Set<T, container>&& other) {
		cont = other.cont;
		try {
			if (container) other.cont = new ArraySequence<T>;
			else other.cont = new ListSequence<T>;
		}
		catch (std::bad_alloc) {
			throw SetException(1);
		}
	}
	~Set() {
		(*cont).clear();
		delete cont;
	}
	/*								methods						*/
	size_t size() const {
		return cont->length();
	}
	bool find(const T& value) const {
		return cont->find(value) != -1;
	}
	bool issubset(const Set<T, container>& other) const {
		for (size_t i = 0; i < other.size(); i++) {
			if (!find((*(other.cont))[i])) return false;
		}
		return true;
	}
	Set map(T func(T)) const {
		Set<T, container> ans;
		for (size_t i = 0; i < size(); i++) {
			ans.add(func((*cont)[i]));
		}
		return ans;
	}
	Set where(bool func(T)) const {
		Set ans = *this;
		for (size_t i = 0; i < ans.size(); i++) {
			if (!func((*(ans.cont))[i])) {
				ans.cont->erase(i);
				i--;
			}
		}
		return ans;
	}
	void add(T value) {
		if (!find(value)) cont->append(value);
	}
	bool operator== (const Set<T, container>& other) const {
		if (size() != other.size()) return false;
		for (size_t i = 0; i < size(); i++) {
			if (!other.find((*cont)[i])) return false;
		}
		return true;
	}
	bool operator!= (const Set<T, container>& other) const {
		return !(*this == other);
	}
	Set& operator= (const Set<T, container>& other) {
		cont->clear();
		if (container) *((ArraySequence<T>*)cont) = *((ArraySequence<T>*)other.cont);
		else *((ListSequence<T>*)cont) = *((ListSequence<T>*)other.cont);
		return *this;
	}
	Set& operator+= (const Set<T, container>& other) {
		for (size_t i = 0; i < other.size(); i++) {
			if (!find((*(other.cont))[i])) cont->append((*(other.cont))[i]);
		}
		return *this;
	}
	Set& operator-= (const Set<T, container>& other) {
		for (size_t i = 0; i < other.size(); i++) {
			int index = cont->find((*(other.cont))[i]);
			if (index != -1) cont->erase(index);
		}
		return *this;
	}
	Set& operator*= (const Set<T, container>& other) {
		for (size_t i = 0; i < size(); i++) {
			if (!other.find((*cont)[i])) {
				cont->erase(i);
				i--;
			}
		}
		return *this;
	}
	Set operator+ (const Set<T, container>& other) const {
		Set<T, container> ans = *this;
		ans += other;
		return ans;
	}
	Set operator- (const Set<T, container>& other) const {
		Set<T, container> ans = *this;
		return ans -= other;
	}
	Set operator* (const Set<T, container>& other) const {
		Set<T, container> ans = *this;
		return ans *= other;
	}
	template <class T1, choosable_type container_>
	friend Set<std::pair<T1, T1>, container_> cartesian_prod(const Set<T1, container_>&, const Set<T1, container_>&);
	template <class T1, choosable_type container_>
	friend std::ostream& operator<< (std::ostream&, const Set<T1, container_>&);
};
//
template <class T1, choosable_type container_> 
Set<std::pair<T1, T1>, container_> cartesian_prod(const Set<T1, container_>& s1, const Set<T1, container_>& s2) {
	Set<std::pair<T1, T1>, container_> ans;
	for (size_t i = 0; i < s1.size(); i++) {
		for (size_t j = 0; j < s2.size(); j++) {
			ans.cont->append(std::pair<T1, T1>((*(s1.cont))[i], (*(s2.cont))[j]));
		}
	}
	return ans;
}
template <class T1, choosable_type container_>
std::ostream& operator<< (std::ostream& os, const Set<T1, container_>& s) {
	if (s.size() == 0) os << "{}";
	else {
		os << "{ ";
		size_t size = s.size();
		for (size_t i = 0; i < size; i++) {
			if (i != size - 1) os << (*(s.cont))[i] << ", ";
			else os << (*(s.cont))[i];
		}
		os << " }";
	}
	return os;
}