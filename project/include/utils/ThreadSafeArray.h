#ifndef LIME_UTILS_THREAD_SAFE_ARRAY_H
#define LIME_UTILS_THREAD_SAFE_ARRAY_H

namespace lime {
	
	static std::array<ByteArrayFunc*, 16> gByteArrayFuncs;
	static unsigned int gNextThreadIndex = 0;
	static std::mutex gMtx;
	template <class T>
	class ThreadSafeArray {

	public:

		ThreadSafeArray (int inSize) {

		}

		T Get() {


		}

	private:

		std::vector<T> elements;

	};
	
}


#endif
