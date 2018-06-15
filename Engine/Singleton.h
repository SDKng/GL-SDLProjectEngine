#pragma once

#ifndef _SINGLETON_H
#define _SINGLETON_H

namespace engine {

	template <class T>
	
	class Singleton {

	private:

		static T* m_instance;

	protected:
		// constructor is pr(rotected)ivate!
		Singleton() {}

	public:

		static T& GetInstance();
	};

	template <class T>
	T* Singleton<T>::m_instance = nullptr;

	template <class T>
	 T& Singleton<T>::GetInstance() {

		if (m_instance) return *m_instance;

		else {
			m_instance = new T();
			return *m_instance;
		}
	}
}
#endif