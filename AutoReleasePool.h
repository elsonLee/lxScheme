#ifndef AUTO_RELEASE_POOL_H
#define AUTO_RELEASE_POOL_H

#include <cassert>
#include <set>
#include <stack>

namespace lx {

struct AutoReleaseObj
{
    AutoReleaseObj ();
    virtual ~AutoReleaseObj ();
};

class AutoReleasePool final
{
    public:

        AutoReleasePool ();
        ~AutoReleasePool ();

        static AutoReleasePool& instance (void);

        void insert (AutoReleaseObj* obj);
        void remove (AutoReleaseObj* obj);

        AutoReleasePool (const AutoReleasePool&) = delete;
        AutoReleasePool& operator= (const AutoReleasePool&) = delete;

    private:

        void* operator new (std::size_t size)
        {
            return ::operator new(size);
        }

    private:

        struct CreatePoolPrivate {};
        AutoReleasePool (CreatePoolPrivate&&) {}

        struct PoolStack final : std::stack<AutoReleasePool*>
        {
            PoolStack ()
            {
                push(new AutoReleasePool(CreatePoolPrivate()));
            }
            ~PoolStack ()
            {
                delete top();
                pop();
            }
        };

        std::set<AutoReleaseObj*>   _objs;

        static PoolStack& get_poolStack (void)
        {
            static thread_local PoolStack _poolStack;
            return _poolStack;
        }
};

}

#endif  // AUTO_RELEASE_POOL_H
