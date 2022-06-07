#include "VERefCounter.h"

using namespace Venus;

VERefCounter::VERefCounter()
	: refCount(0)
{
}

VERefCounter::~VERefCounter() noexcept
{
	// TODO ASSERT Á¤ÀÇ.
	assert(refCount == 0);
}

uint32_t VERefCounter::AddRef()
{
	return ++refCount;
}

uint32_t VERefCounter::Release()
{
	return --refCount;
}

uint32_t VERefCounter::RefCount() const
{
	return refCount;
}
