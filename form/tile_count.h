#ifndef SAKI_TILECOUNT_H
#define SAKI_TILECOUNT_H

#include "parsed.h"

#include <vector>
#include <initializer_list>
#include <numeric>



namespace saki
{



class TileCount
{
public:
    enum AkadoraCount { AKADORA0, AKADORA3, AKADORA4 };

    struct Explain4Closed
    {
        explicit Explain4Closed(T34 p) : pair(p) {}
        T34 pair;
        std::vector<T34> triplets;
        std::vector<T34> sequences;
    };

    TileCount();
    explicit TileCount(AkadoraCount fillMode);
    explicit TileCount(std::initializer_list<T37> t37s);

    TileCount(const TileCount &copy) = default;
    TileCount &operator=(const TileCount &assign) = default;

    int ct(T34 t) const;
    int ct(const T37 &t) const;
    int ctAka5() const;
    int ctZ() const;
    int ctYao() const;
    int ctS() const;

    template<typename V>
    int ct(const V &ts) const
    {
        auto aux = [this](int s, T34 t) { return s + ct(t); };
        return std::accumulate(ts.begin(), ts.end(), 0, aux);
    }

    bool hasZ() const;
    bool hasYao() const;

    void inc(const T37 &t, int delta);

    TileCount &operator-=(const TileCount &rhs);

    int step(int barkCt) const;
    int stepGb(int barkCt) const;
    int step4(int barkCt) const;
    int step7() const;
    int step7Gb() const;
    int step13() const;

    bool hasEffA(int barkCt, T34 t) const;
    bool hasEffA4(int barkCt, T34 t) const;
    bool hasEffA7(T34 t) const;
    bool hasEffA13(T34 t) const;

    util::Stactor<T34, 34> effA(int barkCt) const;
    util::Stactor<T34, 34> effA4(int barkCt) const;

    util::Stactor<T34, 13> t34s13() const;
    util::Stactor<T37, 13> t37s13(bool allowDup = false) const;

    bool dislike4(T34 t) const;

    std::vector<Parsed> parse4(int barkCt) const;

    std::vector<Explain4Closed> explain4(T34 pick) const;
    bool onlyInTriplet(T34 pick, int barkCt) const;

    int sum(const std::vector<T34> &ts) const;
    int sum() const;

    template<typename Ret, typename... Args>
    Ret peekDraw(T34 t, Ret (TileCount::*f) (Args...) const, Args... args) const
    {
        T34Delta guard(mutableCounts(), t, 1);
        (void) guard;
        return (this->*f)(args...);
    }

private:
    // using T34, assume const query functions are free from 34/37 matters
    class T34Delta
    {
    public:
        T34Delta(std::array<int, 34> &mCounts, T34 t, int delta);
        ~T34Delta();

        T34Delta(const T34Delta &copy) = delete;
        T34Delta &operator=(const T34Delta &assign) = delete;

    private:
        std::array<int, 34> &mCount;
        T34 mTile;
        int mDelta;
    };

    class NonEmptyGuard
    {
    public:
        explicit NonEmptyGuard(std::vector<Parsed> &p);
        ~NonEmptyGuard();

    private:
        std::vector<Parsed> &mParseds;
    };

    std::array<int, 34> &mutableCounts() const;
    int cutMeld(int i, int maxCut) const;
    std::vector<Parsed> cutMeldOut(int i, int maxCut) const;
    int cutSubmeld(int i, int maxCut) const;
    std::vector<Parsed> cutSubmeldOut(int i, int maxCut) const;
    bool decomposeBirdless4(Explain4Closed &exp, const std::array<int, 34> &mCounts) const;

private:
    std::array<int, 34> mCounts;
    std::array<int, 3> mAka5s;
};



} // namespace saki



#endif // SAKI_TILECOUNT_H
