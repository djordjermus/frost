#include "primitives.hpp"
#pragma once
namespace frost
{
	template<class T, u64 index = 0> class pimpl_type;

	template<class T, u64 index = 0>
	class pimpl
	{
	public:
		
		pimpl<T, index>() :
			_pimpl() {}
		pimpl<T, index>(pimpl_type<T, index>* pimpl) :
			_pimpl(pimpl) {}
		pimpl<T, index>(pimpl&& move) noexcept :
			_pimpl(move.detachPimpl()) {}
		pimpl<T, index>& operator=(pimpl&& move) noexcept
		{
			pimpl_type<T, index>* temp	= move._pimpl;
			_pimpl						= move._pimpl;
			move._pimpl					= temp;
			return *this;
		}

		operator bool() const
		{
			return _pimpl != nullptr;
		}
		bool operator !() const
		{
			return _pimpl == nullptr;
		}

		//
		// METHODS

		pimpl_type<T, index>* getPimpl() const
		{
			return _pimpl;
		}
		[[nodiscard]]
		pimpl_type<T, index>* detachPimpl()
		{
			pimpl_type<T, index>* temp	= _pimpl;
			_pimpl			= nullptr;
			return temp;
		}
		[[nodiscard]]
		pimpl_type<T, index>* swapPimpls(pimpl_type<T, index>* swap)
		{
			pimpl_type<T, index>* temp	= _pimpl;
			_pimpl			= swap;
			return temp;
		}
		void swapPimpls(pimpl<T, index>& swap)
		{
			pimpl_type<T, index>* temp	= swap._pimpl;
			_pimpl			= swap._pimpl;
			swap._pimpl		= temp;
		}


		//
		// DELETED FUNCTIONS

		pimpl<T, index>(pimpl& copy)							= delete;
		pimpl<T, index>(const pimpl&& copy) noexcept			= delete;
		pimpl<T, index>& operator=(pimpl& copy)					= delete;
		pimpl<T, index>& operator=(const pimpl&& copy) noexcept = delete;
	private:
		pimpl_type<T, index>* _pimpl;
	};
}