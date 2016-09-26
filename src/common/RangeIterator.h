#ifndef RANGEITERATOR_H
#define RANGEITERATOR_H

#include <iterator>
#include <QVector>
#include <QSize>

template <class IteratorType>
class RangeIterator
{
public:
    typedef IteratorType iterator_type;

    typedef RangeIterator<iterator_type> self_type;
    typedef QVector<typename iterator_type::reference> value_type;
    typedef QVector<typename iterator_type::reference>& reference;
    typedef QVector<typename iterator_type::reference>* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    RangeIterator(iterator_type &iterator, QSize size): iterator(iterator), _size(size) {}

    RangeIterator<iterator_type> &operator ++ ()
    {
        iterator++;
        return *this;
    }
    RangeIterator<iterator_type> &operator -- ()
    {
        iterator--;
        return *this;
    }

    value_type operator * () const
    {
        value_type result(_resultSize * _resultSize);
        for (auto i = -halfResultSize(); i <= halfResultSize(); i++)
        {
            for(auto j = -halfResultSize(); j < halfResultSize(); j++)
            {
                result.push_back(*(iterator + size().height() * i + j));
            }
        }
        return result;
    }

    RangeIterator<iterator_type> &operator += (std::ptrdiff_t position)
    {
        iterator += position;
        return *this;
    }
    RangeIterator<iterator_type> &operator -= (std::ptrdiff_t position)
    {
        iterator -= position;
        return *this;
    }

    RangeIterator<iterator_type> operator + (std::ptrdiff_t position) const
    {
        RangeIterator<IteratorType> result(*this);
        result += position;
        return result;
    }
    RangeIterator<iterator_type> operator - (std::ptrdiff_t position) const
    {
        RangeIterator<IteratorType> result(*this);
        result -= position;
        return result;
    }

    std::ptrdiff_t operator - (const RangeIterator<iterator_type> &other) const
    {
        return iterator - other.iterator;
    }


    bool operator == (const RangeIterator<iterator_type> &other) const
    {
        return iterator == other.iterator;
    }
    bool operator != (const RangeIterator<iterator_type> &other) const
    {
        return iterator != other.iterator;
    }


    QSize size() const
    {
        return _size;
    }

    void setSize(const QSize &size)
    {
        _size = size;
    }

    int resutlSize() const
    {
        return _resutlSize;
    }

    void setResutlSize(int resutlSize)
    {
        _resutlSize = resutlSize;
    }

private:
    inline int halfResultSize() const
    {
        return _resutlSize / 2;
    }

    iterator_type &iterator;
    QSize _size;
    int _resutlSize;
};

#endif // RANGEITERATOR_H
