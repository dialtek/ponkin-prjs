
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity first_pgm is
    Port ( LED0,LED1 : out  STD_LOGIC;
			  BTN3,BTN1 : in  STD_LOGIC;
			  BTN2,BTN0 : in  STD_LOGIC
	 );
end first_pgm;

architecture Beh of first_pgm is

	component sec_pgm 
	port (LED1: out std_logic; BTN1,BTN0: in  STD_LOGIC);
   end component;
	
begin
	two_in_one: sec_pgm 
	port map (LED1 => LED1, BTN1 => BTN1,
				 BTN0=>BTN0);
	
	LED0<=BTN3 or BTN2;

end Beh;

