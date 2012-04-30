/*
 *  fbEvent.cpp
 *  Created on: Mar 19, 2012
 *
 *  Copyright (c) 2012 by Leo Hoo
 *  lion@9465.net
 */

#include <exlib/fiber.h>

namespace exlib
{
void Event::wait()
{
	if (!m_set)
	{
		Service* pService = Service::getFiberService();

		m_blocks.put(pService->m_running);
		pService->switchtonext();
	}
}

void Event::pulse()
{
	Service* pService = NULL;
	Fiber* cntxt;

	while (!m_blocks.empty())
	{
		cntxt = m_blocks.get();
		if (pService == NULL)
			pService = Service::getFiberService();
		pService->m_resume.put(cntxt);
	}
}

void Event::set()
{
	m_set = true;
	pulse();
}

void Event::reset()
{
	m_set = false;
}

bool Event::isset()
{
	return m_set;
}

}
