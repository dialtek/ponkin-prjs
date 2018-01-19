library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity test is
	port(		
		 CLK_50MHz: in std_logic;
		 LED7: out bit
		 );	
end test;

architecture Beh of test is
	
	signal led_on: bit;
--2FAF080 - 1 сек.	

begin
	process(CLK_50MHz)
	variable count: std_logic_vector(27 downto 0):= x"0000000";
	constant one_sec: std_logic_vector(27 downto 0):= x"2FAF080";
		begin
		if rising_edge(CLK_50MHz) then 
		 if (count<one_sec) then
		   count:=count+1;
		 elsif (count=x"2FAF080") then 
		   count:= x"0000000";		 
			led_on <= NOT led_on;
    end if;
	end if;
 end process;
 LED7<=led_on;
end Beh;

