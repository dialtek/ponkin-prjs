library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity rs232_test is
	port( --pin_rx: in std_logic;
			pin_tx,LED0: out bit;
			clk_50M: in std_logic
			--BTN3: in std_logic
	);
end rs232_test;

architecture Beh of rs232_test is
	signal led_on: bit;
begin
process(clk_50M)
	variable count: std_logic_vector(27 downto 0):= x"0000000";
	constant one_sec: std_logic_vector(27 downto 0):= x"2FAF080";
		begin
		if rising_edge(clk_50M) then 
		 if (count<one_sec) then
		   count:=count+1;
		 elsif (count=x"2FAF080") then 
		   count:= x"0000000";		 
			led_on <= NOT led_on;
    end if;
	end if;
 end process;
 LED0<=led_on;
 pin_tx<=led_on;
end Beh;

