
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity wiz_main is
port ( CLKIN_IN        : in    std_logic; 
          CLKDV_OUT       : out   std_logic; 
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic; 
          CLK180_OUT      : out   std_logic);

end wiz_main;

architecture Beh of wiz_main is

component wiz2 
port ( CLKIN_IN        : in    std_logic; 
          CLKDV_OUT       : out   std_logic; 
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic; 
          CLK180_OUT      : out   std_logic);
end component;

begin
	clk_divider: wiz2
		port map	(CLKIN_IN=>CLKIN_IN,CLKDV_OUT=>CLKDV_OUT,
	CLKIN_IBUFG_OUT=>CLKIN_IBUFG_OUT,CLK0_OUT=>CLK0_OUT,
	CLK180_OUT=>CLK180_OUT);
end Beh;

