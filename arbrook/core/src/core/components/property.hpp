#pragma once
#include <functional>

namespace rythe::core
{
	template<typename Self, typename T>
	class Property
	{
	public:
		Property(T* data_ptr) :
			m_data(*data_ptr),
			m_setCallback(),
			m_getCallback(),
			m_callbacks(false) {}
		Property(T* data_ptr, void(setfunc_ptr)(T), T(getfunc_ptr)(void)) : 
			m_data(*data_ptr),
			m_setCallback(&setfunc_ptr),
			m_getCallback(&getfunc_ptr),
			m_callbacks(true) {}
		Property(Self* obj_ptr, T* data_ptr, void(Self::* setfunc_ptr)(T), T(Self::* getfunc_ptr)(void)) :
			m_data(*data_ptr),
			m_setCallback(std::bind(setfunc_ptr, obj_ptr, std::placeholders::_1)),
			m_getCallback(std::bind(getfunc_ptr, obj_ptr)), 
			m_callbacks(true) {}

		T operator+(const T& rhs)
		{
			return m_data + rhs;
		}

		T operator-(const T& rhs)
		{
			return m_data - rhs;
		}

		T operator*(const T& rhs)
		{
			return m_data * rhs;
		}

		T operator/(const T& rhs)
		{
			return m_data / rhs;
		}

		Property& operator=(const T& newvalue)
		{
			m_data = newvalue;
			if (m_callbacks)
				m_setCallback(m_data);
			return *this;
		}
		Property& operator+=(const T& newvalue)
		{
			m_data += newvalue;
			if (m_callbacks)
				m_setCallback(m_data);

			return *this;
		}
		Property& operator-=(const T& newvalue)
		{
			m_data -= newvalue;
			if (m_callbacks)
				m_setCallback(m_data);

			return *this;
		}
		Property& operator*=(const T& newvalue)
		{
			m_data *= newvalue;
			if (m_callbacks)
				m_setCallback(m_data);

			return *this;
		}
		Property& operator/=(const T& newvalue)
		{
			m_data /= newvalue;
			if (m_callbacks)
				m_setCallback(m_data);

			return *this;
		}
		bool operator==(const T& newvalue)
		{
			return m_data == newvalue;
		}
		bool operator!=(const T& newvalue)
		{
			return m_data != newvalue;
		}

		operator T() const
		{
			if (m_callbacks)
				return m_getCallback();
			return m_data;
		}

		operator T()
		{
			if (m_callbacks)
				return m_getCallback();
			return m_data;
		}

	private:
		T& m_data;
		std::function<void(T)> m_setCallback;
		std::function<T(void)> m_getCallback;

		bool m_callbacks;
	};

	template<typename T>
	void setProperty(T& data, T input)
	{
		data = input;
	}

}