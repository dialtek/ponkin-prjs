library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Freq_conv_MAIN is
port ( CLKIN_IN        : in    std_logic; 
          CLKFX_OUT       : out   std_logic; 
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic);
end Freq_conv_MAIN;

architecture Beh of Freq_conv_MAIN is

component fx_conv is
   port ( CLKIN_IN        : in    std_logic; 
          CLKFX_OUT       : out   std_logic; 
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic);
end component;

begin
	clk_divider: fx_conv 
		port map	(CLKIN_IN=>CLKIN_IN,CLKFX_OUT=>CLKFX_OUT,
	CLKIN_IBUFG_OUT=>CLKIN_IBUFG_OUT,CLK0_OUT=>CLK0_OUT);
end Beh;

