// tOwn.h: interface for the tOwn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPOINTER_H__93E44A81_17F5_11DB_8340_00025511B36C__INCLUDED_)
#define AFX_TPOINTER_H__93E44A81_17F5_11DB_8340_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tPointer
{
public:
	
	friend void intrusive_ptr_add_ref(tPointer*);
	friend void intrusive_ptr_release(tPointer*);
	size_t m_refCounter;
	void AddRef() {
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
		}
	}
protected:
  tPointer(): m_refCounter(0) {}
  virtual ~tPointer() {}

};
inline void intrusive_ptr_add_ref(tPointer* e) { e->AddRef(); }
inline void intrusive_ptr_release(tPointer* e) { e->Release(); }

#endif // !defined(AFX_TPOINTER_H__93E44A81_17F5_11DB_8340_00025511B36C__INCLUDED_)
