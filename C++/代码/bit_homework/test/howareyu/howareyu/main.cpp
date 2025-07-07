#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

namespace bit
{
    class string
    {
        friend ostream& operator<<(ostream& _cout, const bit::string& s);
        friend istream& operator>>(istream& _cin, bit::string& s);
    public:
        typedef char* iterator;

    public:
        string(const char* str = "") //构造函数，默认值，既能接受const char* ，也能默认创建空字符串
        {
            if (str == nullptr)
            {
                str = " ";
            }

            _size = strlen(str);
            _capacity = _size + 1;
            _str = new char[_capacity];
            strcpy(_str, str);
        }
        
        string(const string& s)
        {
            _size = s._size;
            _capacity = s._capacity;
            _str = new char[_capacity];
            strcpy(_str, s._str);
        }
        string& operator=(const string& s)  //传递过来的s仍是用自定义的string声明的，仍用_size
        {
            if (this != &s)
            {
                delete[] _str; //就算_str为空，也不非法
                _size = s._size;
                _capacity = s._capacity;
                _str = new char[_capacity];
                strcpy(_str, s._str);
            }
            return *this;
        }
        ~string()
        {
            delete[] _str;
        }

        //////////////////////////////////////////////////////////////
        // iterator
        iterator begin()
        {
            return _str;  //返回字符串起始位置
        }
        iterator end()
        {
            return _str + _size;  //返回字符串起始位置和有效字数
        }

        /////////////////////////////////////////////////////////////
        // modify
        void push_back(char c)
        {
            if (_size + 1 >= _capacity)
            {
                _capacity *= 2;
                char* new_str = new char[_capacity];
                strcpy(new_str, _str);
                delete[] _str;
                _str = new_str;
            }
            _str[_size++] = c;
            _str[_size] = '\0';
        }
        string& operator+=(char c)
        {
            push_back(c);
            return *this;
        }
        void append(const char* str)
        {
            while (*str)  //当str解引用的值不为空时
            {
                push_back(*str++);
            }
        }
        string& operator+=(const char* str)
        {
            append(str);
            return *this;
        }
        void clear()  //只是清空字符串而不是释放它的内存
        {
            //delete[] _str;
            //_str = nullptr;
            _str[0] = '\0';
            _size = 0;  //不清_capacity
        }
        void swap(string& s)
        {
            char* temp_str;
            int temp_size,temp_capacity;

            temp_str = _str;
            _str = s._str;
            s._str = temp_str;

            temp_size = _size;
            _size = s._size;
            s._size = _size;

            temp_capacity = _capacity;
            _capacity = s._capacity;
            s._capacity = temp_capacity;
            
        }
        const char* c_str()const
        {
            return _str;
        }

        /////////////////////////////////////////////////////////////
        // capacity
        size_t size()const
        {
            return _size;
        }
        size_t capacity()const
        {
            return _capacity;
        }
        bool empty()const
        {
            return _size == 0;
        }
        void resize(size_t n, char c = '\0')
        {
            /*if (n < _size)
            {
                return;
            }*/
            if (n > _capacity)
            {
                _capacity = n;
                char* new_str = new char[_capacity];
                strcpy(new_str, _str);
                delete[] _str;
                _str = new_str;
            }
            for (size_t i = _size; i < n; ++i)
            {
                _str[i] = c;
            }
            _size = n-1;//这里就n为20，你直接_size=20
            _str[_size] = '\0';//然后这里_str[size]就越界了

        }
        void reserve(size_t n)
        {
            if (n > _capacity)
            {
                _capacity = n;
                char* new_str = new char[_capacity];
                strcpy(new_str, _str);
                delete[] _str;
                _str = new_str;
            }
        }

        /////////////////////////////////////////////////////////////
        // access
        char& operator[](size_t index)
        {
            return _str[index];
        }
        const char& operator[](size_t index)const
        {
            return _str[index];
        }

        /////////////////////////////////////////////////////////////
        //relational operators
        bool operator<(const string& s)
        {
            return strcmp(_str, s._str) < 0;
        }
        bool operator<=(const string& s)
        {
            return strcmp(_str, s._str) <= 0;
        }
        bool operator>(const string& s)
        {
            return strcmp(_str, s._str) > 0;
        }
        bool operator>=(const string& s)
        {
            return strcmp(_str, s._str) >= 0;
        }
        bool operator==(const string& s)
        {
            return strcmp(_str, s._str) == 0;
        }
        bool operator!=(const string& s)
        {
            return strcmp(_str, s._str) != 0;
        }

        // 返回c在string中第一次出现的位置
        size_t find(char c, size_t pos = 0) const
        {
            if (pos >= _size)
            {
                return std::string::npos;
            }

            for (size_t i = pos; i < _size; i++)  //从pos位置开始查找字符c，默认从0开始
            {
                if (_str[i] == c)
                    return i;
            }

            return std::string::npos;
        }
        // 返回子串s在string中第一次出现的位置
        size_t find(const char* s, size_t pos = 0) const
        {
            if (!s || pos >= _size)
                return std::string::npos;
            const char* res = strstr(_str + pos, s);
            return res ? res - _str : std::string::npos;  //res-_str返回偏移量
        }
        // 在pos位置上插入字符c/字符串str，并返回该字符的位置
        string& insert(size_t pos, char c)
        {
            if (pos > _size)
            {
                return *this;
            }

            if (_size + 1 >= _capacity)
            {
                reserve(_capacity * 2);
            }
            push_back('\0');

            for (int i = _size - 1; i >= pos; --i)
            {
                _str[i+1] = _str[i];
            }

            _str[pos] = c;

            return *this;
        }
        string& insert(size_t pos, const char* str)
        {
            while (*str)
            {
                insert(pos++, *str++);
            }
            return *this;
        }

        // 删除pos位置上的元素，并返回该元素的下一个位置
        string& erase(size_t pos, size_t len)
        {
            if (pos + len >= _size)
            {
                throw std::out_of_range("Insert position out of range");
            }

            for (size_t i = pos; i < pos + len; i++)
            {
                _str[i] = _str[i + len];
            }
            _size -= len;
            return *this;
        }

    private:
        char* _str;
        size_t _capacity;
        size_t _size;
    };

    ostream& operator<<(ostream& _cout, const bit::string& s)
    {
        return _cout << s._str;
    }

    istream& operator>>(istream& _cin, bit::string& s)
    {
        char temp[1000];
        _cin >> temp;
        s = bit::string(temp);  //用temp数组中的字符来初始化自己的_str数据成员
        return _cin;  //返回_cin是为了支持链式操作，即可以在同一行代码中对多个输入进行操作
    }
};


int main() {
    bit::string s1, s2;
    cin >> s1 >> s2;
    cout << s1 << endl << s2 << endl;
    bit::string s3(s1);
    s3 = s2;

    s1.push_back('a');
    cout << s1 << endl;
    s1 += ('b');
    cout << s1 << endl;
    s1.clear();
    cout << s1 << endl;
    s1.swap(s2);
    cout << s1 << endl;
    s1.size();
    s1.capacity();
    s1.empty();
    s1.resize(20, 'p');
    s1.insert(2, 'c');
    cout << s1 << endl;
    s1.insert(2, " limit ");
    cout << s1 << endl;
    s1.erase(2, 2);
    cout << s1 << endl;

    return 0;
}