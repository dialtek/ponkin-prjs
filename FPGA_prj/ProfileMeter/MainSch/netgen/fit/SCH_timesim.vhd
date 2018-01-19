--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.49d
--  \   \         Application: netgen
--  /   /         Filename: SCH_timesim.vhd
-- /___/   /\     Timestamp: Wed Oct 07 18:19:04 2015
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -rpw 100 -ar Structure -tm SCH -w -dir netgen/fit -ofmt vhdl -sim SCH.nga SCH_timesim.vhd 
-- Device	: XC9572XL-5-VQ44 (Speed File: Version 3.0)
-- Input file	: SCH.nga
-- Output file	: D:\work\Projects\FPGA_prj\ProfileMeter\MainSch\netgen\fit\SCH_timesim.vhd
-- # of Entities	: 1
-- Design Name	: SCH.nga
-- Xilinx	: C:\Xilinx\14.4\ISE_DS\ISE\
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

entity SCH is
  port (
    LED : out STD_LOGIC 
  );
end SCH;

architecture Structure of SCH is
  signal LED_OBUF_1 : STD_LOGIC; 
  signal LED_OBUF_Q_2 : STD_LOGIC; 
  signal LED_OBUF_D_3 : STD_LOGIC; 
  signal LED_OBUF_D1_4 : STD_LOGIC; 
  signal LED_OBUF_D2_5 : STD_LOGIC; 
  signal NlwBufferSignal_LED_OBUF_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_LED_OBUF_D_IN1 : STD_LOGIC; 
begin
  LED_2 : X_BUF
    port map (
      I => LED_OBUF_1,
      O => LED
    );
  LED_OBUF : X_BUF
    port map (
      I => LED_OBUF_Q_2,
      O => LED_OBUF_1
    );
  LED_OBUF_Q : X_BUF
    port map (
      I => LED_OBUF_D_3,
      O => LED_OBUF_Q_2
    );
  LED_OBUF_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_LED_OBUF_D_IN0,
      I1 => NlwBufferSignal_LED_OBUF_D_IN1,
      O => LED_OBUF_D_3
    );
  LED_OBUF_D1 : X_ZERO
    port map (
      O => LED_OBUF_D1_4
    );
  LED_OBUF_D2 : X_ONE
    port map (
      O => LED_OBUF_D2_5
    );
  NlwBufferBlock_LED_OBUF_D_IN0 : X_BUF
    port map (
      I => LED_OBUF_D1_4,
      O => NlwBufferSignal_LED_OBUF_D_IN0
    );
  NlwBufferBlock_LED_OBUF_D_IN1 : X_BUF
    port map (
      I => LED_OBUF_D2_5,
      O => NlwBufferSignal_LED_OBUF_D_IN1
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => PRLD);

end Structure;

