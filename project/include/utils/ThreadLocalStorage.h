#ifndef LIME_UTILS_THREAD_LOCAL_STORAGE_H
#define LIME_UTILS_THREAD_LOCAL_STORAGE_H

#include <thread>
#include <mutex>
#include <array>

namespace lime {
	
	template <class T>
	class ThreadLocalStorage {

	public:

		ThreadLocalStorage () {

			nextIndex = 0;

		}

		T Get () {

			std::thread::id thisThreadId = std::this_thread::get_id ();
			for (size_t i = 0; i < elements.size (); ++i) {

				if (id[i] == thisThreadId)
					return elements[i];

			}

			return T();

		}

		void Set (T element) {

			std::thread::id thisThreadId = std::this_thread::get_id ();
			std::lock_guard<std::mutex> lock(mtx);
			elements[nextIndex] = element;
			id[nextIndex] = thisThreadId;
			++nextIndex;

		}

	private:

		std::array<T, 16> elements;
		std::array<std::thread::id, 16> id;
		std::mutex mtx;
		int nextIndex;

	};
	
}


#endif
