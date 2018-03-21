#pragma once

namespace seed_cpp { namespace dal {

	class ILoadDAO
	{
	public:
		virtual ~ILoadDAO(){};

		virtual void loadAll() const = 0;
	};

}}

