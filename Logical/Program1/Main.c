
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
    enable = 1;
    count = 0;
    speed = 0;
    fb_motor.dt = 0.01;
    fb_motor.ke = 0.24;
    fb_motor.Tm = 0.1;
    fb_motor2.dt = 0.01;
    fb_motor2.ke = 0.24;
    fb_motor2.Tm = 0.1;
    fb_regulator.dt = 0.01;
    fb_regulator.k_p = 5;
    fb_regulator.k_i = 3;
    fb_regulator.max_abs_value = 24;
	
}

void _CYCLIC ProgramCyclic(void)
{
    if (enable == 1){
        count +=10;
        if (count >=400 && count <=2000) speed = 40;
        else{
            speed = 5;
        }
        if (count>=2000){
            count=0;
        }
    }
    else{
        speed = 0;
    }
    fb_regulator.e = speed - fb_motor.w;
    fb_motor2.u = speed * fb_motor2.ke;
    fb_motor.u = fb_regulator.u*fb_motor.ke;
    FB_regulator(&fb_regulator);
    FB_motor(&fb_motor);
    FB_motor(&fb_motor2);
	
}

void _EXIT ProgramExit(void)
{

}

