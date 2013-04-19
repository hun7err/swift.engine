#ifndef HANDLEMANAGER_H
#define HANDLEMANAGER_H
/*
#include <vector>
#include "Handle.h"

template <typename ObjType, typename HandleType> class HandleManager {
	private:
		std::vector<ObjType> objects;
		std::vector<unsigned int> freepos;
		std::vector<unsigned int> valids;
	public:
		Handle<ObjType Insert(ObjType object) {
			if(freepos.empty()) return Handle<HandleType>(0,0);
			unsigned int pos = objects.back();
			freepos.pop_back();
			return Handle<HandleType>(pos, 1);
		}
		void Release(Handle<HandleType> handle) {
			objects[handle.getIndex()] = 0;
			freepos.push_back(handle.getIndex());
		}
		HandleManager();
	~HandleManager();
};*/

#endif // HANDLEMANAGER_H