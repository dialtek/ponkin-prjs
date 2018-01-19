--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.28xd
--  \   \         Application: netgen
--  /   /         Filename: fx2lp_slaveFIFO2b_streamIN_fpga_top_timesim.vhd
-- /___/   /\     Timestamp: Wed Nov 20 15:25:29 2013
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -s 4 -pcf fx2lp_slaveFIFO2b_streamIN_fpga_top.pcf -rpw 100 -tpw 0 -ar Structure -tm fx2lp_slaveFIFO2b_streamIN_fpga_top -insert_pp_buffers true -w -dir netgen/par -ofmt vhdl -sim fx2lp_slaveFIFO2b_streamIN_fpga_top.ncd fx2lp_slaveFIFO2b_streamIN_fpga_top_timesim.vhd 
-- Device	: 3s500efg320-4 (PRODUCTION 1.27 2012-07-09)
-- Input file	: fx2lp_slaveFIFO2b_streamIN_fpga_top.ncd
-- Output file	: C:\work\Projects\FPGA_prj\FPGA2USB\FPGA2USB\netgen\par\fx2lp_slaveFIFO2b_streamIN_fpga_top_timesim.vhd
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
    RST_IN : in STD_LOGIC := 'X'; 
    flagd : in STD_LOGIC := 'X'; 
    CLKIN_IN : in STD_LOGIC := 'X'; 
    fdata : inout STD_LOGIC_VECTOR ( 7 downto 0 ); 
    faddr : out STD_LOGIC_VECTOR ( 1 downto 0 ) 
  );
end fx2lp_slaveFIFO2b_streamIN_fpga_top;

architecture Structure of fx2lp_slaveFIFO2b_streamIN_fpga_top is
  signal CLKIN_IBUFG_OUT_OBUF_81 : STD_LOGIC; 
  signal CLK0_OUT_OBUF_84 : STD_LOGIC; 
  signal LOCKED_OUT_OBUF_85 : STD_LOGIC; 
  signal RST_IN_IBUF_86 : STD_LOGIC; 
  signal CLKFX_OUT_OBUF_87 : STD_LOGIC; 
  signal clk_div_CLKFX_BUF : STD_LOGIC; 
  signal clk_div_CLK0_BUF : STD_LOGIC; 
  signal input_buf_empty_fl_O : STD_LOGIC; 
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
  signal slwr_O : STD_LOGIC; 
  signal CLKFX_OUT_O : STD_LOGIC; 
  signal clk_div_CLKFX_BUFG_INST_S_INVNOT : STD_LOGIC; 
  signal clk_div_CLKFX_BUFG_INST_I0_INV : STD_LOGIC; 
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
  signal clk_div_DCM_SP_INST_PSCLKINV_268 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLKFB_BUF_267 : STD_LOGIC; 
  signal clk_div_DCM_SP_INST_CLKIN_BUF_266 : STD_LOGIC; 
  signal clk_div_CLK0_BUFG_INST_S_INVNOT : STD_LOGIC; 
  signal clk_div_CLK0_BUFG_INST_I0_INV : STD_LOGIC; 
  signal faddr_0_OUTPUT_OFF_O1INV_113 : STD_LOGIC; 
  signal faddr_1_OUTPUT_OFF_O1INV_121 : STD_LOGIC; 
  signal fdata_0_OUTPUT_OFF_O1INV_129 : STD_LOGIC; 
  signal fdata_1_OUTPUT_OFF_O1INV_137 : STD_LOGIC; 
  signal fdata_2_OUTPUT_OFF_O1INV_145 : STD_LOGIC; 
  signal fdata_3_OUTPUT_OFF_O1INV_153 : STD_LOGIC; 
  signal fdata_4_OUTPUT_OFF_O1INV_161 : STD_LOGIC; 
  signal fdata_5_OUTPUT_OFF_O1INV_169 : STD_LOGIC; 
  signal fdata_6_OUTPUT_OFF_O1INV_177 : STD_LOGIC; 
  signal fdata_7_OUTPUT_OFF_O1INV_185 : STD_LOGIC; 
  signal sloe_OUTPUT_OFF_O1INV_199 : STD_LOGIC; 
  signal slrd_OUTPUT_OFF_O1INV_221 : STD_LOGIC; 
  signal slwr_OUTPUT_OFF_O1INV_243 : STD_LOGIC; 
  signal NlwBufferSignal_clk_div_DCM_SP_INST_RST : STD_LOGIC; 
  signal GND : STD_LOGIC; 
  signal NLW_clk_div_DCM_SP_INST_DSSEN_UNCONNECTED : STD_LOGIC; 
begin
  input_buf_empty_fl_OBUF : X_OBUF
    generic map(
      LOC => "PAD181"
    )
    port map (
      I => input_buf_empty_fl_O,
      O => input_buf_empty_fl
    );
  CLKIN_IBUFG_OUT_OBUF : X_OBUF
    generic map(
      LOC => "PAD120"
    )
    port map (
      I => CLKIN_IBUFG_OUT_O,
      O => CLKIN_IBUFG_OUT
    );
  faddr_0_OBUF : X_OBUF
    generic map(
      LOC => "PAD124"
    )
    port map (
      I => faddr_0_O,
      O => faddr(0)
    );
  faddr_1_OBUF : X_OBUF
    generic map(
      LOC => "PAD132"
    )
    port map (
      I => faddr_1_O,
      O => faddr(1)
    );
  fdata_0_OBUF : X_OBUF
    generic map(
      LOC => "PAD123"
    )
    port map (
      I => fdata_0_O,
      O => fdata(0)
    );
  fdata_1_OBUF : X_OBUF
    generic map(
      LOC => "PAD127"
    )
    port map (
      I => fdata_1_O,
      O => fdata(1)
    );
  fdata_2_OBUF : X_OBUF
    generic map(
      LOC => "PAD128"
    )
    port map (
      I => fdata_2_O,
      O => fdata(2)
    );
  fdata_3_OBUF : X_OBUF
    generic map(
      LOC => "PAD131"
    )
    port map (
      I => fdata_3_O,
      O => fdata(3)
    );
  fdata_4_OBUF : X_OBUF
    generic map(
      LOC => "PAD135"
    )
    port map (
      I => fdata_4_O,
      O => fdata(4)
    );
  fdata_5_OBUF : X_OBUF
    generic map(
      LOC => "PAD134"
    )
    port map (
      I => fdata_5_O,
      O => fdata(5)
    );
  fdata_6_OBUF : X_OBUF
    generic map(
      LOC => "PAD142"
    )
    port map (
      I => fdata_6_O,
      O => fdata(6)
    );
  fdata_7_OBUF : X_OBUF
    generic map(
      LOC => "PAD143"
    )
    port map (
      I => fdata_7_O,
      O => fdata(7)
    );
  clk_div_CLKIN_IBUFG_INST : X_BUF
    generic map(
      LOC => "IPAD29",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IN,
      O => CLKIN_IN_INBUF
    );
  sloe_OBUF : X_OBUF
    generic map(
      LOC => "PAD121"
    )
    port map (
      I => sloe_O,
      O => sloe
    );
  flagd_IBUF : X_BUF
    generic map(
      LOC => "PAD118",
      PATHPULSE => 638 ps
    )
    port map (
      I => flagd,
      O => flagd_INBUF
    );
  CLK0_OUT_OBUF : X_OBUF
    generic map(
      LOC => "PAD115"
    )
    port map (
      I => CLK0_OUT_O,
      O => CLK0_OUT
    );
  slrd_OBUF : X_OBUF
    generic map(
      LOC => "PAD150"
    )
    port map (
      I => slrd_O,
      O => slrd
    );
  LOCKED_OUT_OBUF : X_OBUF
    generic map(
      LOC => "PAD25"
    )
    port map (
      I => LOCKED_OUT_O,
      O => LOCKED_OUT
    );
  RST_IN_IBUF : X_BUF
    generic map(
      LOC => "IPAD98",
      PATHPULSE => 638 ps
    )
    port map (
      I => RST_IN,
      O => RST_IN_INBUF
    );
  slwr_OBUF : X_OBUF
    generic map(
      LOC => "PAD146"
    )
    port map (
      I => slwr_O,
      O => slwr
    );
  CLKFX_OUT_OBUF : X_OBUF
    generic map(
      LOC => "PAD122"
    )
    port map (
      I => CLKFX_OUT_O,
      O => CLKFX_OUT
    );
  clk_div_CLKFX_BUFG_INST : X_BUFGMUX
    generic map(
      LOC => "BUFGMUX_X1Y10"
    )
    port map (
      I0 => clk_div_CLKFX_BUFG_INST_I0_INV,
      I1 => GND,
      S => clk_div_CLKFX_BUFG_INST_S_INVNOT,
      O => CLKFX_OUT_OBUF_87
    );
  clk_div_CLKFX_BUFG_INST_SINV : X_INV
    generic map(
      LOC => "BUFGMUX_X1Y10",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => clk_div_CLKFX_BUFG_INST_S_INVNOT
    );
  clk_div_CLKFX_BUFG_INST_I0_USED : X_BUF
    generic map(
      LOC => "BUFGMUX_X1Y10",
      PATHPULSE => 638 ps
    )
    port map (
      I => clk_div_CLKFX_BUF,
      O => clk_div_CLKFX_BUFG_INST_I0_INV
    );
  clk_div_DCM_SP_INST_PSCLKINV : X_BUF
    generic map(
      LOC => "DCM_X0Y1",
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => clk_div_DCM_SP_INST_PSCLKINV_268
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
      PHASE_SHIFT => 0,
      LOC => "DCM_X0Y1"
    )
    port map (
      CLKIN => clk_div_DCM_SP_INST_CLKIN_BUF_266,
      CLKFB => clk_div_DCM_SP_INST_CLKFB_BUF_267,
      RST => NlwBufferSignal_clk_div_DCM_SP_INST_RST,
      DSSEN => NLW_clk_div_DCM_SP_INST_DSSEN_UNCONNECTED,
      PSINCDEC => '0',
      PSEN => '0',
      PSCLK => clk_div_DCM_SP_INST_PSCLKINV_268,
      PSDONE => clk_div_DCM_SP_INST_PSDONE,
      LOCKED => LOCKED_OUT_OBUF_85,
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
      LOC => "DCM_X0Y1",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLK0_OUT_OBUF_84,
      O => clk_div_DCM_SP_INST_CLKFB_BUF_267
    );
  clk_div_DCM_SP_INST_CLKIN_BUF : X_BUF
    generic map(
      LOC => "DCM_X0Y1",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IBUFG_OUT_OBUF_81,
      O => clk_div_DCM_SP_INST_CLKIN_BUF_266
    );
  clk_div_CLK0_BUFG_INST : X_BUFGMUX
    generic map(
      LOC => "BUFGMUX_X2Y11"
    )
    port map (
      I0 => clk_div_CLK0_BUFG_INST_I0_INV,
      I1 => GND,
      S => clk_div_CLK0_BUFG_INST_S_INVNOT,
      O => CLK0_OUT_OBUF_84
    );
  clk_div_CLK0_BUFG_INST_SINV : X_INV
    generic map(
      LOC => "BUFGMUX_X2Y11",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => clk_div_CLK0_BUFG_INST_S_INVNOT
    );
  clk_div_CLK0_BUFG_INST_I0_USED : X_BUF
    generic map(
      LOC => "BUFGMUX_X2Y11",
      PATHPULSE => 638 ps
    )
    port map (
      I => clk_div_CLK0_BUF,
      O => clk_div_CLK0_BUFG_INST_I0_INV
    );
  CLKIN_IN_IFF_IMUX : X_BUF
    generic map(
      LOC => "IPAD29",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IN_INBUF,
      O => CLKIN_IBUFG_OUT_OBUF_81
    );
  RST_IN_IFF_IMUX : X_BUF
    generic map(
      LOC => "IPAD98",
      PATHPULSE => 638 ps
    )
    port map (
      I => RST_IN_INBUF,
      O => RST_IN_IBUF_86
    );
  input_buf_empty_fl_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD181",
      PATHPULSE => 638 ps
    )
    port map (
      I => flagd_INBUF,
      O => input_buf_empty_fl_O
    );
  CLKIN_IBUFG_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD120",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKIN_IBUFG_OUT_OBUF_81,
      O => CLKIN_IBUFG_OUT_O
    );
  faddr_0_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD124",
      PATHPULSE => 638 ps
    )
    port map (
      I => faddr_0_OUTPUT_OFF_O1INV_113,
      O => faddr_0_O
    );
  faddr_0_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD124",
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => faddr_0_OUTPUT_OFF_O1INV_113
    );
  faddr_1_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD132",
      PATHPULSE => 638 ps
    )
    port map (
      I => faddr_1_OUTPUT_OFF_O1INV_121,
      O => faddr_1_O
    );
  faddr_1_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD132",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => faddr_1_OUTPUT_OFF_O1INV_121
    );
  fdata_0_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD123",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_0_OUTPUT_OFF_O1INV_129,
      O => fdata_0_O
    );
  fdata_0_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD123",
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_0_OUTPUT_OFF_O1INV_129
    );
  fdata_1_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD127",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_1_OUTPUT_OFF_O1INV_137,
      O => fdata_1_O
    );
  fdata_1_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD127",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_1_OUTPUT_OFF_O1INV_137
    );
  fdata_2_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD128",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_2_OUTPUT_OFF_O1INV_145,
      O => fdata_2_O
    );
  fdata_2_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD128",
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_2_OUTPUT_OFF_O1INV_145
    );
  fdata_3_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD131",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_3_OUTPUT_OFF_O1INV_153,
      O => fdata_3_O
    );
  fdata_3_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD131",
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => fdata_3_OUTPUT_OFF_O1INV_153
    );
  fdata_4_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD135",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_4_OUTPUT_OFF_O1INV_161,
      O => fdata_4_O
    );
  fdata_4_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD135",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_4_OUTPUT_OFF_O1INV_161
    );
  fdata_5_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD134",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_5_OUTPUT_OFF_O1INV_169,
      O => fdata_5_O
    );
  fdata_5_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD134",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_5_OUTPUT_OFF_O1INV_169
    );
  fdata_6_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD142",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_6_OUTPUT_OFF_O1INV_177,
      O => fdata_6_O
    );
  fdata_6_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD142",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_6_OUTPUT_OFF_O1INV_177
    );
  fdata_7_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD143",
      PATHPULSE => 638 ps
    )
    port map (
      I => fdata_7_OUTPUT_OFF_O1INV_185,
      O => fdata_7_O
    );
  fdata_7_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD143",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => fdata_7_OUTPUT_OFF_O1INV_185
    );
  sloe_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD121",
      PATHPULSE => 638 ps
    )
    port map (
      I => sloe_OUTPUT_OFF_O1INV_199,
      O => sloe_O
    );
  sloe_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD121",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => sloe_OUTPUT_OFF_O1INV_199
    );
  CLK0_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD115",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLK0_OUT_OBUF_84,
      O => CLK0_OUT_O
    );
  slrd_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD150",
      PATHPULSE => 638 ps
    )
    port map (
      I => slrd_OUTPUT_OFF_O1INV_221,
      O => slrd_O
    );
  slrd_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD150",
      PATHPULSE => 638 ps
    )
    port map (
      I => '1',
      O => slrd_OUTPUT_OFF_O1INV_221
    );
  LOCKED_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD25",
      PATHPULSE => 638 ps
    )
    port map (
      I => LOCKED_OUT_OBUF_85,
      O => LOCKED_OUT_O
    );
  slwr_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD146",
      PATHPULSE => 638 ps
    )
    port map (
      I => slwr_OUTPUT_OFF_O1INV_243,
      O => slwr_O
    );
  slwr_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      LOC => "PAD146",
      PATHPULSE => 638 ps
    )
    port map (
      I => '0',
      O => slwr_OUTPUT_OFF_O1INV_243
    );
  CLKFX_OUT_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD122",
      PATHPULSE => 638 ps
    )
    port map (
      I => CLKFX_OUT_OBUF_87,
      O => CLKFX_OUT_O
    );
  NlwBufferBlock_clk_div_DCM_SP_INST_RST : X_BUF
    generic map(
      PATHPULSE => 638 ps
    )
    port map (
      I => RST_IN_IBUF_86,
      O => NlwBufferSignal_clk_div_DCM_SP_INST_RST
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

