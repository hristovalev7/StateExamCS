#include <vector>
#include <iostream>

template<typename T>
class Function
{ public:
    virtual T value(T) const = 0;
};

class Inc : public Function<double>
{ public:
    double value(double x) const { return x+1; }
};

class Square : public Function<double>
{ public:
    double value(double x) const { return x*x; }
};

template<typename T>
class Max : public Function<T>
{ private:
    std::vector<Function<T>*> functions;
public:
    void addFunction(Function<T> *f) { functions.push_back(f); }
    T value(T x) const
    {
        if(functions.size()<1)
            throw "Function list is empty!";
        T result = functions[0]->value(x);
        for(Function<T> *f : functions)
            result = std::max(result,f->value(x));
        return result;
    }
};

template<typename T>
class Sum : public Function<T>
{ private:
    std::vector<Function<T>*> functions;
public:
    void addFunction(Function<T> *f) { functions.push_back(f); }
    T value(T x) const
    {
        T result = 0;
        for(Function<T> *f : functions)
            result += f->value(x);
        return result;
    }
};

int main()
{
    Inc i; Square sq;
    Sum<double> s; Max<double> m;
    
    // s представя (x+1)+(x*x)
    s.addFunction(&i); s.addFunction(&sq);
    
    // m представя max{x+1, x*x, (x+1)+(x*x)}
    m.addFunction(&i); m.addFunction(&sq);
    m.addFunction(&s);
    
    double x; std::cin >> x;
    std::cout << m.value(x) << std::endl;
}
