#ifndef __pair__
#define __pair__

#include <iostream>

namespace LAZ {
    template<typename First, typename Second>
    struct Pair {
    public:
        Pair();
        Pair(First&& first, Second&& second);
        template<typename... T, typename... U>
        Pair(std::piecewise_construct_t, std::tuple<T...>, std::tuple<U...>);
        Pair(const Pair<First, Second>& oth);   // copy ctor
        Pair(Pair<First, Second>&& oth);        // move ctor
        template<typename T, typename U>
        Pair(const Pair<T, U>& oth);            // copy ctor for other pair
        template<typename T, typename U>
        Pair(Pair<T, U>&& oth);                 // move ctor for other pair
    public:
        Pair<First, Second>& operator=(const Pair<First, Second>& rhs);
        Pair<First, Second>& operator=(Pair<First, Second>&& rhs);
        template<typename T, typename U>
        Pair<First, Second>& operator=(const Pair<T, U>& rhs);
        template<typename T, typename U>
        Pair<First, Second>& operator=(Pair<T, U>&& rhs);
        bool operator==(const Pair<First, Second>& rhs);
        bool operator!=(const Pair<First, Second>& rhs);
        bool operator<(const Pair<First, Second>& rhs);
        bool operator<=(const Pair<First, Second>& rhs);
        bool operator>(const Pair<First, Second>& rhs);
        bool operator>=(const Pair<First, Second>& rhs);
    public:
        First _first;
        Second _second;
    };

    // CTORS
    template<typename First, typename Second>
    Pair<First, Second>::Pair() : _first{}, _second{} {}

    template<typename First, typename Second>
    Pair<First, Second>::Pair(First&& first, Second&& second) : _first{std::forward<First>(first)},
                                                                _second{std::forward<Second>(second)}
    {}

    template<typename First, typename Second>
    template<typename... T, typename... U>
    Pair<First, Second>::Pair(std::piecewise_construct_t,
                              std::tuple<T...> first,
                              std::tuple<U...> second) : _first{first}, 
                                                         _second{second}
    {}

    template<typename First, typename Second>
    Pair<First,Second>::Pair(const Pair<First, Second>& oth) :_first{oth._first},
                                                              _second{oth._second}
    {}

    template<typename First, typename Second>
    Pair<First, Second>::Pair(Pair<First, Second>&& oth) : _first{oth._first},
                                                           _second{oth._second}
    {}

    template<typename First, typename Second>
    template<typename T, typename U>
    Pair<First, Second>::Pair(const Pair<T, U>& oth) : _first{oth._first},
                                                       _second{oth._second}
    {}

    template<typename First, typename Second>
    template<typename T, typename U>
    Pair<First, Second>::Pair(Pair<T, U>&& oth) : _first{oth._first},
                                                  _second{oth._second}
    {}

    // OPERATORS
    template<typename First, typename Second>
    Pair<First, Second>& Pair<First, Second>::operator=(const Pair<First, Second>& rhs) {
        if(this == &rhs) {
            return *this;
        }
        _first = rhs._first;
        _second = rhs._second;
        return *this;
    }

    template<typename First, typename Second>
    Pair<First, Second>& Pair<First, Second>::operator=(Pair<First, Second>&& rhs) {
        _first = rhs._first;
        _second = rhs._second;
        return *this;
    }

    template<typename First, typename Second>
    template<typename T, typename U>
    Pair<First, Second>& Pair<First, Second>::operator=(const Pair<T, U>& rhs) {
        _first = rhs._first;
        _second = rhs._second;
        return *this;
    }

    template<typename First, typename Second>
    template<typename T, typename U>
    Pair<First, Second>& Pair<First, Second>::operator=(Pair<T, U>&& rhs) {
        _first = rhs._first;
        _second = rhs._second;
        return *this;
    }

    template<typename First, typename Second>
    bool Pair<First, Second>::operator==(const Pair<First, Second>& rhs) {
        return (_first == rhs._first && _second == rhs._second);
    }

    template<typename First, typename Second>
    bool Pair<First, Second>::operator!=(const Pair<First, Second>& rhs) {
        return (_first != rhs._first && _second != rhs._second);
    }

    template<typename First, typename Second>
    bool Pair<First, Second>::operator<(const Pair<First, Second>& rhs) {
        return (_first < rhs._first || (!(rhs._first < _first) && _second < rhs._second));
    }
    
    template<typename First, typename Second>
    bool Pair<First, Second>::operator<=(const Pair<First, Second>& rhs) {
        return (_first <= rhs._first || _second <= rhs._second);
    }
    
    template<typename First, typename Second>
    bool Pair<First, Second>::operator>(const Pair<First, Second>& rhs) {
        return (_first > rhs._first || (!(rhs._first > _first) && _second > rhs._second));
    }

    template<typename First, typename Second>
    bool Pair<First, Second>::operator>=(const Pair<First, Second>& rhs) {
        return (_first >= rhs._first || _second >= rhs._second);
    }

    // CONVENIENCE FUNCTIONS
    template<typename First, typename Second>
    Pair<First, Second> makePair(const First& x, const Second& y) {
        return Pair(x, y);
    }

    template<typename First, typename Second>
    std::ostream& operator<<(std::ostream& out, const Pair<First, Second>& x) {
        out << "[ " << x._first << "  " << x._second << " ]" << std::endl;
        return out;
    }
};

int main() {
    LAZ::Pair<int, std::string> x;
    LAZ::Pair<int, std::string> y(1, "asd");
    auto a = LAZ::makePair(123, 'a');
    x = std::move(y);
    std::cout << a;
}
#endif
