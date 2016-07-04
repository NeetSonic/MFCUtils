//--------------------------------
// LinkStructs for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

//------------------------------------------------
// 特性：
//      1.链式数据结构，有常见的链表，栈，队列等结构
//------------------------------------------------

#pragma once
#include "MFCUtils.h"
using namespace MFCUtils;

template<class T> class LinkUnit {
public:
	T m_val;
	LinkUnit* m_pPrev;
	LinkUnit* m_pNext;

public:
	LinkUnit(LinkUnit* prev = NULL, LinkUnit* next = NULL);
	LinkUnit(const T & t, LinkUnit* prev = NULL, LinkUnit* next = NULL);
	~LinkUnit();

private:
	explicit LinkUnit(const LinkUnit & lu) {}
	LinkUnit & operator=(const LinkUnit & lu) {}
};
template<class T>
LinkUnit<T>::LinkUnit(LinkUnit* prev /* = NULL */, LinkUnit* next /* = NULL */) : m_pPrev(prev), m_pNext(next) {}
template<class T>
LinkUnit<T>::LinkUnit(const T & t, LinkUnit* prev /* = NULL */, LinkUnit* next /* = NULL */) : m_val(t), m_pPrev(prev), m_pNext(next) {}
template<class T>
LinkUnit<T>::~LinkUnit() {}

template<class T> class LinkList {
public:
	int m_nCount;
	LinkUnit<T>* m_pHead;
	LinkUnit<T>* m_pTail;

public:
	LinkList();
	explicit LinkList(const LinkList & ll);
	~LinkList();
	void Clear();
	const T* Append(const T & t); // Returns the pointer to the element appended.
	const T* Insert(int idx, const T & t); // Returns the pointer to the element inserted, NULL if failed.
	bool Delete(int idx); // Returns true if succeed, otherwise false.
	bool DeleteFirst();
	const int & GetCount() const;
	const T* GetValPtr(int idx) const; // Returns NULL if failed.
	LinkUnit<T>* GetFirstLinkUnitPtr() const; // Returns NULL if the list is empty.
	LinkUnit<T>* GetNextLinkUnitPtr(LinkUnit<T>* p) const; // Returns NULL if reaches end or failed.
	LinkList<T> & operator=(const LinkList & ll);
	void Sort(int(*cmp)(T*, T*));
	void Reverse();
	int InsertBySort(const T & t, int(*cmp)(T*, T*)); // Returns index of the inserted element.

private:
	void SwapVal(LinkUnit<T>* a, LinkUnit<T>* b);
	void QuickSort(LinkUnit<T>* left, LinkUnit<T>* right, int(*cmp)(T*, T*));
};
template<class T>
LinkList<T>::LinkList() : m_nCount(0) {
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
}
template<class T>
LinkList<T>::LinkList(const LinkList & ll) : m_nCount(0) {
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
	LinkUnit<T>* p;
	p = ll.GetFirstLinkUnitPtr();
	if(p) {
		do { Append(p->m_val); } while(p = ll.GetNextLinkUnitPtr(p));
	}
}
template<class T>
LinkList<T>::~LinkList() {
	LinkUnit<T>* p;
	while(m_pHead != m_pTail) {
		p = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete p;
	}
	delete m_pTail;
}
template<class T>
inline const int & LinkList<T>::GetCount() const { return m_nCount; }
template<class T>
void LinkList<T>::Clear() {
	LinkUnit<T>* p;
	while(m_pHead != m_pTail) {
		p = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete p;
	}
	delete m_pTail;
	m_nCount = 0;
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
}
template<class T>
const T* LinkList<T>::Append(const T & t) {
	m_pTail->m_val = t;
	m_pTail = m_pTail->m_pNext = new LinkUnit<T>(m_pTail);
	m_nCount++;
	return &(m_pTail->m_pPrev->m_val);
}
template<class T>
const T* LinkList<T>::Insert(int idx, const T & t) {
	ASSERT((idx >= 0) && (idx <= m_nCount));
	if((idx > m_nCount) || (idx < 0)) return NULL;
	LinkUnit<T>* p;
	p = m_pHead;
	while(idx--) p = p->m_pNext;
	p->m_pNext = p->m_pNext->m_pPrev = new LinkUnit<T>(t, p, p->m_pNext);
	m_nCount++;
	return &(p->m_pNext->m_val);
}
template<class T>
bool LinkList<T>::Delete(int idx) {
	ASSERT((idx >= 0) && (idx < m_nCount));
	if((idx >= m_nCount) || (idx < 0)) return false;
	LinkUnit<T>* p;
	p = m_pHead->m_pNext;
	while(idx--) p = p->m_pNext;
	p->m_pPrev->m_pNext = p->m_pNext;
	p->m_pNext->m_pPrev = p->m_pPrev;
	delete p;
	m_nCount--;
	return true;
}
template<class T>
bool LinkList<T>::DeleteFirst() {
	return Delete(0);
}
template<class T>
const T* LinkList<T>::GetValPtr(int idx) const {
	ASSERT((idx >= 0) && (idx < m_nCount));
	if((idx >= m_nCount) || (idx < 0)) return NULL;
	if((idx >= m_nCount) || (idx < 0)) return NULL;
	LinkUnit<T>* p;
	p = m_pHead->m_pNext;
	while(idx--) p = p->m_pNext;
	return &(p->m_val);
}
template<class T>
LinkUnit<T>* LinkList<T>::GetFirstLinkUnitPtr() const {
	return (m_nCount) ? m_pHead->m_pNext : NULL;
}
template<class T>
LinkUnit<T>* LinkList<T>::GetNextLinkUnitPtr(LinkUnit<T>* p) const {
	ASSERT(p);
	return ((p) && (p->m_pNext != m_pTail)) ? p->m_pNext : NULL;
}
template<class T>
LinkList<T> & LinkList<T>::operator=(const LinkList & ll) {
	if(this != &ll) {
		Clear();
		LinkUnit<T>* p;
		p = ll.GetFirstLinkUnitPtr();
		if(p) {
			do { Append(p->m_val); } while(p = ll.GetNextLinkUnitPtr(p));
		}
	}
	return *this;
}
template<class T>
void LinkList<T>::SwapVal(LinkUnit<T>* a, LinkUnit<T>* b) {
	if(a != b) {
		T temp;
		temp = a->m_val;
		a->m_val = b->m_val;
		b->m_val = temp;
	}
}
template<class T>
void LinkList<T>::QuickSort(LinkUnit<T>* left, LinkUnit<T>* right, int(*cmp)(T*, T*)) {
	// 根据算法确保传入的left的位置在right之前或者和right一样，或者right之后一位，才可使用此算法编程
	if((left->m_pPrev != right) && (left != right)) {
		LinkUnit<T> *pCurr, *pPivot;
		pPivot = left;
		pCurr = left->m_pNext;
		while(pCurr != right->m_pNext) {
			if((*cmp)(&(pCurr->m_val), &(left->m_val)) < 0) {
				pPivot = pPivot->m_pNext;
				SwapVal(pCurr, pPivot);
			}
			pCurr = pCurr->m_pNext;
		}
		SwapVal(left, pPivot);
		QuickSort(left, pPivot->m_pPrev, cmp);
		QuickSort(pPivot->m_pNext, right, cmp);
	}
}
template<class T>
void LinkList<T>::Sort(int(*cmp)(T*, T*)) {
	// It doesn't make any sence to sort when length is below 2.
	if(m_nCount > 1) QuickSort(m_pHead->m_pNext, m_pTail->m_pPrev, cmp);
}
template<class T>
void LinkList<T>::Reverse() {
	if(m_nCount > 1) {
		LinkUnit<T> *pLeft, *pRight;
		pLeft = m_pHead->m_pNext;
		pRight = m_pTail->m_pPrev;
		while((pLeft->m_pPrev != pRight) && (pLeft != pRight)) {
			SwapVal(pLeft, pRight);
			pLeft = pLeft->m_pNext;
			pRight = pRight->m_pPrev;
		}
	}
}
template<class T>
int LinkList<T>::InsertBySort(const T & t, int(*cmp)(T*, T*)) {
	int nIndex;
	LinkUnit<T>* p;
	nIndex = 0;
	p = m_pHead->m_pNext;
	while(p != m_pTail) {
		if(cmp(&(p->m_val), &t) < 0) {
			p = p->m_pNext;
			nIndex++;
		}
		else break;
	}
	Insert(nIndex, t);
	return nIndex;
}

template<class T> class LinkQueue {
public:
	int m_nCount;
	LinkUnit<T>* m_pHead;
	LinkUnit<T>* m_pTail;

public:
	LinkQueue();
	~LinkQueue();
	void Clear();
	const T* Enqueue(const T & t); // Returns the pointer to the element enqueued.
	bool Dequeue(T & dequeued);
	const int & GetCount() const;

private:
	explicit LinkQueue(const LinkQueue & lq);
	LinkList<T> & operator=(const LinkQueue & lq);
};
template<class T>
LinkQueue<T>::LinkQueue() : m_nCount(0) {
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
}
template<class T>
LinkQueue<T>::~LinkQueue() {
	LinkUnit<T>* p;
	while(m_pHead != m_pTail) {
		p = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete p;
	}
	delete m_pTail;
}
template<class T>
void LinkQueue<T>::Clear() {
	LinkUnit<T>* p;
	while(m_pHead != m_pTail) {
		p = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete p;
	}
	delete m_pTail;
	m_nCount = 0;
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
}
template<class T>
const T* LinkQueue<T>::Enqueue(const T & t) {
	m_pTail->m_val = t;
	m_pTail = m_pTail->m_pNext = new LinkUnit<T>(m_pTail);
	m_nCount++;
	return &(m_pTail->m_pPrev->m_val);
}
template<class T>
bool LinkQueue<T>::Dequeue(T & t) {
	ASSERT(m_nCount > 0);
	if(m_nCount > 0) {
		LinkUnit<T>* p;
		p = m_pHead->m_pNext;
		p->m_pPrev->m_pNext = p->m_pNext;
		p->m_pNext->m_pPrev = p->m_pPrev;
		t = p->m_val;
		delete p;
		m_nCount--;
		return true;
	}
	else return false;
}
template<class T>
inline const int & LinkQueue<T>::GetCount() const { return m_nCount; }

template<class T> class LinkStack {
public:
	int m_nCount;
	LinkUnit<T>* m_pHead;
	LinkUnit<T>* m_pTail;

public:
	LinkStack();
	~LinkStack();
	void Clear();
	const T* Push(const T & t); // Returns the pointer to the element pushed.
	bool Pop(T & poped);
	const T* GetTop();
	const int & GetCount() const;

private:
	explicit LinkStack(const LinkStack & lq);
	LinkStack<T> & operator=(const LinkStack & lq);
};
template<class T>
LinkStack<T>::LinkStack() : m_nCount(0) {
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
}
template<class T>
LinkStack<T>::~LinkStack() {
	LinkUnit<T>* p;
	while(m_pHead != m_pTail) {
		p = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete p;
	}
	delete m_pTail;
}
template<class T>
void LinkStack<T>::Clear() {
	LinkUnit<T>* p;
	while(m_pHead != m_pTail) {
		p = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete p;
	}
	delete m_pTail;
	m_nCount = 0;
	m_pHead = new LinkUnit<T>();
	m_pHead->m_pNext = m_pTail = new LinkUnit<T>(m_pHead);
}
template<class T>
const T* LinkStack<T>::Push(const T & t) {
	m_pHead->m_pNext = m_pHead->m_pNext->m_pPrev = new LinkUnit<T>(t, m_pHead, m_pHead->m_pNext);
	m_nCount++;
	return &(m_pHead->m_pNext->m_val);
}
template<class T>
bool LinkStack<T>::Pop(T & t) {
	ASSERT(m_nCount > 0);
	if(m_nCount > 0) {
		LinkUnit<T>* p;
		p = m_pHead->m_pNext;
		p->m_pPrev->m_pNext = p->m_pNext;
		p->m_pNext->m_pPrev = p->m_pPrev;
		t = p->m_val;
		delete p;
		m_nCount--;
		return true;
	}
	else return false;
}
template<class T>
const T* LinkStack<T>::GetTop() {
	if(m_nCount <= 0) return NULL;
	return &(m_pHead->m_pNext->m_val);
}
template<class T>
inline const int & LinkStack<T>::GetCount() const { return m_nCount; }