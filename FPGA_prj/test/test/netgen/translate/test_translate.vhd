--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.28xd
--  \   \         Application: netgen
--  /   /         Filename: test_translate.vhd
-- /___/   /\     Timestamp: Sat Aug 03 15:20:58 2013
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -rpw 100 -tpw 0 -ar Structure -tm test -w -dir netgen/translate -ofmt vhdl -sim test.ngd test_translate.vhd 
-- Device	: 3s500efg320-5
-- Input file	: test.ngd
-- Output file	: C:\Xilinx\test\test\netgen\translate\test_translate.vhd
-- # of Entities	: 1
-- Design Name	: test
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

entity test is
  port (
    LED0 : out STD_LOGIC; 
    LED1 : out STD_LOGIC; 
    BTN2 : in STD_LOGIC := 'X'; 
    BTN3 : in STD_LOGIC := 'X' 
  );
end test;

architecture Structure of test is
  signal BTN2_IBUF_1 : STD_LOGIC; 
  signal BTN3_IBUF_3 : STD_LOGIC; 
  signal LED0_OBUF_5 : STD_LOGIC; 
  signal LED1_OBUF_7 : STD_LOGIC; 
begin
  LED11 : X_LUT2
    generic map(
      INIT => X"8"
    )
    port map (
      ADR0 => BTN2_IBUF_1,
      ADR1 => BTN3_IBUF_3,
      O => LED1_OBUF_7
    );
  LED01 : X_LUT2
    generic map(
      INIT => X"E"
    )
    port map (
      ADR0 => BTN2_IBUF_1,
      ADR1 => BTN3_IBUF_3,
      O => LED0_OBUF_5
    );
  BTN2_IBUF : X_BUF
    port map (
      I => BTN2,
      O => BTN2_IBUF_1
    );
  BTN3_IBUF : X_BUF
    port map (
      I => BTN3,
      O => BTN3_IBUF_3
    );
  LED0_OBUF : X_OBUF
    port map (
      I => LED0_OBUF_5,
      O => LED0
    );
  LED1_OBUF : X_OBUF
    port map (
      I => LED1_OBUF_7,
      O => LED1
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => GSR);
  NlwBlockTOC : X_TOC
    port map (O => GTS);

end Structure;

