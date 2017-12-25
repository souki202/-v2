#pragma once
#include <vector>
#include <memory>

template <typename T>
class Subject {
public:
	Subject() {};
	virtual ~Subject() {};

	virtual void addListener(const std::weak_ptr<T>& obj);
	virtual void removeListener(const std::weak_ptr<T>& obj);
protected:
	std::vector<std::weak_ptr<T>> objs;
};

template<typename T>
inline void Subject<T>::addListener(const std::weak_ptr<T>& obj)
{
	objs.push_back(obj);
}

template<typename T>
inline void Subject<T>::removeListener(const std::weak_ptr<T>& obj)
{
	auto t = obj.lock();
	//�폜�ȑO�ɒ��g���Ȃ�
	if (!t) return;

	for (auto it = objs.cbegin(); it != objs.cend();) {
		auto s = it->lock();
		//���g�����邩�m�F
		if (s && t == s) {
			it = objs.erase(it);
			return;
		}
		else if (!s) { //���g�������Ȃ��������Ȃ��̂ł��łɏ���.
			it = objs.erase(it);
		}
		else ++it;
	}
}
