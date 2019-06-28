#pragma once

#include <memory>

namespace seed_cpp { namespace rest {

	template<typename _Entity>
	struct PaginationData
	{
		std::vector<_Entity> m_content;
		unsigned int m_totalElements;
		bool m_first;
		bool m_last;
		unsigned int m_number;
		unsigned int m_numberOfElements;
		unsigned int m_size;
		unsigned int m_totalPages;
	};

}}