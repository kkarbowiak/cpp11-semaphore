#include <condition_variable>
#include <mutex>


namespace thr
{
    template<typename C>
    class semaphore
    {
        public:
            semaphore();
            explicit semaphore(C count);

            void acquire();
            void release();

        private:
            std::mutex mMutex;
            std::condition_variable mCondVar;
            C mCount;
    };
}

namespace thr
{
////////////////////////////////////////////////////////////////////////////////
template<typename C>
inline semaphore<C>::semaphore()
    : mMutex()
    , mCondVar()
    , mCount(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename C>
inline semaphore<C>::semaphore(C count)
    : mMutex()
    , mCondVar()
    , mCount(count)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename C>
inline void semaphore<C>::acquire()
{
    std::unique_lock<std::mutex> lock(mMutex);

    while (mCount == 0)
    {
        mCondVar.wait(lock);
    }

    --mCount;
}
////////////////////////////////////////////////////////////////////////////////
template<typename C>
inline void semaphore<C>::release()
{
    std::unique_lock<std::mutex> lock(mMutex);

    ++mCount;

    mCondVar.notify_one();
}
////////////////////////////////////////////////////////////////////////////////
}

