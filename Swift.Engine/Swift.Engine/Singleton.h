#ifndef SINGLETON_H
#define SINGLETON_H

#include <cassert>
#include <cstdio>

template <class T> class Singleton {
	public:
		static T* getSingleton() {
			if(!SingletonInstance) SingletonInstance = new T;
			assert(SingletonInstance != NULL);
			return SingletonInstance;
		}
	protected:
		Singleton() {}
		~Singleton() {}
	private:
		Singleton(Singleton const&) {}
		Singleton& operator= (Singleton const&);
		static T* SingletonInstance;
};

template <class T> T* Singleton<T>::SingletonInstance = NULL;

#endif // SINGLETON_H