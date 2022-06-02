#ifndef REDEMPTION_IENUMERABLE_H
#define REDEMPTION_IENUMERABLE_H

template<typename T>
class IEnumerable {
public:
    virtual T GetCurrent() = 0;

    virtual bool Next() = 0;

    virtual void Next(int forward) = 0;

    virtual int Count() = 0;

    virtual void ForEach(void (*func)(T)) = 0;
};

template<typename T>
class IMutable {
public:
    virtual bool Insert(T node) = 0;

    virtual bool Delete(T value) = 0;

    virtual bool Replace(int position) = 0;
};

#endif //REDEMPTION_IENUMERABLE_H
