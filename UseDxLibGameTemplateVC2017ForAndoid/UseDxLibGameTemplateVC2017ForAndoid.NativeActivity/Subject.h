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
	//削除以前に中身がない
	if (!t) return;

	for (auto it = objs.cbegin(); it != objs.cend();) {
		auto s = it->lock();
		//中身があるか確認
		if (s && t == s) {
			it = objs.erase(it);
			return;
		}
		else if (!s) { //中身が無いならもういらないのでついでに消す.
			it = objs.erase(it);
		}
		else ++it;
	}
}
