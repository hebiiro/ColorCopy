#pragma once

#include "Resource.h"

class CColorCopyApp : public CWinApp
{
public:

	CColorCopyApp();

public:

	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CColorCopyApp theApp;
