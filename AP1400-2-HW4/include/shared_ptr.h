#ifndef SHARED_PTR
#define SHARED_PTR

template<typename T>
class SharedPtr
{
public:
    SharedPtr(T* obj = nullptr) : _p(obj)
    {
        if (!count)
        {
            count = new size_t(1);
        }
    }

    ~SharedPtr()
    {
        if (count)
        {
            (*count)--;
            if (*count == 0 && _p)
            {
                delete count;
                delete _p;
            }
            count = nullptr;
            _p = nullptr;
        }
    }

    SharedPtr(const SharedPtr& obj) : _p(obj._p), count(obj.count)
    {
        (*count)++;
    }

    SharedPtr& operator=(const SharedPtr& obj)
    {
        if (&obj != this)
        {
            _p = obj._p;
            count = obj.count;
            (*count) ++;
        }
        return *this;
    }

    size_t use_count() const
    {
        return count ? *count : 0;
    }

    T* get() const
    {
        return _p;
    }

    T& operator*() const
    {
        if (_p)
        {
            return *_p;
        }
        else
        {
            throw std::runtime_error("Cannot dereference a nullptr.");
        }
    }

    T* operator->() const
    {
        return _p;
    }

    void reset()
    {
        if (count)
        {
            (*count) --;
            if (*count == 0 && _p)
            {
                delete count;
                delete _p;
            }
            count = nullptr;
            _p = nullptr;
        }
    }

    void reset(T* obj)
    {
        if (count)
        {
            (*count) --;
            if (*count == 0 && _p)
            {
                delete count;
                delete _p;
            }
            _p = obj;
            count = new size_t(1);
        }
    }

    explicit operator bool()
    {
        return _p != nullptr;
    }

private:
    T* _p = nullptr;
    size_t* count = nullptr;
};

template<typename T, class... Args>
auto make_shared(Args&&... args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SHARED_PTR