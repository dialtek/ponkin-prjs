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
static const char *ng0 = "D:/work/Projects/FPGA_prj/Verilog LFSR 8-bit/main/main.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static int ng3[] = {2, 0};
static int ng4[] = {3, 0};
static int ng5[] = {4, 0};
static int ng6[] = {5, 0};
static int ng7[] = {6, 0};
static int ng8[] = {7, 0};



static void NetDecl_10_0(char *t0)
{
    char t5[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;

LAB0:    t1 = (t0 + 2528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(10, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t5, 0, 8);
    t6 = (t5 + 4);
    t7 = (t4 + 4);
    t8 = *((unsigned int *)t4);
    t9 = (t8 >> 7);
    t10 = (t9 & 1);
    *((unsigned int *)t5) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 7);
    t13 = (t12 & 1);
    *((unsigned int *)t6) = t13;
    t14 = (t0 + 3192);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    memset(t18, 0, 8);
    t19 = 1U;
    t20 = t19;
    t21 = (t5 + 4);
    t22 = *((unsigned int *)t5);
    t19 = (t19 & t22);
    t23 = *((unsigned int *)t21);
    t20 = (t20 & t23);
    t24 = (t18 + 4);
    t25 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t25 | t19);
    t26 = *((unsigned int *)t24);
    *((unsigned int *)t24) = (t26 | t20);
    xsi_driver_vfirst_trans(t14, 0, 0U);
    t27 = (t0 + 3096);
    *((int *)t27) = 1;

LAB1:    return;
}

static void Always_14_1(char *t0)
{
    char t6[8];
    char t19[8];
    char t32[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    unsigned int t12;
    int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    unsigned int t37;

LAB0:    t1 = (t0 + 2776U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(14, ng0);
    t2 = (t0 + 3112);
    *((int *)t2) = 1;
    t3 = (t0 + 2808);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(17, ng0);

LAB5:    xsi_set_current_line(19, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = (t0 + 1608);
    t7 = (t0 + 1608);
    t8 = (t7 + 72U);
    t9 = *((char **)t8);
    t10 = ((char*)((ng1)));
    xsi_vlog_generic_convert_bit_index(t6, t9, 2, t10, 32, 1);
    t11 = (t6 + 4);
    t12 = *((unsigned int *)t11);
    t13 = (!(t12));
    if (t13 == 1)
        goto LAB6;

LAB7:    xsi_set_current_line(22, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 0);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 0);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t11 = *((char **)t10);
    t20 = ((char*)((ng2)));
    xsi_vlog_generic_convert_bit_index(t19, t11, 2, t20, 32, 1);
    t21 = (t19 + 4);
    t22 = *((unsigned int *)t21);
    t13 = (!(t22));
    if (t13 == 1)
        goto LAB8;

LAB9:    xsi_set_current_line(25, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 1);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 1);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t11 = *((char **)t10);
    t20 = ((char*)((ng3)));
    xsi_vlog_generic_convert_bit_index(t19, t11, 2, t20, 32, 1);
    t21 = (t19 + 4);
    t22 = *((unsigned int *)t21);
    t13 = (!(t22));
    if (t13 == 1)
        goto LAB10;

LAB11:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 2);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 2);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t11 = *((char **)t10);
    t20 = ((char*)((ng4)));
    xsi_vlog_generic_convert_bit_index(t19, t11, 2, t20, 32, 1);
    t21 = (t19 + 4);
    t22 = *((unsigned int *)t21);
    t13 = (!(t22));
    if (t13 == 1)
        goto LAB12;

LAB13:    xsi_set_current_line(31, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 3);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 3);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1208U);
    t9 = *((char **)t8);
    t22 = *((unsigned int *)t6);
    t23 = *((unsigned int *)t9);
    t24 = (t22 ^ t23);
    *((unsigned int *)t19) = t24;
    t8 = (t6 + 4);
    t10 = (t9 + 4);
    t11 = (t19 + 4);
    t25 = *((unsigned int *)t8);
    t26 = *((unsigned int *)t10);
    t27 = (t25 | t26);
    *((unsigned int *)t11) = t27;
    t28 = *((unsigned int *)t11);
    t29 = (t28 != 0);
    if (t29 == 1)
        goto LAB14;

LAB15:
LAB16:    t20 = (t0 + 1608);
    t21 = (t0 + 1608);
    t33 = (t21 + 72U);
    t34 = *((char **)t33);
    t35 = ((char*)((ng5)));
    xsi_vlog_generic_convert_bit_index(t32, t34, 2, t35, 32, 1);
    t36 = (t32 + 4);
    t37 = *((unsigned int *)t36);
    t13 = (!(t37));
    if (t13 == 1)
        goto LAB17;

LAB18:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 4);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 4);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1208U);
    t9 = *((char **)t8);
    t22 = *((unsigned int *)t6);
    t23 = *((unsigned int *)t9);
    t24 = (t22 ^ t23);
    *((unsigned int *)t19) = t24;
    t8 = (t6 + 4);
    t10 = (t9 + 4);
    t11 = (t19 + 4);
    t25 = *((unsigned int *)t8);
    t26 = *((unsigned int *)t10);
    t27 = (t25 | t26);
    *((unsigned int *)t11) = t27;
    t28 = *((unsigned int *)t11);
    t29 = (t28 != 0);
    if (t29 == 1)
        goto LAB19;

LAB20:
LAB21:    t20 = (t0 + 1608);
    t21 = (t0 + 1608);
    t33 = (t21 + 72U);
    t34 = *((char **)t33);
    t35 = ((char*)((ng6)));
    xsi_vlog_generic_convert_bit_index(t32, t34, 2, t35, 32, 1);
    t36 = (t32 + 4);
    t37 = *((unsigned int *)t36);
    t13 = (!(t37));
    if (t13 == 1)
        goto LAB22;

LAB23:    xsi_set_current_line(37, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 5);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 5);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1208U);
    t9 = *((char **)t8);
    t22 = *((unsigned int *)t6);
    t23 = *((unsigned int *)t9);
    t24 = (t22 ^ t23);
    *((unsigned int *)t19) = t24;
    t8 = (t6 + 4);
    t10 = (t9 + 4);
    t11 = (t19 + 4);
    t25 = *((unsigned int *)t8);
    t26 = *((unsigned int *)t10);
    t27 = (t25 | t26);
    *((unsigned int *)t11) = t27;
    t28 = *((unsigned int *)t11);
    t29 = (t28 != 0);
    if (t29 == 1)
        goto LAB24;

LAB25:
LAB26:    t20 = (t0 + 1608);
    t21 = (t0 + 1608);
    t33 = (t21 + 72U);
    t34 = *((char **)t33);
    t35 = ((char*)((ng7)));
    xsi_vlog_generic_convert_bit_index(t32, t34, 2, t35, 32, 1);
    t36 = (t32 + 4);
    t37 = *((unsigned int *)t36);
    t13 = (!(t37));
    if (t13 == 1)
        goto LAB27;

LAB28:    xsi_set_current_line(40, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t14 = (t12 >> 6);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 6);
    t18 = (t17 & 1);
    *((unsigned int *)t5) = t18;
    t8 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t11 = *((char **)t10);
    t20 = ((char*)((ng8)));
    xsi_vlog_generic_convert_bit_index(t19, t11, 2, t20, 32, 1);
    t21 = (t19 + 4);
    t22 = *((unsigned int *)t21);
    t13 = (!(t22));
    if (t13 == 1)
        goto LAB29;

LAB30:    goto LAB2;

LAB6:    xsi_vlogvar_wait_assign_value(t4, t5, 0, *((unsigned int *)t6), 1, 0LL);
    goto LAB7;

LAB8:    xsi_vlogvar_wait_assign_value(t8, t6, 0, *((unsigned int *)t19), 1, 0LL);
    goto LAB9;

LAB10:    xsi_vlogvar_wait_assign_value(t8, t6, 0, *((unsigned int *)t19), 1, 0LL);
    goto LAB11;

LAB12:    xsi_vlogvar_wait_assign_value(t8, t6, 0, *((unsigned int *)t19), 1, 0LL);
    goto LAB13;

LAB14:    t30 = *((unsigned int *)t19);
    t31 = *((unsigned int *)t11);
    *((unsigned int *)t19) = (t30 | t31);
    goto LAB16;

LAB17:    xsi_vlogvar_wait_assign_value(t20, t19, 0, *((unsigned int *)t32), 1, 0LL);
    goto LAB18;

LAB19:    t30 = *((unsigned int *)t19);
    t31 = *((unsigned int *)t11);
    *((unsigned int *)t19) = (t30 | t31);
    goto LAB21;

LAB22:    xsi_vlogvar_wait_assign_value(t20, t19, 0, *((unsigned int *)t32), 1, 0LL);
    goto LAB23;

LAB24:    t30 = *((unsigned int *)t19);
    t31 = *((unsigned int *)t11);
    *((unsigned int *)t19) = (t30 | t31);
    goto LAB26;

LAB27:    xsi_vlogvar_wait_assign_value(t20, t19, 0, *((unsigned int *)t32), 1, 0LL);
    goto LAB28;

LAB29:    xsi_vlogvar_wait_assign_value(t8, t6, 0, *((unsigned int *)t19), 1, 0LL);
    goto LAB30;

}


extern void work_m_00000000001514513887_2183612458_init()
{
	static char *pe[] = {(void *)NetDecl_10_0,(void *)Always_14_1};
	xsi_register_didat("work_m_00000000001514513887_2183612458", "isim/m_seq_8bit_isim_beh.exe.sim/work/m_00000000001514513887_2183612458.didat");
	xsi_register_executes(pe);
}
