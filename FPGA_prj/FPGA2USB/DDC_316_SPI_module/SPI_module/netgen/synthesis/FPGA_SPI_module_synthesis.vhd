--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.49d
--  \   \         Application: netgen
--  /   /         Filename: FPGA_SPI_module_synthesis.vhd
-- /___/   /\     Timestamp: Mon May 19 15:44:34 2014
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -ar Structure -tm FPGA_SPI_module -w -dir netgen/synthesis -ofmt vhdl -sim FPGA_SPI_module.ngc FPGA_SPI_module_synthesis.vhd 
-- Device	: xc3s500e-4-fg320
-- Input file	: FPGA_SPI_module.ngc
-- Output file	: D:\work\Projects\FPGA_prj\FPGA2USB\DDC_316_SPI_module\SPI_module\netgen\synthesis\FPGA_SPI_module_synthesis.vhd
-- # of Entities	: 1
-- Design Name	: FPGA_SPI_module
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
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
use UNISIM.VPKG.ALL;

entity FPGA_SPI_module is
  port (
    DCLK : out STD_LOGIC; 
    DIN : in STD_LOGIC := 'X'; 
    CLK_IN_40MEG : in STD_LOGIC := 'X'; 
    DOUT : out STD_LOGIC_VECTOR ( 3 downto 0 ) 
  );
end FPGA_SPI_module;

architecture Structure of FPGA_SPI_module is
  signal CLK_IN_40MEG_IBUF_1 : STD_LOGIC; 
  signal CLK_IN_40MEG_IBUF1 : STD_LOGIC; 
  signal SPI_DCLK_signal_4 : STD_LOGIC; 
begin
  SPI_DCLK_signal : FD
    port map (
      C => CLK_IN_40MEG_IBUF_1,
      D => CLK_IN_40MEG_IBUF1,
      Q => SPI_DCLK_signal_4
    );
  CLK_IN_40MEG_IBUF : IBUF
    port map (
      I => CLK_IN_40MEG,
      O => CLK_IN_40MEG_IBUF1
    );
  DCLK_OBUF : OBUF
    port map (
      I => SPI_DCLK_signal_4,
      O => DCLK
    );
  CLK_IN_40MEG_IBUF_BUFG : BUFG
    port map (
      I => CLK_IN_40MEG_IBUF1,
      O => CLK_IN_40MEG_IBUF_1
    );

end Structure;

