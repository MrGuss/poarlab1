#include <math.h>
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Motor.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_regulator(struct FB_regulator* inst)
{
    /*TODO: Add your code here*/
    inst->integrator.in = inst->e*inst->k_i*inst->dt+inst->iyOld;
    FB_integrator(&(inst->integrator));
    inst->e_p = inst->e * inst->k_p;
    if (inst->e_p>inst->max_abs_value || inst->e_p < -inst->max_abs_value) {
        if (inst->e_p>0) inst->e_p = inst->max_abs_value;
        else inst->e_p = -inst->max_abs_value;
    }
    inst->e_p += inst->integrator.out;
    if (inst->e_p<inst->max_abs_value || inst->e_p > -inst->max_abs_value) inst->u = inst->e_p;
    else
    {
        if (inst->e_p>0) inst->u = inst->max_abs_value;
        else inst->u = -inst->max_abs_value;
    }
    inst->iyOld = inst->u - inst->e_p;
}
