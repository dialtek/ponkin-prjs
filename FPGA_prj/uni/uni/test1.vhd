library IEEE;
use IEEE.STD_LOGIC_1164.ALL;      
use IEEE.STD_LOGIC_ARITH.ALL;     
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity test1 is
    Port ( A : in  STD_LOGIC;
			  B : in STD_LOGIC;
			  C : out STD_LOGIC;
			 clk: in STD_LOGIC
 	 );
end test1;

architecture Behave of test1 is

signal wire: std_logic;

	begin
		process(clk) 
			begin
				if rising_edge(clk) then	
				 
					wire <= NOT (A AND B);
					
				end if;
		
	end process;
	
	C <= wire;
	
end Behave;

