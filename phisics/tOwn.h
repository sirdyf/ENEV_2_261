// tOwn.h: interface for the tOwn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOWN_H__93E44A81_17F5_11DB_8340_00025511B36C__INCLUDED_)
#define AFX_TOWN_H__93E44A81_17F5_11DB_8340_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tOwn  
{
public:
	char name[10];

	friend void intrusive_ptr_add_ref(tOwn*);
	friend void intrusive_ptr_release(tOwn*);
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
  tOwn(): m_refCounter(0) {
	  name[0]=0;
  }
  virtual ~tOwn() {}

};
inline void intrusive_ptr_add_ref(tOwn* e) { e->AddRef(); }
inline void intrusive_ptr_release(tOwn* e) { e->Release(); }

#endif // !defined(AFX_TOWN_H__93E44A81_17F5_11DB_8340_00025511B36C__INCLUDED_)
