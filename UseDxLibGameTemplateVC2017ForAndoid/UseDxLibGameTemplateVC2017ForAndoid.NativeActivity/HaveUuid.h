#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class HaveUuid {
public:
	HaveUuid() { uuid = boost::uuids::random_generator()(); };
	virtual ~HaveUuid() {};

	const boost::uuids::uuid& getUuid() const { return uuid; };

	bool operator==(const HaveUuid& rhs) const {
		return uuid == rhs.uuid;
	};
private:
	boost::uuids::uuid uuid;
};