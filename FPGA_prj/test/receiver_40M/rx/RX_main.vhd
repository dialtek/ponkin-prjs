library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity RX_main is
port ( CLKIN_IN        : in    std_logic; 
       CLKFX_OUT       : out   std_logic; 
       CLKIN_IBUFG_OUT : out   std_logic; 
       CLK0_OUT        : out   std_logic);
end RX_main;

architecture Beh of RX_main is

component fx_conv is
   port ( CLKIN_IN        : in    std_logic; 
          CLKFX_OUT       : out   std_logic; 
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic
			 );
end component;

begin
	clk_div: fx_conv 
		port map	(CLKIN_IN=>CLKIN_IN,CLKFX_OUT=>CLKFX_OUT,
	   CLKIN_IBUFG_OUT=>CLKIN_IBUFG_OUT,CLK0_OUT=>CLK0_OUT);
end Beh;