//--------------------------------
// FixedStructs for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

//------------------------------------------------
// 特性：
//      1.数组式数据结构，有列表等结构
//------------------------------------------------

template<class T> class FixedList { // class T must have defined the assignment operator '='
private:
	int m_nLength;
	T* m_pHead;
	T* m_pCurr;

public:
	enum { FL_SET_LENGTH_FAILED = -1 }; // Error code.
	FixedList(const int & len = 0); // Default constructor.
	~FixedList();
	explicit FixedList(const FixedList & list);
	int SetLength(const int & len); // Returns length of this list if succeed, returns -1 if failed. 
	void Clear();
	bool IsFull() const;
	T* Add(const T & t); // Returns the pointer to the element just added if succeed, returns NULL if failed.
	T* GetFirstElemPtr() const; // Returns NULL if failed.
	T* GetNextElemPtr(T* curr) const; // Returns NULL if reaches end.
	T* GetElem(int num) const; // Returns NULL if failed.
	int GetLength() const;
	void Sort(int(*cmp)(T*, T*));
	void Reverse();
	FixedList<T>& operator=(const FixedList<T> & list);
	T& operator[](int idx); // Element can be assigned particularly.
	const T& operator[](int idx) const; // Use a specific element to assign other variables. 

private:
	void QuickSort(T* left, T* right, int(*cmp)(T*, T*));
	void Swap(T* a, T* b);
};
template<class T>
FixedList<T>::FixedList(const int & len/* = 0 */) :m_nLength(0), m_pHead(NULL), m_pCurr(NULL) {
	SetLength(len);
}
template<class T>
FixedList<T>::~FixedList() {
	Clear();
}
template<class T>
FixedList<T>::FixedList(const FixedList & list) :m_nLength(0), m_pHead(NULL), m_pCurr(NULL) {
	bool bValid;
	bValid = list.IsFull();
	ASSERT(bValid);
	if(bValid) {
		T* p;
		SetLength(list.GetLength());
		p = list.GetFirstElemPtr();
		if(p) {
			do { Add(*p); } while(p = list.GetNextElemPtr(p));
		}
	}
}
template<class T>
inline int FixedList<T>::GetLength() const {
	return m_nLength;
}
template<class T>
void FixedList<T>::Clear() {
	MultiDelete(m_pHead);
	m_pCurr = NULL;
	m_nLength = 0;
}
template<class T>
int FixedList<T>::SetLength(const int & len) {
	ASSERT(len >= 0);
	if(len < 0) return FL_SET_LENGTH_FAILED;
	m_nLength = len;
	if(m_nLength) {
		m_pCurr = m_pHead = new T[m_nLength];
		memset(m_pHead, 0, static_cast<size_t>(sizeof(T)*m_nLength));
	}
	return len;
}
template<class T>
T* FixedList<T>::Add(const T & t) {
	if(IsFull()) return NULL;
	*m_pCurr++ = t;
	return (m_pCurr - 1);
}
template<class T>
bool FixedList<T>::IsFull() const {
	return (m_pCurr == m_pHead + m_nLength);
}
template<class T>
T* FixedList<T>::GetFirstElemPtr() const {
	return IsFull() ? m_pHead : NULL;
}
template<class T>
T* FixedList<T>::GetNextElemPtr(T* curr) const {
	ASSERT(curr);
	ASSERT((curr >= m_pHead) && (curr < m_pHead + m_nLength));
	return (curr && (curr >= m_pHead) && (++curr < m_pHead + m_nLength)) ? curr : NULL;
}
template<class T>
T* FixedList<T>::GetElem(int num) const {
	ASSERT((num >= 0) && (num < m_nLength));
	if((num >= 0) && (num < m_nLength)) {
		T* p;
		p = m_pHead;
		while(num--) p++;
		return p;
	}
	return NULL;
}
template<class T>
void FixedList<T>::Sort(int(*cmp)(T*, T*)) {
	// It doesn't make any sence to sort when length is below 2.
	if(m_nLength > 1) QuickSort(m_pHead, m_pHead + m_nLength - 1, cmp);
}
template<class T>
void FixedList<T>::QuickSort(T* left, T* right, int(*cmp)(T*, T*)) {
	if(left < right) {
		T *pCurr, *pPivot;
		pPivot = left;
		pCurr = left + 1;
		while(pCurr <= right) {
			if((*cmp)(pCurr, left) < 0) Swap(pCurr++, ++pPivot);
		}
		Swap(left, pPivot);
		QuickSort(left, pPivot - 1, cmp);
		QuickSort(pPivot + 1, right, cmp);
	}
}
template<class T>
void FixedList<T>::Swap(T* a, T* b) {
	if(a != b) {
		T temp;
		temp = *a;
		*a = *b;
		*b = temp;
	}
}
template<class T>
FixedList<T>& FixedList<T>::operator=(const FixedList<T> & list) {
	if(this != &list) { // Prevent from self-assignment.
		bool bValid;
		bValid = list.IsFull();
		ASSERT(bValid);
		if(bValid) {
			T* p;
			Clear();
			SetLength(list.GetLength());
			p = list.GetFirstElemPtr();
			if(p) {
				do { Add(*p); } while(p = list.GetNextElemPtr(p));
			}
		}
	}
	return *this;
}
template<class T>
T& FixedList<T>::operator[](int idx) {
	ASSERT((idx >= 0) && (idx < m_nLength));
	T* p;
	p = m_pHead;
	while(idx--) p++;
	return *p;
}
template<class T>
const T& FixedList<T>::operator[](int idx) const {
	ASSERT((idx >= 0) && (idx < m_nLength));
	T* p;
	p = m_pHead;
	while(idx--) p++;
	return *p;
}
template<class T>
void FixedList<T>::Reverse() {
	if(m_nLength >= 2) {
		T *pLeft, *pRight;
		pLeft = m_pHead;
		pRight = m_pHead + m_nLength - 1;
		while(pLeft < pRight) {
			Swap(pLeft, pRight);
			pLeft++;
			pRight--;
		}
	}
}