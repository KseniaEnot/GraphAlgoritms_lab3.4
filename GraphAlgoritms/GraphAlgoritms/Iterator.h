#pragma once
class Iterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
	virtual bool newconnection() = 0;
	virtual int beforecur() = 0;
};
