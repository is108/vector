#include <iostream>

using namespace std;

template <typename T>
class Vector 
{
    protected:
    int m_size;
    int total_size;
    T* v;
    const int RESIZE_CONST = 2;

    public:
    Vector(int s) // Конструктор с 1 аргументом
    {
        total_size = s;
        m_size = 0;
        v = new T[s];
        
    }

    Vector() : m_size(0), total_size(0), v(NULL)
    {
    }

    ~Vector() // Деструктор
    {
       delete[] v;
    }

    Vector(const Vector& other) // Конструктор присваивания
    {
        total_size = other.total_size;
        v = new T[total_size];

        for (int i = 0; i < this->total_size; i++)
        {
            v[i] = other.v[i];
        }

    }

    Vector& operator=(const Vector& other)
    {
        total_size = other.total_size;
        if (this->v != NULL)
        {
            delete[] v;
        }

        v = new T[total_size];
        for (int i = 0; i < total_size; i++)
        {
            this->v[i] = other.v[i];
        }
        return *this;
    }
    
    friend Vector operator+(const Vector& left, const Vector& right )
    {
        Vector temp(left.total_size);

        for (int i = 0; i < temp.total_size; i++)
        {
            temp.v[i] = left.v[i] + right.v[i];
        }
        return temp;
    }

    friend Vector operator-(const Vector& left, const Vector& right)
    {
        Vector temp(left.total_size);

        for (int i = 0; i < temp.total_size; i++)
        {
            temp.v[i] = left.v[i] - right.v[i];
        }
        return temp;
    }
   
    void operator+=(const Vector& other)
    {
        for (int i = 0; i < this->total_size; i++)
            this->v[i] += other.v[i];
    }

    void operator-=(const Vector& other)
    {
        for (int i = 0; i < this->total_size; i++)
            this->v[i] -= other.v[i];
    }
    
    T& operator[](int index) const
    {
        return v[index];
    }

    void add(const T& elem);
    void push_back(T n);
    void pop_back();
    void print();
    void resize(int);
    int capacity();
    void erase(int);
    void reserve(int n);
    void clear();
    int size(){return m_size;}
    T& begin(){return *v;}
    T& end(){return *(v + m_size - 1);}
};

template<typename T>
void Vector<T>::push_back(T n)
{
    add(n);
}

template<typename T>
void Vector<T>::reserve(int n)
{
    if (n <= total_size)
        {
        total_size = n;
        if (m_size > total_size)
        {
            m_size = n;
        }
    }
    else resize(n);
}

template<typename T>
void Vector<T>::clear()
{
    delete[] v;
    m_size = 0;
    total_size = 0;
    v = new T[total_size]; 
}

template<typename T>
//Добавление элемента в конец вектора
void Vector<T>::add(const T& elem)
{
    if (m_size < total_size)
    {    
        new (v + m_size) T(elem); // placement new
        m_size++;
    }
    else
    {
        if (total_size == 0)
        {
            resize(1);
            add(elem);
        }
        else
        {
        resize(total_size*RESIZE_CONST);
        add(elem);
        }
    }
}

template<typename T>
//Удаление последнего элемента в векторе
void Vector<T>::pop_back()
{
    v[m_size -1] = 0;
    m_size--;
}

template<typename T>
//Вывод всех элементов в векторе
void Vector<T>::print()
{
    for (int i = 0; i < m_size; i++)
    {
        cout << *(v + i) << ' ';
    }
    cout << endl << "Размер вектора: " << m_size << endl;
}

template<typename T>
//Выделение дополнительной памяти в вектор
void Vector<T>::resize(int counter_elem)
{
    T *p;
    if (counter_elem != 1)
    {
        p = new T[counter_elem];
        total_size = counter_elem;
        for (int i = 0; i < m_size; i++)
        {
            p[i] = v[i];
        }
    
        delete[] v;
        v = p;
    }
    else 
    {
        v = new T[counter_elem];
        total_size = counter_elem;
    }
    
}

template<typename T>
int Vector<T>::capacity()
{
    return (total_size - m_size);
}

template<typename T>
//Удаляет выбранный элемент из вектора
void Vector<T>::erase(int n)
{
    if (n < m_size)
    {
        m_size--;
        (v + n)->~T();
        for (int i = n; i < m_size; ++i)
        {
            *(v + i) = *(v + i + 1);
        }
    }
}
