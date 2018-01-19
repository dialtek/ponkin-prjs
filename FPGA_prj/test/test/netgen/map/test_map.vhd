--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.28xd
--  \   \         Application: netgen
--  /   /         Filename: test_map.vhd
-- /___/   /\     Timestamp: Fri Aug 02 13:10:25 2013
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -s 5 -pcf test.pcf -rpw 100 -tpw 0 -ar Structure -tm test -w -dir netgen/map -ofmt vhdl -sim test_map.ncd test_map.vhd 
-- Device	: 3s500efg320-5 (PRODUCTION 1.27 2012-07-09)
-- Input file	: test_map.ncd
-- Output file	: C:\Xilinx\test\test\netgen\map\test_map.vhd
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
    clock : in STD_LOGIC := 'X'; 
    LED : out STD_LOGIC 
  );
end test;

architecture Structure of test is
  signal clock_IBUF_7 : STD_LOGIC; 
  signal LED_O : STD_LOGIC; 
  signal clock_INBUF : STD_LOGIC; 
  signal LED_OUTPUT_OFF_O1INV_15 : STD_LOGIC; 
begin
  LED_OBUF : X_OBUF
    port map (
      I => LED_O,
      O => LED
    );
  clock_IBUF : X_BUF
    generic map(
      PATHPULSE => 555 ps
    )
    port map (
      I => clock,
      O => clock_INBUF
    );
  clock_IFF_IMUX : X_BUF
    generic map(
      PATHPULSE => 555 ps
    )
    port map (
      I => clock_INBUF,
      O => clock_IBUF_7
    );
  LED_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      PATHPULSE => 555 ps
    )
    port map (
      I => LED_OUTPUT_OFF_O1INV_15,
      O => LED_O
    );
  LED_OUTPUT_OFF_O1INV : X_BUF
    generic map(
      PATHPULSE => 555 ps
    )
    port map (
      I => '1',
      O => LED_OUTPUT_OFF_O1INV_15
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => GSR);
  NlwBlockTOC : X_TOC
    port map (O => GTS);

end Structure;

