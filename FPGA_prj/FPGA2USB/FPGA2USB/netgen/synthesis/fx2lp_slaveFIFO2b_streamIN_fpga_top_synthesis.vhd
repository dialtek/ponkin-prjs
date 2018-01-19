--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.28xd
--  \   \         Application: netgen
--  /   /         Filename: fx2lp_slaveFIFO2b_streamIN_fpga_top_synthesis.vhd
-- /___/   /\     Timestamp: Wed Nov 20 14:32:37 2013
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -ar Structure -tm fx2lp_slaveFIFO2b_streamIN_fpga_top -w -dir netgen/synthesis -ofmt vhdl -sim fx2lp_slaveFIFO2b_streamIN_fpga_top.ngc fx2lp_slaveFIFO2b_streamIN_fpga_top_synthesis.vhd 
-- Device	: xc3s500e-4-fg320
-- Input file	: fx2lp_slaveFIFO2b_streamIN_fpga_top.ngc
-- Output file	: C:\work\Projects\FPGA_prj\FPGA2USB\FPGA2USB\netgen\synthesis\fx2lp_slaveFIFO2b_streamIN_fpga_top_synthesis.vhd
-- # of Entities	: 1
-- Design Name	: fx2lp_slaveFIFO2b_streamIN_fpga_top
-- Xilinx	: C:\Xilinx\14.2\ISE_DS\ISE\
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Command Line Tools User Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
use UNISIM.VPKG.ALL;

entity fx2lp_slaveFIFO2b_streamIN_fpga_top is
  port (
    CLKFX_OUT : inout STD_LOGIC; 
    input_buf_empty_fl : inout STD_LOGIC; 
    sloe : out STD_LOGIC; 
    CLKIN_IBUFG_OUT : out STD_LOGIC; 
    slrd : out STD_LOGIC; 
    LED0 : out STD_LOGIC; 
    CLK0_OUT : out STD_LOGIC; 
    LOCKED_OUT : out STD_LOGIC; 
    slwr : out STD_LOGIC; 
    RST_IN : in STD_LOGIC := 'X'; 
    flagd : in STD_LOGIC := 'X'; 
    CLKIN_IN : in STD_LOGIC := 'X'; 
    BTN3 : in STD_LOGIC := 'X'; 
    fdata : inout STD_LOGIC_VECTOR ( 7 downto 0 ); 
    faddr : out STD_LOGIC_VECTOR ( 1 downto 0 ) 
  );
end fx2lp_slaveFIFO2b_streamIN_fpga_top;

architecture Structure of fx2lp_slaveFIFO2b_streamIN_fpga_top is
  signal BTN3_IBUF_1 : STD_LOGIC; 
  signal CLK0_OUT_OBUF_3 : STD_LOGIC; 
  signal CLKFX_OUT_OBUF_5 : STD_LOGIC; 
  signal CLKIN_IBUFG_OUT_OBUF_7 : STD_LOGIC; 
  signal LOCKED_OUT_OBUF_11 : STD_LOGIC; 
  signal RST_IN_IBUF_13 : STD_LOGIC; 
  signal btn_on_signal_14 : STD_LOGIC; 
  signal clk_div_CLK0_BUF : STD_LOGIC; 
  signal clk_div_CLKFX_BUF : STD_LOGIC; 
  signal faddr_0_OBUF_19 : STD_LOGIC; 
  signal faddr_1_OBUF_20 : STD_LOGIC; 
  signal input_buf_empty_fl_OBUF_31 : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLK90_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLK180_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLK270_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLK2X_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLK2X180_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLKDV_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_CLKFX180_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_PSDONE_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_7_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_6_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_5_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_4_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_3_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_2_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_1_UNCONNECTED : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_STATUS_0_UNCONNECTED : STD_LOGIC; 
begin
  XST_GND : GND
    port map (
      G => faddr_0_OBUF_19
    );
  XST_VCC : VCC
    port map (
      P => faddr_1_OBUF_20
    );
  btn_on_signal : FD
    port map (
      C => CLKFX_OUT_OBUF_5,
      D => BTN3_IBUF_1,
      Q => btn_on_signal_14
    );
  clk_div_DCM_SP_INST : DCM_SP
    generic map(
      CLKDV_DIVIDE => 2.000000,
      CLKFX_DIVIDE => 25,
      CLKFX_MULTIPLY => 24,
      CLKIN_DIVIDE_BY_2 => FALSE,
      CLKIN_PERIOD => 20.000000,
      CLKOUT_PHASE_SHIFT => "NONE",
      CLK_FEEDBACK => "1X",
      DESKEW_ADJUST => "SYSTEM_SYNCHRONOUS",
      DFS_FREQUENCY_MODE => "LOW",
      DLL_FREQUENCY_MODE => "LOW",
      DSS_MODE => "NONE",
      DUTY_CYCLE_CORRECTION => TRUE,
      PHASE_SHIFT => 0,
      STARTUP_WAIT => FALSE,
      FACTORY_JF => X"C080"
    )
    port map (
      CLKIN => CLKIN_IBUFG_OUT_OBUF_7,
      CLKFB => CLK0_OUT_OBUF_3,
      RST => RST_IN_IBUF_13,
      DSSEN => faddr_0_OBUF_19,
      PSINCDEC => faddr_0_OBUF_19,
      PSEN => faddr_0_OBUF_19,
      PSCLK => faddr_0_OBUF_19,
      CLK0 => clk_div_CLK0_BUF,
      CLK90 => NLW_clk_div_DCM_SP_INST_CLK90_UNCONNECTED,
      CLK180 => NLW_clk_div_DCM_SP_INST_CLK180_UNCONNECTED,
      CLK270 => NLW_clk_div_DCM_SP_INST_CLK270_UNCONNECTED,
      CLK2X => NLW_clk_div_DCM_SP_INST_CLK2X_UNCONNECTED,
      CLK2X180 => NLW_clk_div_DCM_SP_INST_CLK2X180_UNCONNECTED,
      CLKDV => NLW_clk_div_DCM_SP_INST_CLKDV_UNCONNECTED,
      CLKFX => clk_div_CLKFX_BUF,
      CLKFX180 => NLW_clk_div_DCM_SP_INST_CLKFX180_UNCONNECTED,
      LOCKED => LOCKED_OUT_OBUF_11,
      PSDONE => NLW_clk_div_DCM_SP_INST_PSDONE_UNCONNECTED,
      STATUS(7) => NLW_clk_div_DCM_SP_INST_STATUS_7_UNCONNECTED,
      STATUS(6) => NLW_clk_div_DCM_SP_INST_STATUS_6_UNCONNECTED,
      STATUS(5) => NLW_clk_div_DCM_SP_INST_STATUS_5_UNCONNECTED,
      STATUS(4) => NLW_clk_div_DCM_SP_INST_STATUS_4_UNCONNECTED,
      STATUS(3) => NLW_clk_div_DCM_SP_INST_STATUS_3_UNCONNECTED,
      STATUS(2) => NLW_clk_div_DCM_SP_INST_STATUS_2_UNCONNECTED,
      STATUS(1) => NLW_clk_div_DCM_SP_INST_STATUS_1_UNCONNECTED,
      STATUS(0) => NLW_clk_div_DCM_SP_INST_STATUS_0_UNCONNECTED
    );
  clk_div_CLK0_BUFG_INST : BUFG
    port map (
      I => clk_div_CLK0_BUF,
      O => CLK0_OUT_OBUF_3
    );
  clk_div_CLKIN_IBUFG_INST : IBUFG
    generic map(
      CAPACITANCE => "DONT_CARE",
      IBUF_DELAY_VALUE => "0",
      IBUF_LOW_PWR => TRUE,
      IOSTANDARD => "DEFAULT"
    )
    port map (
      I => CLKIN_IN,
      O => CLKIN_IBUFG_OUT_OBUF_7
    );
  clk_div_CLKFX_BUFG_INST : BUFG
    port map (
      I => clk_div_CLKFX_BUF,
      O => CLKFX_OUT_OBUF_5
    );
  RST_IN_IBUF : IBUF
    port map (
      I => RST_IN,
      O => RST_IN_IBUF_13
    );
  flagd_IBUF : IBUF
    port map (
      I => flagd,
      O => input_buf_empty_fl_OBUF_31
    );
  BTN3_IBUF : IBUF
    port map (
      I => BTN3,
      O => BTN3_IBUF_1
    );
  CLKFX_OUT_OBUF : OBUF
    port map (
      I => CLKFX_OUT_OBUF_5,
      O => CLKFX_OUT
    );
  input_buf_empty_fl_OBUF : OBUF
    port map (
      I => input_buf_empty_fl_OBUF_31,
      O => input_buf_empty_fl
    );
  fdata_7_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => fdata(7)
    );
  fdata_6_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => fdata(6)
    );
  fdata_5_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => fdata(5)
    );
  fdata_4_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => fdata(4)
    );
  fdata_3_OBUF : OBUF
    port map (
      I => faddr_0_OBUF_19,
      O => fdata(3)
    );
  fdata_2_OBUF : OBUF
    port map (
      I => faddr_0_OBUF_19,
      O => fdata(2)
    );
  fdata_1_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => fdata(1)
    );
  fdata_0_OBUF : OBUF
    port map (
      I => faddr_0_OBUF_19,
      O => fdata(0)
    );
  sloe_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => sloe
    );
  CLKIN_IBUFG_OUT_OBUF : OBUF
    port map (
      I => CLKIN_IBUFG_OUT_OBUF_7,
      O => CLKIN_IBUFG_OUT
    );
  slrd_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => slrd
    );
  LED0_OBUF : OBUF
    port map (
      I => btn_on_signal_14,
      O => LED0
    );
  CLK0_OUT_OBUF : OBUF
    port map (
      I => CLK0_OUT_OBUF_3,
      O => CLK0_OUT
    );
  LOCKED_OUT_OBUF : OBUF
    port map (
      I => LOCKED_OUT_OBUF_11,
      O => LOCKED_OUT
    );
  slwr_OBUF : OBUF
    port map (
      I => faddr_0_OBUF_19,
      O => slwr
    );
  faddr_1_OBUF : OBUF
    port map (
      I => faddr_1_OBUF_20,
      O => faddr(1)
    );
  faddr_0_OBUF : OBUF
    port map (
      I => faddr_0_OBUF_19,
      O => faddr(0)
    );

end Structure;

