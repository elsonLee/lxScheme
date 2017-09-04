#include <cstdio>
#include <cassert>
#include "AutoReleasePool.h"

namespace lx {

//! AutoReleasePool

AutoReleasePool::AutoReleasePool ()
{
   get_poolStack().emplace(this);
}

AutoReleasePool::~AutoReleasePool ()
{
    while (!_objs.empty())
    {
        delete *_objs.begin();
    }
    get_poolStack().pop();
}

AutoReleasePool&
AutoReleasePool::instance (void)
{
    assert(!get_poolStack().empty());
    return *get_poolStack().top();
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
