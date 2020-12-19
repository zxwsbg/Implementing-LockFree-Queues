#ifndef DCAS_H
#define DCAS_H
#include <iostream>

template <typename T, unsigned N = sizeof(uint32_t)> struct DPointer
{
public:
    union
    {
        uint64_t ui;
        struct
        {
            T*     ptr;
            size_t count;
        };
    };

    DPointer() : ptr(NULL), count(0) {}
    DPointer(T* p) : ptr(p), count(0) {}
    DPointer(T* p, size_t c) : ptr(p), count(c) {}

    bool double_cas(DPointer<T, N> const& new_val, DPointer<T, N> const& ori_val)
    {
        bool result;
        __asm__ __volatile__("lock cmpxchg8b %1\n\t"
                             "setz %0\n"
        : "=q"(result), "+m"(ui)
        : "a"(ori_val.ptr), "d"(ori_val.count), "b"(new_val.ptr),
        "c"(new_val.count)
        : "cc");
        return result;
    }

    bool operator==(DPointer<T, N> const& x)
    {
        return x.ui == ui;
    }
};

template <typename T> struct DPointer<T, sizeof(uint64_t)>
{
public:
    union
    {
        uint64_t ui[2];
        struct
        {
            T*     ptr;
            size_t count;
        } __attribute__((__aligned__(16)));
    };

    DPointer() : ptr(NULL), count(0) {}
    DPointer(T* p) : ptr(p), count(0) {}
    DPointer(T* p, size_t c) : ptr(p), count(c) {}

    bool double_cas(DPointer<T, 8> const& new_val, DPointer<T, 8> const& ori_val)
    {
        bool result;
        __asm__ __volatile__("lock cmpxchg16b %1\n\t"
                             "setz %0\n"
        : "=q"(result), "+m"(ui)
        : "a"(ori_val.ptr), "d"(ori_val.count), "b"(new_val.ptr),
        "c"(new_val.count)
        : "cc");
        return result;
    }

    bool operator==(DPointer<T, 8> const& x)
    {
        return x.ptr == ptr && x.count == count;
    }
};


#endif