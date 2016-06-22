#pragma once
#include "stdafx.h"

//--------------------标准数字定义--------------------
#ifndef MAX_PATH
#define MAX_PATH 260
#endif /* MAX_PATH */
#define BUFFER_SIZE MAX_PATH

//--------------------字符（串）操作相关定义--------------------
#define BACK_SLASH '\\'
#define DOT_W L'.'
#define EMPTY_WCS L""
#define SPACE_WCS L" "
#define SEMICOLON_WCS L";"
#define BACK_SLASH_WCS L"\\"
#define NEW_LINE_WCS L"\r\n"
#define LEFT_SQUARE_BRACKET_WCS L"["
#define RIGHT_SQUARE_BRACKET_WCS L"]"
#define WCHAR_UPPER_CASE_A L'A'
#define WCHAR_PLUS L'+'
#define WCHAR_MINUS L'-'
#define WCHAR_MULTIPLE L'*'
#define WCHAR_DIVIDE L'/'
#define WCHAR_LEFT_BRACKET L'('
#define WCHAR_RIGHT_BRACKET L')'
#define WCHAR_LEFT_BRACKET_DOUBLE_BYTE L'（'
#define WCHAR_RIGHT_BRACKET_DOUBLE_BYTE L'）'

//--------------------常用宏操作--------------------
#define CHECK_HRESULT(hr, errMsgW) if(FAILED(hr)) AfxMessageBox(errMsgW)
#define WCS_SIZE_IN_WORDS(buff) (sizeof(buff) / sizeof(wchar_t))

//--------------------MFC控件常用相关值定义--------------------
#define LC_NOT_SELECTED -1
#define CSTRING_FIND_FAILED -1
#define SINGLE_ALPHABET_COUNT 26

namespace MFCUtils {
	//--------------------类声明--------------------
	template<class T> class FixedList;
	template<class T> class LinkUnit;
	template<class T> class LinkList;

	//--------------------字符（串）操作相关--------------------
	void UnicodeToAnsi(const wchar_t* srcStr, char* destStr, const UINT & nMaxBytesToConvert);
	void UnicodeToUTF8(const wchar_t* srcStr, char* destStr, const UINT & nMaxBytesToConvert);
	void AnsiToUnicode(const char* srcStr, wchar_t* destStr, const UINT & nMaxWordsToConvert);
	void WcscpyPtr(wchar_t** dstPtrAddr, const wchar_t* src); // 拷贝至Heap空间中的连续字符串
	void WcscpyArray(wchar_t* dstArr, const size_t & sizeInWords, const wchar_t* src); // 拷贝至Stack空间中的字符串（字符数组）
	bool WcsEndWith(const CString & cs, const wchar_t* endStr);

	//--------------------实用功能--------------------
	int GetCurrYear();
	CString GetCTimeFormatString(CTime & time);

	//--------------------文件操作--------------------
	void GetFileSizeWcs(CString path, wchar_t *buf, int maxWordCount);
	void RemoveFilePostfix(CString & filePath);
	void GetPathFilePostfix(const wchar_t* filePath, CString & postfix);
	void GetPathFileName(const wchar_t* filePath, CString & name);
	void GetFileDirectory(const wchar_t* filePath, CString & csDir);
	void EnsureDirExist(const wchar_t* dir);
	BOOL SmartCopyFile(const wchar_t* lpExistingFileName, const wchar_t* lpNewFileName, BOOL bFailIfExists); // 如果指定的目标路径不存在将自动创建

	//--------------------打开对话框操作--------------------
	BOOL ShowFolderDlg(wchar_t* pWcsGetPath, BFFCALLBACK callback = NULL);
	int ShowMultiFileDlg(LinkList<CString>* queue);
	int ShowSingleFileDlg(CString & filePath);

	//--------------------释放指针模版--------------------
	template<class T>
	void SingleDelete(T & t) {
		if(t) {
			delete t;
			t = NULL;
		}
	}
	template<class T>
	void MultiDelete(T & t) {
		if(t) {
			delete[]t;
			t = NULL;
		}
	}

	//--------------------常用数据结构模版--------------------
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
	LinkQueue<T>::LinkQueue() : m_nCount(0){
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
		} else return false;
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
	LinkStack<T>::LinkStack() : m_nCount(0){
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
		} else return false;
	}
	template<class T>
	const T* LinkStack<T>::GetTop() {
		if(m_nCount <= 0) return NULL;
		return &(m_pHead->m_pNext->m_val);
	}
	template<class T>
	inline const int & LinkStack<T>::GetCount() const { return m_nCount; }
}

