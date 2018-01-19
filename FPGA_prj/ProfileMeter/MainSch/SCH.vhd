--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.4
--  \   \         Application : sch2hdl
--  /   /         Filename : SCH.vhf
-- /___/   /\     Timestamp : 10/08/2015 17:42:03
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500xl -flat -suppress -vhdl D:/work/Projects/FPGA_prj/ProfileMeter/MainSch/SCH.vhf -w D:/work/Projects/FPGA_prj/ProfileMeter/MainSch/SCH.sch
--Design Name: SCH
--Device: xc9500xl
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity FD_MXILINX_SCH is
   generic( INIT : bit :=  '0');
   port ( C : in    std_logic; 
          D : in    std_logic; 
          Q : out   std_logic);
end FD_MXILINX_SCH;

architecture BEHAVIORAL of FD_MXILINX_SCH is
   attribute BOX_TYPE   : string ;
   signal XLXN_4 : std_logic;
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component FDCP
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             PRE : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDCP : component is "BLACK_BOX";
   
begin
   I_36_43 : GND
      port map (G=>XLXN_4);
   
   U0 : FDCP
   generic map( INIT => INIT)
      port map (C=>C,
                CLR=>XLXN_4,
                D=>D,
                PRE=>XLXN_4,
                Q=>Q);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity SCH is
   port ( IN_F  : in    std_logic; 
          OUT_F : out   std_logic);
end SCH;

architecture BEHAVIORAL of SCH is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal XLXN_14     : std_logic;
   signal OUT_F_DUMMY : std_logic;
   component FD_MXILINX_SCH
      generic( INIT : bit :=  '0');
      port ( C : in    std_logic; 
             D : in    std_logic; 
             Q : out   std_logic);
   end component;
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_26 : label is "XLXI_26_0";
begin
   OUT_F <= OUT_F_DUMMY;
   XLXI_26 : FD_MXILINX_SCH
      port map (C=>IN_F,
                D=>XLXN_14,
                Q=>OUT_F_DUMMY);
   
   XLXI_27 : INV
      port map (I=>OUT_F_DUMMY,
                O=>XLXN_14);
   
end BEHAVIORAL;


