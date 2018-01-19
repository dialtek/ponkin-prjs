--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.28xd
--  \   \         Application: netgen
--  /   /         Filename: fx2lp_slaveFIFO2b_streamIN_fpga_top_map.vhd
-- /___/   /\     Timestamp: Thu Oct 03 14:16:24 2013
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -s 4 -pcf fx2lp_slaveFIFO2b_streamIN_fpga_top.pcf -rpw 100 -tpw 0 -ar Structure -tm fx2lp_slaveFIFO2b_streamIN_fpga_top -w -dir netgen/map -ofmt vhdl -sim fx2lp_slaveFIFO2b_streamIN_fpga_top_map.ncd fx2lp_slaveFIFO2b_streamIN_fpga_top_map.vhd 
-- Device	: 3s500efg320-4 (PRODUCTION 1.27 2012-07-09)
-- Input file	: fx2lp_slaveFIFO2b_streamIN_fpga_top_map.ncd
-- Output file	: C:\work\Projects\FPGA_prj\FPGA2USB\FPGA2USB\netgen\map\fx2lp_slaveFIFO2b_streamIN_fpga_top_map.vhd
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
library SIMPRIM;
use SIMPRIM.VCOMPONENTS.ALL;
use SIMPRIM.VPACKAGE.ALL;

entity fx2lp_slaveFIFO2b_streamIN_fpga_top is
  port (
    CLKFX_OUT : inout STD_LOGIC; 
    input_buf_empty_fl : inout STD_LOGIC; 
    sloe : out STD_LOGIC; 
    CLKIN_IBUFG_OUT : out STD_LOGIC; 
    slrd : out STD_LOGIC; 
    CLK0_OUT : out STD_LOGIC; 
    LOCKED_OUT : out STD_LOGIC; 
    slwr : out STD_LOGIC; 
    Sw7 : in STD_LOGIC := 'X'; 
    RST_IN : in STD_LOGIC := 'X'; 
    flagd : in STD_LOGIC := 'X'; 
    Sw7_led : out STD_LOGIC; 
    CLKIN_IN : in STD_LOGIC := 'X'; 
    fdata : inout STD_LOGIC_VECTOR ( 7 downto 0 ); 
    faddr : out STD_LOGIC_VECTOR ( 1 downto 0 ) 
  );
end fx2lp_slaveFIFO2b_streamIN_fpga_top;

architecture Structure of fx2lp_slaveFIFO2b_streamIN_fpga_top is
  signal Sw7_IBUF_87 : STD_LOGIC; 
  signal CLKIN_IBUFG_OUT_OBUF_88 : STD_LOGIC; 
  signal CLK0_OUT_OBUF_91 : STD_LOGIC; 
  signal LOCKED_OUT_OBUF_92 : STD_LOGIC; 
  signal RST_IN_IBUF_93 : STD_LOGIC; 
  signal CLKFX_OUT_OBUF_94 : STD_LOGIC; 
  signal clk_div_CLKFX_BUF : STD_LOGIC; 
  signal clk_div_CLK0_BUF : STD_LOGIC; 
  signal input_buf_empty_fl_O : STD_LOGIC; 
  signal Sw7_INBUF : STD_LOGIC; 
  signal CLKIN_IBUFG_OUT_O : STD_LOGIC; 
  signal faddr_0_O : STD_LOGIC; 
  signal faddr_1_O : STD_LOGIC; 
  signal fdata_0_O : STD_LOGIC; 
  signal fdata_1_O : STD_LOGIC; 
  signal fdata_2_O : STD_LOGIC; 
  signal fdata_3_O : STD_LOGIC; 
  signal fdata_4_O : STD_LOGIC; 
  signal fdata_5_O : STD_LOGIC; 
  signal fdata_6_O : STD_LOGIC; 
  signal fdata_7_O : STD_LOGIC; 
  signal CLKIN_IN_INBUF : STD_LOGIC; 
  signal sloe_O : STD_LOGIC; 
  signal flagd_INBUF : STD_LOGIC; 
  signal CLK0_OUT_O : STD_LOGIC; 
  signal slrd_O : STD_LOGIC; 
  signal LOCKED_OUT_O : STD_LOGIC; 
  signal RST_IN_INBUF : STD_LOGIC; 
  signal Sw7_led_O : STD_LOGIC; 
  signal slwr_O : STD_LOGIC; 
  signal CLKFX_OUT_O : STD_LOGIC; 
  signal clk_div_CLKFX_BUFG_INST_S_INVNOT : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLK90 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLK180 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLK270 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLK2X : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLK2X180 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLKDV : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLKFX180 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS7 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS6 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS5 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS4 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS3 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS2 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS1 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_STATUS0 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_PSDONE : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_PSCLKINV_289 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLKFB_BUF_288 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLKIN_BUF_287 : STD_LOGIC; 
  signal clk_div_CLK0_BUFG_INST_S_INVNOT : STD_LOGIC; 
  signal faddr_0_OUTPUT_OFF_O1INV_126 : STD_LOGIC; 
  signal faddr_1_OUTPUT_OFF_O1INV_134 : STD_LOGIC; 
  signal fdata_0_OUTPUT_OFF_O1INV_142 : STD_LOGIC; 
  signal fdata_1_OUTPUT_OFF_O1INV_150 : STD_LOGIC; 
  signal fdata_2_OUTPUT_OFF_O1INV_158 : STD_LOGIC; 
  signal fdata_3_OUTPUT_OFF_O1INV_166 : STD_LOGIC; 
  signal fdata_4_OUTPUT_OFF_O1INV_174 : STD_LOGIC; 
  signal fdata_5_OUTPUT_OFF_O1INV_182 : STD_LOGIC; 
  signal fdata_6_OUTPUT_OFF_O1INV_190 : STD_LOGIC; 
  signal fdata_7_OUTPUT_OFF_O1INV_198 : STD_LOGIC; 
  signal sloe_OUTPUT_OFF_O1INV_212 : STD_LOGIC; 
  signal slrd_OUTPUT_OFF_O1INV_234 : STD_LOGIC; 
  signal Sw7_led_OUTPUT_OFF_O1INV_256 : STD_LOGIC; 
  signal slwr_OUTPUT_OFF_O1INV_264 : STD_LOGIC; 
  signal GND : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_DSSEN_UNCONNECTED : STD_LOGIC; 
begin
  input_buf_empty_fl_OBUF : X_OBUF
    port map (
      I => input_buf_empty_fl_O,
      O => input_buf_empty_fl
    );
  Sw7_IBUF : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => Sw7,
      O => Sw7_INBUF
    );
  CLKIN_IBUFG_OUT_OBUF : X_OBUF
    port map (
      I => CLKIN_IBUFG_OUT_O,
      O => CLKIN_IBUFG_OUT
    );
  faddr_0_OBUF : X_OBUF
    port map (
      I => faddr_0_O,
      O => faddr(0)
    );
  faddr_1_OBUF : X_OBUF
    port map (
      I => faddr_1_O,
      O => faddr(1)
    );
  fdata_0_OBUF : X_OBUF
    port map (
      I => fdata_0_O,
      O => fdata(0)
    );
  fdata_1_OBUF : X_OBUF
    port map (
      I => fdata_1_O,
      O => fdata(1)
    );
  fdata_2_OBUF : X_OBUF
    port map (
      I => fdata_2_O,
      O => fdata(2)
    );
  fdata_3_OBUF : X_OBUF
    port map (
      I => fdata_3_O,
      O => fdata(3)
    );
  fdata_4_OBUF : X_OBUF
    port map (
      I => fdata_4_O,
      O => fdata(4)
    );
  fdata_5_OBUF : X_OBUF
    port map (
      I => fdata_5_O,
      O => fdata(5)
    );
  fdata_6_OBUF : X_OBUF
    port map (
      I => fdata_6_O,
      O => fdata(6)
    );
  fdata_7_OBUF : X_OBUF
    port map (
      I => fdata_7_O,
      O => fdata(7)
    );
  clk_div_CLKIN_IBUFG_INST : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IN,
      O => CLKIN_IN_INBUF
    );
  sloe_OBUF : X_OBUF
    port map (
      I => sloe_O,
      O => sloe
    );
  flagd_IBUF : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => flagd,
      O => flagd_INBUF
    );
  CLK0_OUT_OBUF : X_OBUF
    port map (
      I => CLK0_OUT_O,
      O => CLK0_OUT
    );
  slrd_OBUF : X_OBUF
    port map (
      I => slrd_O,
      O => slrd
    );
  LOCKED_OUT_OBUF : X_OBUF
    port map (
      I => LOCKED_OUT_O,
      O => LOCKED_OUT
    );
  RST_IN_IBUF : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => RST_IN,
      O => RST_IN_INBUF
    );
  Sw7_led_OBUF : X_OBUF
    port map (
      I => Sw7_led_O,
      O => Sw7_led
    );
  slwr_OBUF : X_OBUF
    port map (
      I => slwr_O,
      O => slwr
    );
  CLKFX_OUT_OBUF : X_OBUF
    port map (
      I => CLKFX_OUT_O,
      O => CLKFX_OUT
    );
  clk_div_CLKFX_BUFG_INST : X_BUFGMUX
    port map (
      I0 => clk_div_CLKFX_BUF,
      I1 => GND,
      S => clk_div_CLKFX_BUFG_INST_S_INVNOT,
      O => CLKFX_OUT_OBUF_94
    );
  clk_div_CLKFX_BUFG_INST_SINV : X_INV
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => clk_div_CLKFX_BUFG_INST_S_INVNOT
    );
  clk_div_DCM_SP_INST_PSCLKINV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => clk_div_DCM_SP_INST_PSCLKINV_289
    );
  clk_div_DCM_SP_INST : X_DCM_SP
    generic map(
      DUTY_CYCLE_CORRECTION => TRUE,
      FACTORY_JF => X"C080",
      CLKDV_DIVIDE => 2.000000,
      CLKFX_DIVIDE => 25,
      CLKFX_MULTIPLY => 24,
      CLKOUT_PHASE_SHIFT => "NONE",
      CLKIN_PERIOD => 20.000000,
      DESKEW_ADJUST => "6",
      DFS_FREQUENCY_MODE => "LOW",
      STARTUP_WAIT => FALSE,
      CLK_FEEDBACK => "1X",
      DLL_FREQUENCY_MODE => "LOW",
      CLKIN_DIVIDE_BY_2 => FALSE,
      PHASE_SHIFT => 0
    )
    port map (
      CLKIN => clk_div_DCM_SP_INST_CLKIN_BUF_287,
      CLKFB => clk_div_DCM_SP_INST_CLKFB_BUF_288,
      RST => RST_IN_IBUF_93,
      DSSEN => NLW_clk_div_DCM_SP_INST_DSSEN_UNCONNECTED,
      PSINCDEC => '0',
      PSEN => '0',
      PSCLK => clk_div_DCM_SP_INST_PSCLKINV_289,
      PSDONE => clk_div_DCM_SP_INST_PSDONE,
      LOCKED => LOCKED_OUT_OBUF_92,
      CLKFX180 => clk_div_DCM_SP_INST_CLKFX180,
      CLKFX => clk_div_CLKFX_BUF,
      CLKDV => clk_div_DCM_SP_INST_CLKDV,
      CLK2X180 => clk_div_DCM_SP_INST_CLK2X180,
      CLK2X => clk_div_DCM_SP_INST_CLK2X,
      CLK270 => clk_div_DCM_SP_INST_CLK270,
      CLK180 => clk_div_DCM_SP_INST_CLK180,
      CLK90 => clk_div_DCM_SP_INST_CLK90,
      CLK0 => clk_div_CLK0_BUF,
      STATUS(7) => clk_div_DCM_SP_INST_STATUS7,
      STATUS(6) => clk_div_DCM_SP_INST_STATUS6,
      STATUS(5) => clk_div_DCM_SP_INST_STATUS5,
      STATUS(4) => clk_div_DCM_SP_INST_STATUS4,
      STATUS(3) => clk_div_DCM_SP_INST_STATUS3,
      STATUS(2) => clk_div_DCM_SP_INST_STATUS2,
      STATUS(1) => clk_div_DCM_SP_INST_STATUS1,
      STATUS(0) => clk_div_DCM_SP_INST_STATUS0
    );
  clk_div_DCM_SP_INST_CLKFB_BUF : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLK0_OUT_OBUF_91,
      O => clk_div_DCM_SP_INST_CLKFB_BUF_288
    );
  clk_div_DCM_SP_INST_CLKIN_BUF : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IBUFG_OUT_OBUF_88,
      O => clk_div_DCM_SP_INST_CLKIN_BUF_287
    );
  clk_div_CLK0_BUFG_INST : X_BUFGMUX
    port map (
      I0 => clk_div_CLK0_BUF,
      I1 => GND,
      S => clk_div_CLK0_BUFG_INST_S_INVNOT,
      O => CLK0_OUT_OBUF_91
    );
  clk_div_CLK0_BUFG_INST_SINV : X_INV
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => clk_div_CLK0_BUFG_INST_S_INVNOT
    );
  Sw7_IFF_IMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => Sw7_INBUF,
      O => Sw7_IBUF_87
    );
  CLKIN_IN_IFF_IMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IN_INBUF,
      O => CLKIN_IBUFG_OUT_OBUF_88
    );
  RST_IN_IFF_IMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => RST_IN_INBUF,
      O => RST_IN_IBUF_93
    );
  input_buf_empty_fl_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => flagd_INBUF,
      O => input_buf_empty_fl_O
    );
  CLKIN_IBUFG_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IBUFG_OUT_OBUF_88,
      O => CLKIN_IBUFG_OUT_O
    );
  faddr_0_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => faddr_0_OUTPUT_OFF_O1INV_126,
      O => faddr_0_O
    );
  faddr_0_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => faddr_0_OUTPUT_OFF_O1INV_126
    );
  faddr_1_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => faddr_1_OUTPUT_OFF_O1INV_134,
      O => faddr_1_O
    );
  faddr_1_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => faddr_1_OUTPUT_OFF_O1INV_134
    );
  fdata_0_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_0_OUTPUT_OFF_O1INV_142,
      O => fdata_0_O
    );
  fdata_0_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_0_OUTPUT_OFF_O1INV_142
    );
  fdata_1_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_1_OUTPUT_OFF_O1INV_150,
      O => fdata_1_O
    );
  fdata_1_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_1_OUTPUT_OFF_O1INV_150
    );
  fdata_2_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_2_OUTPUT_OFF_O1INV_158,
      O => fdata_2_O
    );
  fdata_2_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_2_OUTPUT_OFF_O1INV_158
    );
  fdata_3_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_3_OUTPUT_OFF_O1INV_166,
      O => fdata_3_O
    );
  fdata_3_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_3_OUTPUT_OFF_O1INV_166
    );
  fdata_4_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_4_OUTPUT_OFF_O1INV_174,
      O => fdata_4_O
    );
  fdata_4_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_4_OUTPUT_OFF_O1INV_174
    );
  fdata_5_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_5_OUTPUT_OFF_O1INV_182,
      O => fdata_5_O
    );
  fdata_5_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_5_OUTPUT_OFF_O1INV_182
    );
  fdata_6_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_6_OUTPUT_OFF_O1INV_190,
      O => fdata_6_O
    );
  fdata_6_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_6_OUTPUT_OFF_O1INV_190
    );
  fdata_7_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_7_OUTPUT_OFF_O1INV_198,
      O => fdata_7_O
    );
  fdata_7_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_7_OUTPUT_OFF_O1INV_198
    );
  sloe_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => sloe_OUTPUT_OFF_O1INV_212,
      O => sloe_O
    );
  sloe_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => sloe_OUTPUT_OFF_O1INV_212
    );
  CLK0_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLK0_OUT_OBUF_91,
      O => CLK0_OUT_O
    );
  slrd_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => slrd_OUTPUT_OFF_O1INV_234,
      O => slrd_O
    );
  slrd_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => slrd_OUTPUT_OFF_O1INV_234
    );
  LOCKED_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => LOCKED_OUT_OBUF_92,
      O => LOCKED_OUT_O
    );
  Sw7_led_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => Sw7_led_OUTPUT_OFF_O1INV_256,
      O => Sw7_led_O
    );
  Sw7_led_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => Sw7_led_OUTPUT_OFF_O1INV_256
    );
  slwr_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => slwr_OUTPUT_OFF_O1INV_264,
      O => slwr_O
    );
  slwr_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => slwr_OUTPUT_OFF_O1INV_264
    );
  CLKFX_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKFX_OUT_OBUF_94,
      O => CLKFX_OUT_O
    );
  NlwBlock_fx2lp_slaveFIFO2b_streamIN_fpga_top_GND : X_ZERO
    port map (
      O => GND
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => GSR);
  NlwBlockTOC : X_TOC
    port map (O => GTS);

end Structure;

