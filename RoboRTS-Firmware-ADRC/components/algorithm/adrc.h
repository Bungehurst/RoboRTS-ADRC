#ifndef __ADRC_H__
#define __ADRC_H__

#include <stdlib.h>
#include <math.h>

typedef struct
{
	float v1;
	float v2;
	float r2;
	float h2;
	float h;
}TD_Controller_Def;

typedef struct
{
	float v1;
	float v2;
	float r0;
	float h0;
	float h;
}ADRC_TD_Def;

typedef struct
{
	float h;
	float beta1;
	float beta2;
	float beta3;
	float alpha1;
	float alpha2;
	float delta1;
	float delta2;
	float u;
	float b0;
	/* ESO */
	float z1;
	float z2;
	float z3;
}ADRC_ESO_Def;

typedef struct
{
	float h;
	float beta1;
	float beta2;
	float u;
	float b0;
	/* LESO */
	float z1;
	float z2;
}ADRC_LESO_Def;	/* Linear ESO */

typedef struct
{
	float h;
	float h1;
	float r1;
	float c;
	float u0;
	float kp;
	float kd;
	float alpha3;
	float delta3;
	float alpha4;
	float delta4;
}ADRC_NLSEF_Def;

void adrc_td(ADRC_TD_Def* td, float v);
void adrc_eso(ADRC_ESO_Def* eso_t, float y);
void adrc_leso(ADRC_LESO_Def* leso_t, float y);
float adrc_nlsef_partial(ADRC_NLSEF_Def* nlsef_t, ADRC_ESO_Def* eso_t, float e1, float e2);
float adrc_calculate(ADRC_TD_Def* td, ADRC_ESO_Def* eso_t, ADRC_NLSEF_Def* nlsef_t, float target, float y);

#endif
