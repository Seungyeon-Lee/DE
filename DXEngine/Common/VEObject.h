#pragma once
#include "VERefCounter.h"
#include <type_traits>

namespace Venus
{
	// RefCounter를 상속 받은 (갖고 있는) 타입
	template<class T>
	concept HasRefCounter = std::is_convertible_v<T*, VERefCounter*>;

	// RefCounter를 상속 받은 타입과 서로 캐스팅될 수 있는 타입
	template<class T, class U>
	concept Convertible = std::is_convertible_v<T*, U*>;

	template<HasRefCounter T>
	class VEObject final
	{
	public:
		VEObject(T* p = nullptr) : target(p)
		{
			InternalAddRef();
		}
		VEObject(const VEObject& obj) : target(obj.target)
		{
			InternalAddRef();
		}
		VEObject(VEObject&& obj) noexcept
			: target(obj.target)
		{
			obj.target = nullptr;
		}

		// convertible 형식도 동일하게 처리
		template<Convertible U>
		VEObject(U* p) : target(p)
		{
			InternalAddRef();
		}
		template<Convertible U>
		VEObject(const VEObject<U>& obj) : target(obj.target)
		{
			InternalAddRef();
		}
		template<Convertible U>
		VEObject(const VEObject<U>&& obj) noexcept
			: target(obj.target)
		{
			obj.target = nullptr;
		}

		~VEObject() noexcept
		{
			InternalRelease();
		}

		VEObject& operator = (T* obj)
		{
			if (target != obj)
				InternalRelease();

			target = obj;
			InternalAddRef();
			return *this;
		}
		VEObject& operator = (const VEObject& obj)
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			InternalAddRef();
			return *this;
		}
		VEObject& operator = (VEObject&& obj) noexcept
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			obj.target = nullptr;
			return *this;
		}

		template<Convertible U>
		VEObject& operator = (U* obj)
		{
			if (target != obj)
				InternalRelease();

			target = obj;
			InternalAddRef();
			return *this;
		}
		template<Convertible U>
		VEObject& operator = (const VEObject<U>& obj)
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			InternalAddRef();
			return *this;
		}

		template<Convertible U>
		VEObject& operator = (VEObject<U>&& obj) noexcept
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			obj.target = nullptr;
			return *this;
		}

		template<class U>
		VEObject<U> DynamicCast()
		{
			return dynamic_cast<U*>(target);
		}

		T* operator -> ()
		{
			return target;
		}
		const T* operator -> () const
		{
			return target;
		}

		T* operator * ()
		{
			return target;
		}
		const T* operator * () const
		{
			return target;
		}

		operator T* ()
		{
			return target;
		}
		operator const T* () const
		{
			return target;
		}

		T* Ptr()
		{
			return target;
		}
		const T* Ptr() const
		{
			return target;
		}

	private:
		void InternalAddRef()
		{
			if (target)
				target->AddRef();
		}

		void InternalRelease()
		{
			if (target && target->Release() == 0)
			{
				delete target;
				target = nullptr;
			}
		}

		T* target;
	};
}