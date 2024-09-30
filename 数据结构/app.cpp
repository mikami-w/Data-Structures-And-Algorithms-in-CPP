#include "app.h"
namespace mkm = Mikami;
using std::cin, std::cout, std::endl;

auto defaultcinbuf = cin.rdbuf();

void RedirectInputBuffer(std::string& str)
{
	std::istringstream iss(str);
	cin.rdbuf(iss.rdbuf());
}

void TestVector()
{
	mkm::Vector<int,4> vec;

	//����pop, push�����ʲ���
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	cout << vec.front() << ' ' << vec.at(1) << ' ' << vec[2] << ' ' << vec.back() << endl;

	//�������ݲ���
	cout << vec.full() << endl;
	cout << "capacity:" << vec.capacity() << endl;
	vec.push_back(4);
	cout << vec.full() << endl;
	cout << "capacity:" << vec.capacity() << endl;

	//���Խ�������
	mkm::Vector<int, 4> nvec;
	cout << vec.data()[0] << ' ' << vec.data()[1] << ' ' << vec.data()[2] << ' ' << vec.data()[3] << ' ' << vec.data()[4] << endl;

	vec.swap(nvec);

	//cout << vec.front() << ' ' << vec.at(1) << ' ' << vec[2] << ' ' << vec.back() << endl;
	cout << nvec.front() << ' ' << nvec.at(1) << ' ' << nvec[2] << ' ' << nvec.back() << endl;
	cout << nvec.data()[0] << ' ' << nvec.data()[1] << ' ' << nvec.data()[2] << ' ' << nvec.data()[3] << ' ' << nvec.data()[4] << endl;

	cout << endl << endl;

	//���Գ�ʼ���б��켰������
	mkm::Vector<int> iv{ 0,11,22,33 };
	cout << iv.front() << ' ' << iv.at(1) << ' ' << iv[2] << ' ' << iv.back() << endl;

	cout << *iv.begin() << ' ' << *(iv.end() - 1) << endl << endl;

	mkm::Vector<int>::iterator it = iv.begin();
	cout << *it++ << *it << endl << endl;

	for (auto i = iv.begin(); i < iv.end(); ++i)
		cout << *i << ' ';
	cout << endl << endl;

	for (auto x : iv)
		cout << x << ' ';
	cout << endl << endl;

	it = iv.begin();
	it = it + 2;
	cout << *it;

	//���Գ�ֵ��ʼ��
	mkm::Vector<int, 4>* vp[]{
		new mkm::Vector<int,4>(4,7),
		new mkm::Vector<int,4>(8,7),
		new mkm::Vector<int,4>{0,1,2,3,4,5,6}
	};
	for (auto x : vp)
		cout << "capacity: " << x->capacity() << " size: " << x->size() << " full: " << x->full() << endl;
	for (auto x : *vp[1])
		cout << x << ' ';

	
}

void TestFixedLengthStackAndQueue()
{
	using Q = mkm::FLQueue<int, 16>;
	using S = mkm::FLStack<int, 15>;

	S s; Q q;
	cout << s.empty() << ' ' << q.empty() << endl;
	std::initializer_list<int> li{ 0,1,2,3,4,5,6,7,8,9,10,11 };
	for (auto x : li) {
		s.push(x);
		q.in_queue(x);
		cout << s.top() << '\t' << q.front() << endl;
	}

	cout << endl;

	for (int i = 0; i < 9; ++i) {
		cout << s.pop() << '\t' << q.de_queue() << endl;
	}

	cout << endl;

	for (auto x : li) {
		s.push(x);
		q.in_queue(x);
		cout << s.top() << '\t' << q.front() << endl;
	}

	cout << endl;

	for (int i = 0; i < 15; i++) {
		cout << s.pop() << '\t' << q.de_queue() << endl;
	}

}

