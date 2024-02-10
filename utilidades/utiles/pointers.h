#pragma once
#include <cstring>
struct cmp_str{
	bool operator()(char const* a, char const* b) const{
		return std::strcmp(a, b) < 0;
	}
};

class Pointer{
public:
	template<typename T>
	static T* deleteMulti(T* p);
};
template<typename T>
inline T* Pointer::deleteMulti(T* p) {
	if (p) {
		delete[]p;
	}
	return 0;
};
#define DELETE_MULTI(p) \
	if(p){\
		delete []p;\
	};\
	p=NULL;
#define DELETE_SIMPLE(p) \
	if(p){\
		delete p;\
	};\
	p=NULL;
#define DELETE_VECTOR_MULTI(p, l)\
	if (p) {\
		for (int i = 0; i < l;i++) {\
			delete[]p[i];\
		}\
		delete p;\
	};\
	p = NULL;


#define COPY_CHAR(source, target) \
	DELETE_MULTI(target);\
	int l=strlen(source);\
	target=new char[l+1];\
	for(int i=0;i<l;i++){\
		target[i]=source[i];\
	};\
	target[l]='\0';

#define CONCAT_CHAR(source1, source2, target)\
	DELETE_MULTI(target);{\
	int l1=strlen(source1);\
	int l2=strlen(source2);\
	target=new char[l1+l2+1];\
	int j=0;\
	for(int i=0;i<l1;i++){\
		target[j++]=source1[i];\
	};\
	for(int i=0;i<l2;i++){\
		target[j++]=source2[i];\
	};\
	target[l1+l2]='\0';};