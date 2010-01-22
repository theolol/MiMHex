/*
 * LimitedSet.h Implementuje zbiór z góry ograniczoną liczą elementów.
 *
 *  Created on: 2010-01-21
 *      Author: Michał Albrycht
 */

#ifndef LIMITEDSET_H_
#define LIMITEDSET_H_

#include "conditional_assert.h"
#include "Rand.h"


template <typename T, unsigned MAXIMUM>
class LimitedSet;


template <typename T, unsigned MAXIMUM>
class LimitedSetIterator{
public:

	T Next(){
		ASSERT(!End());
		return set.elements[position++];
	}

	T Get(){
		ASSERT(!End());
		return set[position];
	}

	bool End() {
		return position >= set.elem_count;
	}

private:
	LimitedSetIterator(const LimitedSet<T, MAXIMUM>& set_itr) : position(0), set(set_itr) { }
	uint position;
	LimitedSet<T, MAXIMUM> set;
	friend class LimitedSet<T, MAXIMUM>;
};



template <typename T, unsigned MAXIMUM>
class LimitedSet {
public:
	static const uint InvalidPosition = -1;
	LimitedSet() : elem_count(0) { };

	void Insert(T& elem) {
		ASSERT(!IsFull());
		if (!Contains(elem))
			elements[elem_count++] = elem;
	}

	void Remove(T& elem) {
		if (Contains(elem)){
			elements[GetPosition(elem)] = elements[--elem_count];
		}
	}

	bool IsFull() const {
		return elem_count >= MAXIMUM;
	}

	bool Contains(T& elem) const {
		for (uint i=0; i<elem_count; ++i){
			if (elements[i] == elem)
				return true;
		}
		return false;
	}

	void Clear() {
		elem_count = 0;
	}

	bool Empty() const{
		return elem_count == 0;
	}

	int Size() const{
		return (int) elem_count;
	}

	LimitedSetIterator<T, MAXIMUM> GetIterator(){
		return LimitedSetIterator<T, MAXIMUM> (*this);
	}

	T RandomElem() const{
		ASSERT(!Empty());
		int rand  = Rand::next_rand(elem_count);
		return elements[rand];
	}

	virtual ~LimitedSet() {}

private:
	uint elem_count;
	T elements[MAXIMUM];

	uint GetPosition(T& elem){
		for (uint i=0; i<elem_count; ++i){
			if (elements[i] == elem)
				return i;
		}
		return InvalidPosition;
	}
	friend class LimitedSetIterator<T, MAXIMUM>;
};

#endif /* BRIDGESET_H_ */
