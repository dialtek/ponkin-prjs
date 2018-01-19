library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VComponents.all;

-- DCM: Digital Clock Manager Circuit

entity DCM_test is
	port ( --Gclk_50MHz: in std_logic;
	       Gclk_div_2: out std_logic;
			 DCM_CLKFB: inout std_logic; -- feedback 4 DCM
			 DCM_CLKIN: in std_logic;
			 DCM_CLK180: out std_logic
	     );
end DCM_test;

architecture Beh of DCM_test is

--signal div_clk: std_logic;
--signal main_clk_50M: std_logic;
--signal clk_fb: std_logic;
--signal clk_180: std_logic;

begin

DCM_SP_inst : DCM_SP
   generic map (
      CLKDV_DIVIDE => 2.0, --  Divide by: 1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5
                           --     7.0,7.5,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0 or 16.0
      CLKFX_DIVIDE => 1,   --  Can be any interger from 1 to 32
      CLKFX_MULTIPLY => 4, --  Can be any integer from 1 to 32
      CLKIN_DIVIDE_BY_2 => FALSE, --  TRUE/FALSE to enable CLKIN divide by two feature
      CLKIN_PERIOD => 20000.0, --  Specify period of input clock
      CLKOUT_PHASE_SHIFT => "NONE", --  Specify phase shift of "NONE", "FIXED" or "VARIABLE" 
      CLK_FEEDBACK => "NONE",         --  Specify clock feedback of "NONE", "1X" or "2X" 
      DESKEW_ADJUST => "SYSTEM_SYNCHRONOUS", -- "SOURCE_SYNCHRONOUS", "SYSTEM_SYNCHRONOUS" or
                                             --     an integer from 0 to 15
      DLL_FREQUENCY_MODE => "LOW",     -- "HIGH" or "LOW" frequency mode for DLL
      DUTY_CYCLE_CORRECTION => TRUE, --  Duty cycle correction, TRUE or FALSE
      PHASE_SHIFT => 0,        --  Amount of fixed phase shift from -255 to 255
      STARTUP_WAIT => FALSE) --  Delay configuration DONE until DCM_SP LOCK, TRUE/FALSE
		
   port map (
--      CLK0 => CLK0,     -- 0 degree DCM CLK ouptput
      CLK180 => DCM_CLK180, -- 180 degree DCM CLK output
--      CLK270 => CLK270, -- 270 degree DCM CLK output
--      CLK2X => CLK2X,   -- 2X DCM CLK output
--      CLK2X180 => CLK2X180, -- 2X, 180 degree DCM CLK out
--      CLK90 => CLK90,   -- 90 degree DCM CLK output
      CLKDV => Gclk_div_2,   -- Divided DCM CLK out (CLKDV_DIVIDE)
--      CLKFX => CLKFX,   -- DCM CLK synthesis out (M/D)
--      CLKFX180 => CLKFX180, -- 180 degree CLK synthesis out
--      LOCKED => LOCKED, -- DCM LOCK status output
--      PSDONE => PSDONE, -- Dynamic phase adjust done output
--      STATUS => STATUS, -- 8-bit DCM status bits output
		CLKFB => DCM_CLKFB,   -- DCM clock feedback
      CLKIN => DCM_CLKIN   -- Clock input (from IBUFG, BUFG or DCM)
--      PSCLK => PSCLK,   -- Dynamic phase adjust clock input
--      PSEN => PSEN,     -- Dynamic phase adjust enable input
--      PSINCDEC => PSINCDEC, -- Dynamic phase adjust increment/decrement
--      RST => RST        -- DCM asynchronous reset input
   
--		Gclk_50MHz: in std_logic;
--	       Gclk_div_2: out std_logic;
--			 DCM_CLKFB: in std_logic; -- feedback 4 DCM
--			 DCM_CLKIN: in std_logic;
--			 DCM_CLK180: out std_logic
--
--
-- div_clk <= Gclk_div_2;
-- main_clk_50M <= Gclk_50MHz; 

-- clk_180 <= DCM_CLK180
--	
	);
	
--clk_fb <= DCM_CLKIN ;
--DCM_CLKFB <= clk_fb ;

end Beh;

   