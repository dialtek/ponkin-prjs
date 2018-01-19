/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/work/Projects/FPGA_prj/ProfileMeter/MainSch/StateMachine.vhd";
extern char *IEEE_P_3620187407;

char *ieee_p_3620187407_sub_121739838_3965413181(char *, char *, char *, char *, char *, char *);


static void work_a_2603445318_3212880686_p_0(char *t0)
{
    char t29[16];
    char t30[16];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    unsigned char t7;
    unsigned char t8;
    int t9;
    int t10;
    int t11;
    unsigned char t12;
    unsigned char t13;
    char *t14;
    char *t15;
    unsigned char t16;
    unsigned char t17;
    char *t18;
    int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned char t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    int t31;
    int t32;
    int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;

LAB0:    xsi_set_current_line(47, ng0);
    t1 = (t0 + 3088U);
    t2 = *((char **)t1);
    t1 = (t0 + 5728);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 4U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(49, ng0);
    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t7 = *((unsigned char *)t2);
    t8 = (t7 == (unsigned char)3);
    if (t8 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 5616);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(51, ng0);
    t1 = (t0 + 2152U);
    t3 = *((char **)t1);
    t1 = (t0 + 3088U);
    t4 = *((char **)t1);
    t9 = xsi_mem_cmp(t4, t3, 4U);
    if (t9 == 1)
        goto LAB6;

LAB10:    t1 = (t0 + 3208U);
    t5 = *((char **)t1);
    t10 = xsi_mem_cmp(t5, t3, 4U);
    if (t10 == 1)
        goto LAB7;

LAB11:    t1 = (t0 + 3328U);
    t6 = *((char **)t1);
    t11 = xsi_mem_cmp(t6, t3, 4U);
    if (t11 == 1)
        goto LAB8;

LAB12:
LAB9:    xsi_set_current_line(108, ng0);
    t1 = (t0 + 3088U);
    t2 = *((char **)t1);
    t1 = (t0 + 5728);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 4U);
    xsi_driver_first_trans_fast(t1);

LAB5:    goto LAB3;

LAB6:    xsi_set_current_line(55, ng0);
    t1 = (t0 + 1152U);
    t13 = xsi_signal_has_event(t1);
    if (t13 == 1)
        goto LAB17;

LAB18:    t12 = (unsigned char)0;

LAB19:    if (t12 != 0)
        goto LAB14;

LAB16:
LAB15:    xsi_set_current_line(63, ng0);
    t1 = (t0 + 3448U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t7 = (t9 > 15);
    if (t7 != 0)
        goto LAB22;

LAB24:    xsi_set_current_line(67, ng0);
    t1 = (t0 + 3088U);
    t2 = *((char **)t1);
    t1 = (t0 + 5728);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 4U);
    xsi_driver_first_trans_fast(t1);

LAB23:    goto LAB5;

LAB7:    xsi_set_current_line(76, ng0);
    t1 = (t0 + 5920);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_delta(t1, 19U, 1, 0LL);
    xsi_set_current_line(77, ng0);
    t1 = (t0 + 5920);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_delta(t1, 18U, 1, 0LL);
    xsi_set_current_line(78, ng0);
    t1 = (t0 + 5920);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_delta(t1, 17U, 1, 0LL);
    xsi_set_current_line(79, ng0);
    t1 = (t0 + 5920);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_delta(t1, 16U, 1, 0LL);
    xsi_set_current_line(81, ng0);
    t1 = (t0 + 9817);
    *((int *)t1) = 0;
    t2 = (t0 + 9821);
    *((int *)t2) = 15;
    t9 = 0;
    t10 = 15;

LAB25:    if (t9 <= t10)
        goto LAB26;

LAB28:    xsi_set_current_line(86, ng0);
    t1 = (t0 + 3328U);
    t2 = *((char **)t1);
    t1 = (t0 + 5728);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 4U);
    xsi_driver_first_trans_fast(t1);
    goto LAB5;

LAB8:    xsi_set_current_line(90, ng0);
    t1 = (t0 + 992U);
    t8 = xsi_signal_has_event(t1);
    if (t8 == 1)
        goto LAB33;

LAB34:    t7 = (unsigned char)0;

LAB35:    if (t7 != 0)
        goto LAB30;

LAB32:
LAB31:    xsi_set_current_line(97, ng0);
    t1 = (t0 + 3568U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t7 = (t9 > 19);
    if (t7 != 0)
        goto LAB36;

LAB38:    xsi_set_current_line(101, ng0);
    t1 = (t0 + 3328U);
    t2 = *((char **)t1);
    t1 = (t0 + 5728);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 4U);
    xsi_driver_first_trans_fast(t1);

LAB37:    goto LAB5;

LAB13:;
LAB14:    xsi_set_current_line(57, ng0);
    t14 = (t0 + 2312U);
    t18 = *((char **)t14);
    t19 = (15 - 15);
    t20 = (t19 * -1);
    t21 = (1U * t20);
    t22 = (0 + t21);
    t14 = (t18 + t22);
    t23 = *((unsigned char *)t14);
    t24 = (t0 + 5792);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    *((unsigned char *)t28) = t23;
    xsi_driver_first_trans_fast(t24);
    xsi_set_current_line(58, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t1 = (t0 + 9676U);
    t3 = (t0 + 9816);
    t5 = (t30 + 0U);
    t6 = (t5 + 0U);
    *((int *)t6) = 0;
    t6 = (t5 + 4U);
    *((int *)t6) = 0;
    t6 = (t5 + 8U);
    *((int *)t6) = 1;
    t9 = (0 - 0);
    t20 = (t9 * 1);
    t20 = (t20 + 1);
    t6 = (t5 + 12U);
    *((unsigned int *)t6) = t20;
    t6 = ieee_p_3620187407_sub_121739838_3965413181(IEEE_P_3620187407, t29, t2, t1, t3, t30);
    t14 = (t29 + 12U);
    t20 = *((unsigned int *)t14);
    t20 = (t20 * 1U);
    t7 = (16U != t20);
    if (t7 == 1)
        goto LAB20;

LAB21:    t15 = (t0 + 5856);
    t18 = (t15 + 56U);
    t24 = *((char **)t18);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memcpy(t26, t6, 16U);
    xsi_driver_first_trans_fast(t15);
    xsi_set_current_line(59, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t7 = *((unsigned char *)t2);
    t1 = (t0 + 5856);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = t7;
    xsi_driver_first_trans_delta(t1, 15U, 1, 0LL);
    xsi_set_current_line(60, ng0);
    t1 = (t0 + 3448U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t10 = (t9 + 1);
    t1 = (t0 + 3448U);
    t3 = *((char **)t1);
    t1 = (t3 + 0);
    *((int *)t1) = t10;
    goto LAB15;

LAB17:    t14 = (t0 + 1192U);
    t15 = *((char **)t14);
    t16 = *((unsigned char *)t15);
    t17 = (t16 == (unsigned char)3);
    t12 = t17;
    goto LAB19;

LAB20:    xsi_size_not_matching(16U, t20, 0);
    goto LAB21;

LAB22:    xsi_set_current_line(64, ng0);
    t1 = (t0 + 3208U);
    t3 = *((char **)t1);
    t1 = (t0 + 5728);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t14 = *((char **)t6);
    memcpy(t14, t3, 4U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(65, ng0);
    t1 = (t0 + 3448U);
    t2 = *((char **)t1);
    t1 = (t2 + 0);
    *((int *)t1) = 0;
    goto LAB23;

LAB26:    xsi_set_current_line(82, ng0);
    t3 = (t0 + 2312U);
    t4 = *((char **)t3);
    t3 = (t0 + 9817);
    t11 = *((int *)t3);
    t19 = (t11 - 15);
    t20 = (t19 * -1);
    xsi_vhdl_check_range_of_index(15, 0, -1, *((int *)t3));
    t21 = (1U * t20);
    t22 = (0 + t21);
    t5 = (t4 + t22);
    t7 = *((unsigned char *)t5);
    t6 = (t0 + 9817);
    t31 = *((int *)t6);
    t32 = (t31 + 4);
    t33 = (t32 - 19);
    t34 = (t33 * -1);
    t35 = (1 * t34);
    t36 = (0U + t35);
    t14 = (t0 + 5920);
    t15 = (t14 + 56U);
    t18 = *((char **)t15);
    t24 = (t18 + 56U);
    t25 = *((char **)t24);
    *((unsigned char *)t25) = t7;
    xsi_driver_first_trans_delta(t14, t36, 1, 0LL);

LAB27:    t1 = (t0 + 9817);
    t9 = *((int *)t1);
    t2 = (t0 + 9821);
    t10 = *((int *)t2);
    if (t9 == t10)
        goto LAB28;

LAB29:    t11 = (t9 + 1);
    t9 = t11;
    t3 = (t0 + 9817);
    *((int *)t3) = t9;
    goto LAB25;

LAB30:    xsi_set_current_line(92, ng0);
    t2 = (t0 + 2472U);
    t4 = *((char **)t2);
    t2 = (t0 + 3568U);
    t5 = *((char **)t2);
    t9 = *((int *)t5);
    t10 = (19 - t9);
    t11 = (t10 - 19);
    t20 = (t11 * -1);
    xsi_vhdl_check_range_of_index(19, 0, -1, t10);
    t21 = (1U * t20);
    t22 = (0 + t21);
    t2 = (t4 + t22);
    t16 = *((unsigned char *)t2);
    t6 = (t0 + 5984);
    t14 = (t6 + 56U);
    t15 = *((char **)t14);
    t18 = (t15 + 56U);
    t24 = *((char **)t18);
    *((unsigned char *)t24) = t16;
    xsi_driver_first_trans_fast(t6);
    xsi_set_current_line(93, ng0);
    t1 = (t0 + 3568U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t10 = (t9 + 1);
    t1 = (t0 + 3568U);
    t3 = *((char **)t1);
    t1 = (t3 + 0);
    *((int *)t1) = t10;
    goto LAB31;

LAB33:    t2 = (t0 + 1032U);
    t3 = *((char **)t2);
    t12 = *((unsigned char *)t3);
    t13 = (t12 == (unsigned char)3);
    t7 = t13;
    goto LAB35;

LAB36:    xsi_set_current_line(98, ng0);
    t1 = (t0 + 3088U);
    t3 = *((char **)t1);
    t1 = (t0 + 5728);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t14 = *((char **)t6);
    memcpy(t14, t3, 4U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(99, ng0);
    t1 = (t0 + 3568U);
    t2 = *((char **)t1);
    t1 = (t2 + 0);
    *((int *)t1) = 0;
    goto LAB37;

}

static void work_a_2603445318_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(117, ng0);

LAB3:    t1 = (t0 + 2792U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 6048);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 5632);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2603445318_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(118, ng0);

LAB3:    t1 = (t0 + 2632U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 6112);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 5648);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2603445318_3212880686_p_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;

LAB0:    xsi_set_current_line(119, ng0);

LAB3:    t1 = (t0 + 6176);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:
LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_2603445318_3212880686_init()
{
	static char *pe[] = {(void *)work_a_2603445318_3212880686_p_0,(void *)work_a_2603445318_3212880686_p_1,(void *)work_a_2603445318_3212880686_p_2,(void *)work_a_2603445318_3212880686_p_3};
	xsi_register_didat("work_a_2603445318_3212880686", "isim/StateMachine_isim_beh.exe.sim/work/a_2603445318_3212880686.didat");
	xsi_register_executes(pe);
}
