#pragma once

namespace seed_cpp { namespace dal {

	class ISaveDAO
	{
	public:
		virtual ~ISaveDAO(){};

		virtual void addEntity() = 0;
		virtual void updateEntity() = 0;
		virtual void deleteEntity() = 0;
	};

}}

