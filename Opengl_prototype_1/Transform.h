#pragma once
template <class T>
class Transform {
	public:
		T obj;
		float x;
		float y;
		float z;
	private:
		void moveObject(); //might need to return the object, have to think about this when I'm not tired
};