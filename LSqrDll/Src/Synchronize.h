/*==========================================================================;
 *
 *  File:          Synchronize.h
 *  Version:       1.1
 *  Desc:		   Synchronization for multithreading
 *  Author:        Miha Grcar
 *  Created on:    Jul-2008
 *  Last modified: Jul-2008
 *  License:       Common Public License (CPL)
 *  Note:
 *      See ReadMe.txt for additional info and acknowledgements.
 *
 ***************************************************************************/

#ifndef SYNCHRONIZE_H
#define SYNCHRONIZE_H

#include <windows.h>
#include <intrin.h>

class CriticalSection
{
private:
	CRITICAL_SECTION m_critical_section;
public:
	CriticalSection()
	{ 
		InitializeCriticalSection(&m_critical_section);
	}
	~CriticalSection()
	{ 
		DeleteCriticalSection(&m_critical_section); 
	}
	void Enter()
	{ 
		EnterCriticalSection(&m_critical_section); 
	}
	void Leave()
	{ 
#ifndef _DEBUG
		_ReadWriteBarrier(); // in VS 2005 or later, this is enforced all the way up the call tree 
#endif
		LeaveCriticalSection(&m_critical_section); 
	}
};

class CriticalSectionLock 
{
private:
	CriticalSection *m_critical_section;
public:
	CriticalSectionLock(CriticalSection *critical_section)
	{ 
		m_critical_section = critical_section;
		m_critical_section->Enter();
	}
	~CriticalSectionLock()
	{ 
		m_critical_section->Leave();
	}
};

#endif