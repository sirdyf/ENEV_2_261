#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>

class tMenu{
	friend class tControl;
	char num,max,end,start;
	void Next(){
		if (++num>max) {
			num=max;
			if (end>max){
				start++;
				if (start>end-max) {
					start=end-max;
				}
			}
		}
	}
	void Prev(){
		if (--num<0) {
			num=0;
			if (end>max){
				start--;
				if (start<0) start=0;
			}
		}
	}
public:
	tMenu(){num=0;max=0;end=0;start=0;}
	tMenu(char maximum){
		end=max=maximum;
		
		if (max>15) max=15;
		num=0;
		start=0;
	}
    template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & BOOST_SERIALIZATION_NVP(num);
		ar & BOOST_SERIALIZATION_NVP(max);
		ar & BOOST_SERIALIZATION_NVP(end);
		ar & BOOST_SERIALIZATION_NVP(start);
	}
//	unsigned char GetNum(){
//		if (++num>max) num=0;
//		return num;
//	}
	inline char GetCurNum(){return num;}
	inline char GetMaximum(){return max;}
	inline char GetStartNum(){return start;}
	virtual ~tMenu(void){}
};
