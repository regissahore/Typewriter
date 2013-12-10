/**
 * ���ߺе��ĵ���
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "SwitchBox.h"

class CWiringDoc : public CDocument
{
public:
	CWiringDoc();
	virtual ~CWiringDoc();
	DECLARE_DYNCREATE(CWiringDoc)
	virtual void Serialize(CArchive& archive);
	void setInitialized(bool value);
	bool initialized() const;
	SwitchBox& switchBox();
	void initSwitchBox();

private:
	SwitchBox _switchBox;
	bool _initialized;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};
