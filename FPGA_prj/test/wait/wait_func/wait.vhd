
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity waitX is
	port (
		LED0: out bit;
		clk_50M: in std_logic);
end waitX;

architecture Beh of waitX is

signal Led_val: bit := '0';
signal tmp: bit := '0';

begin
	process (clk_50M)
		begin
			if rising_edge(clk_50M) then
		LED_VAL <= not tmp after 100 ms;	
	end if;
end process;
		LED0 <= LED_VAL;
end Beh;

