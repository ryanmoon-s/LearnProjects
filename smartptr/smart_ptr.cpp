#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <map>
using namespace std;

template <class T>
class WeakPtr; //为了用weak_ptr的lock()，来生成share_ptr用，需要拷贝构造用

template <class T>
class SharePtr
{
public:
	SharePtr(T *p = 0) : _ptr(p)
	{
		if (p)
			cnt = new int(1);
		else
			cnt = new int(0);
		cout << "in construct " << *cnt << endl;
	}

	~SharePtr()
	{
		if (is_use) {
			release();
		}
	}

	SharePtr(SharePtr<T> const &s)
	{
		_ptr = s._ptr;
		(*s.cnt)++;
		cout << "copy s construct " << *s.cnt << endl;
		cnt = s.cnt;
	}

	SharePtr(WeakPtr<T> const &w) //为了用weak_ptr的lock()，来生成share_ptr用，需要拷贝构造用
	{
		_ptr = w._ptr;
		(*w.cnt)++;  //从weak变成share，引用计数++
		cout << "copy w  construct" << *w.cnt << endl;
		cnt = w.cnt;
	}

	SharePtr<T> &operator=(SharePtr<T> &s)
	{
		if (this != &s)   //防止自已传给自己
		{
			(*s.cnt)++;
			cout << "assign construct " << *s.cnt << endl;
			cnt = s.cnt;
			_ptr = s._ptr;
		}
		return *this;
	}

	T &operator*()
	{
		return *_ptr;
	}

	T *operator->()
	{
		return _ptr;
	}

	int use_count() {
		return *cnt;
	}

	void reset() {
		//减少计数
		release();
		//放弃使用权
		_ptr = nullptr;
		cnt = nullptr;
		is_use = false;
	}

	friend class WeakPtr<T>; //方便weak_ptr与share_ptr设置引用计数和赋值

protected:
	void release()
	{
		(*cnt)--;
		cout << "release " << *cnt << endl;

		if (*cnt < 1)
		{
			delete _ptr;
			delete cnt;
		}
	}

private:
	bool is_use = true;   //当reset放弃后，析构对象时不该减少计数，reset已经做了
	T* _ptr;
	int* cnt;
};

template <class T>
class WeakPtr
{
public: //给出默认构造和拷贝构造，其中拷贝构造不能有从原始指针进行构造
	WeakPtr()
	{
		_ptr = nullptr;
		cnt = nullptr;
	}

	WeakPtr(SharePtr<T> &s) : _ptr(s._ptr), cnt(s.cnt)
	{
		cout << "w con s" << endl;
	}

	WeakPtr(WeakPtr<T> &w) : _ptr(w._ptr), cnt(w.cnt)
	{
	}

	~WeakPtr()
	{
		release();
	}

	WeakPtr<T> &operator=(WeakPtr<T> &w)
	{
		if (this != &w)   //防止自己传给自己，只在重载=时，拷贝构造时，左边肯定是新的
		{
			cnt = w.cnt;
			_ptr = w._ptr;
		}
		return *this;
	}

	WeakPtr<T> &operator=(SharePtr<T> &s)
	{
		cout << "w = s" << endl;
		cnt = s.cnt;
		_ptr = s._ptr;
		return *this;
	}

	SharePtr<T> lock()
	{
		SharePtr<T> *s = new SharePtr<T>(_ptr);
		s->cnt = this->cnt;
		return *s;
	}

	bool expired()
	{
		if (cnt)
		{
			if (*cnt > 0)
			{
				cout << "empty" << *cnt << endl;
				return false;
			}
		}
		return true;
	}

	int use_count() {
		return *cnt;
	}

	friend class SharePtr<T>; //方便weak_ptr与share_ptr设置引用计数和赋值

protected:
	void release()
	{
		if (cnt)
		{
			cout << "weakptr release " << *cnt << endl;
		}
	}

private:
	T *_ptr;
	int *cnt;
};

class B;
class A {
public:
	SharePtr<B> pa;
};
class B {
public:
	WeakPtr<A> pb;
};

void test() {
	A *a = new A();
	B *b = new B();
	SharePtr<A> _pa(a);
	SharePtr<B> _pb(b);
	_pa->pa = _pb;
	_pb->pb = _pa;

	//两个share_ptr   release后，还剩下1个指向，内存未释放
	//一个换成weak_ptr     release后，还剩下0个指向，内存已释放
}

int main() {

	test();

	system("pause");
}

