#include <cstdio>
#include <cassert>
#include "AutoReleasePool.h"

namespace lx {

//! AutoReleasePool

thread_local AutoReleasePool::PoolStack AutoReleasePool::_poolStack;

AutoReleasePool::AutoReleasePool ()
{
    _poolStack.emplace(this);
}

AutoReleasePool::~AutoReleasePool ()
{
    while (!_objs.empty())
    {
        delete *_objs.begin();
    }
    _poolStack.pop();
}

AutoReleasePool&
AutoReleasePool::instance (void)
{
    assert(!_poolStack.empty());
    return *_poolStack.top();
}

void
AutoReleasePool::insert (AutoReleaseObj* obj)
{
    if (_objs.find(obj) == _objs.end()) {
        _objs.insert(obj);
    }
}

void
AutoReleasePool::remove (AutoReleaseObj* obj)
{
    if (_objs.find(obj) != _objs.end()) {
        _objs.erase(obj);
    }
}

//! AutoReleaseObj
AutoReleaseObj::AutoReleaseObj ()
{
    AutoReleasePool::instance().insert(this);
}

AutoReleaseObj::~AutoReleaseObj ()
{
    AutoReleasePool::instance().remove(this);
}

}
