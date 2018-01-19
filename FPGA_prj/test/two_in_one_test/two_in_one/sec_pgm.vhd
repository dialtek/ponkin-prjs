library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity sec_pgm is
    Port ( LED1 : out  STD_LOGIC;
			  BTN0 : in  STD_LOGIC;
			  BTN1 : in  STD_LOGIC
	 );
end sec_pgm;

architecture Beh of sec_pgm is

begin
	LED1<=BTN0 or BTN1;
end Beh;

