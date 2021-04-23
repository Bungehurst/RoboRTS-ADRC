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
//extern TD_Controller_Def td_controller_def;

typedef struct
{
	float v1;
	float v2;
	float r0;
	float h0;
	float h;
}ADRC_TD_Def;
//extern ADRC_TD_Def adrc_td_def;
	
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
//extern ADRC_ESO_Def adrc_eso_def;

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
//extern ADRC_NLSEF_Def adrc_nlsef_def;

void adrc_td_init(ADRC_TD_Def* td_t, float h, float r0, float h0);
void adrc_td(ADRC_TD_Def* td, float v);
void adrc_td_control_init(TD_Controller_Def* td_controller, float h, float r2, float h2);
float adrc_td_control(TD_Controller_Def* td_controller, float err);
// void adrc_eso_init(ADRC_ESO_Def* eso_t, float h, float beta1, float beta2, float beta3, float alpha, float delta, float b0);
void adrc_eso_init(ADRC_ESO_Def* eso_t, float h, float beta1, float beta2, float beta3, float alpha1, float alpha2, float delta1, float delta2, float b0);
void adrc_eso(ADRC_ESO_Def* eso_t, float y);
void adrc_leso_init(ADRC_LESO_Def* leso_t, float h, float w, float b0);
void adrc_leso(ADRC_LESO_Def* leso_t, float y);
void adrc_nlsef_init(ADRC_NLSEF_Def* nlsef_t, float h, float r1, float h1, float c);
float adrc_nlsef_partial(ADRC_NLSEF_Def* nlsef_t, ADRC_ESO_Def* eso_t, float e1, float e2);

#endif
