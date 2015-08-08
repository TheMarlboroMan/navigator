#ifndef CON_TURNO_I
#define CON_TURNO_I

namespace App_Interfaces
{

class Con_turno_I
{
	////////////////////
	//Interface pública.

	public:

	~Con_turno_I() {}
	virtual void turno(float)=0;
};

}

#endif
