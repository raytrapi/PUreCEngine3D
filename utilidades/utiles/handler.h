#pragma once
#include <vector>
struct Handler {
	template <typename T>
	static int setHandle(std::vector<T>* vector, T object);
   template <typename T>
   static void removeHandle(std::vector<T>* vector, int i);
};

template<typename T>
inline int Handler::setHandle(std::vector<T>* data, T object){
   for (int i = 0; i < data->size(); i++) {
      if(data->operator[](i)==nullptr){
         data->operator[](i) = object;
         return i;
      }
   }
   data->push_back(object);
   return data->size() - 1;
}

template<typename T>
inline void Handler::removeHandle(std::vector<T>* vector, int i){
   if (vector->size() > i) {
      vector->operator[](i) = nullptr;
   }
}
