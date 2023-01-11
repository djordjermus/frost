#include "primitives.hpp"
#pragma once
namespace frost
{
	template<class T, u64 index> class pimpl_type;
	template<class T, u64 index> using pimpl = pimpl_type<T, index>*;

	template<class T, u64 index = 0>
	class pimpl
	{
	public:
		using pimpl_t = pimpl<T, index>;
		
		pimpl<T, index>() :
			_pimpl() {}
		pimpl<T, index>(pimpl_t pimpl) :
			_pimpl(pimpl) {}
		pimpl<T, index>(pimpl&& move) noexcept :
			_pimpl(move.detachPimpl()) {}
		pimpl<T, index>& operator=(pimpl&& move) noexcept
		{
			pimpl_t temp	= swap._pimpl;
			_pimpl			= swap._pimpl;
			swap._pimpl		= temp;
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

		pimpl_t getPimpl() const
		{
			return _pimpl;
		}
		[[nodiscard]]
		pimpl_t detachPimpl()
		{
			pimpl_t temp	= _pimpl;
			_pimpl			= nullptr;
			return temp;
		}
		[[nodiscard]]
		pimpl_t swapPimpls(pimpl_t swap)
		{
			pimpl_t temp	= _pimpl;
			_pimpl			= swap;
			return temp;
		}
		void swapPimpls(pimpl<T, index>& swap)
		{
			pimpl_t temp	= swap._pimpl;
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
		pimpl_t _pimpl;
	};
}