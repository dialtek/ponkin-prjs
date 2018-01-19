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
static const char *ng0 = "D:/work/Projects/FPGA_prj/FPGA2USB/DDC_316_SPI_module/SPI_module/main.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_1258338084_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_3205524545_0831356973_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned int t3;
    unsigned int t4;
    unsigned int t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    unsigned char t11;
    int t12;
    unsigned char t13;
    int t14;

LAB0:    xsi_set_current_line(32, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t3 = (0 - 0);
    t4 = (t3 * 1U);
    t5 = (0 + t4);
    t1 = (t2 + t5);
    t6 = (t0 + 3936);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 8U);
    xsi_driver_first_trans_delta(t6, 0U, 8U, 0LL);
    xsi_set_current_line(34, ng0);
    t1 = (t0 + 1472U);
    t11 = ieee_p_2592010699_sub_1258338084_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t11 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 3840);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(36, ng0);
    t2 = (t0 + 2288U);
    t6 = *((char **)t2);
    t12 = *((int *)t6);
    t13 = (t12 == 8);
    if (t13 != 0)
        goto LAB5;

LAB7:    xsi_set_current_line(37, ng0);
    t1 = (t0 + 2288U);
    t2 = *((char **)t1);
    t12 = *((int *)t2);
    t14 = (t12 + 1);
    t1 = (t0 + 2288U);
    t6 = *((char **)t1);
    t1 = (t6 + 0);
    *((int *)t1) = t14;

LAB6:    goto LAB3;

LAB5:    xsi_set_current_line(36, ng0);
    t2 = (t0 + 4000);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    goto LAB6;

}

static void work_a_3205524545_0831356973_p_1(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(84, ng0);

LAB3:    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 4064);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 3856);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_3205524545_0831356973_init()
{
	static char *pe[] = {(void *)work_a_3205524545_0831356973_p_0,(void *)work_a_3205524545_0831356973_p_1};
	xsi_register_didat("work_a_3205524545_0831356973", "isim/FPGA_SPI_module_isim_beh.exe.sim/work/a_3205524545_0831356973.didat");
	xsi_register_executes(pe);
}
