#include "adrc.h"

static float adrc_sign(float val)
{
	if(val >= 0.0f)
		return 1.0f;
	else
		return -1.0f;
}

float adrc_fhan(float v1, float v2, float r0, float h0)
{
	float d = h0 * h0 * r0;
	float a0 = h0 * v2;
	float y = v1 + a0;
	float a1 = sqrtf(d*(d + 8.0f*fabsf(y)));
	float a2 = a0 + adrc_sign(y)*(a1-d)*0.5f;
	float sy = (adrc_sign(y+d) - adrc_sign(y-d))*0.5f;
	float a = (a0 + y - a2)*sy + a2;
	float sa = (adrc_sign(a+d) - adrc_sign(a-d))*0.5f;
	
	return -r0*(a/d - adrc_sign(a))*sa - r0*adrc_sign(a);
}

float adrc_fal(float e, float alpha, float delta)
{
	if(fabsf(e) <= delta){
		return e / (powf(delta, 1.0f-alpha));
	}else
	{
		return powf(fabsf(e), alpha) * adrc_sign(e);
	}
}

void adrc_td(ADRC_TD_Def* td, float v)
{
	float fv = adrc_fhan(td->v1 - v, td->v2, td->r0, td->h0);
	
	td->v1 += td->h * td->v2;
	td->v2 += td->h * fv;
}

void adrc_eso(ADRC_ESO_Def* eso_t, float y)
{
	float e = eso_t->z1 - y;
	float fe = adrc_fal(e, eso_t->alpha1, eso_t->delta1);
	float fe1 = adrc_fal(e, eso_t->alpha2, eso_t->delta2);
	
	eso_t->z1 += eso_t->h*eso_t->z2 - eso_t->beta1*e;
  	eso_t->z2 += eso_t->h*(eso_t->z3 + eso_t->b0*eso_t->u) - eso_t->beta2*fe;
	eso_t->z3 -= eso_t->beta3*fe1;
}

float adrc_nlsef_partial(ADRC_NLSEF_Def* nlsef_t, ADRC_ESO_Def* eso_t, float e1, float e2)
{
	float u;
	nlsef_t->u0 = nlsef_t->kp*adrc_fal(e1, nlsef_t->alpha3, nlsef_t->delta3) + \
                nlsef_t->kd*adrc_fal(e2, nlsef_t->alpha4, nlsef_t->delta4);
	u = (nlsef_t->u0 - eso_t->z3)/eso_t->b0;
	return u;
}

float adrc_calculate(ADRC_TD_Def* td, ADRC_ESO_Def* eso_t, ADRC_NLSEF_Def* nlsef_t, float target, float y)
{
	adrc_td(&td, target);
	adrc_eso(&eso_t, y);
	float e1 = td->v1 - eso_t->z1;
	float e2 = td->v2 - eso_t->z2;
	eso_t->u = adrc_nlsef_partial(&nlsef_t, &eso_t, e1, e2);
	return eso_t->u
}