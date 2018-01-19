library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity test is
port(
CLK_50MHz,BTN3: in STD_LOGIC;
LED1,SEG_COM_ANODE1,SEG_COM_ANODE2,
SEG_COM_ANODE3,SEG_COM_ANODE4 :out STD_LOGIC;
SEG_CA,SEG_CB,SEG_CC,SEG_CD,
SEG_CE,SEG_CF,SEG_CG,SEG_DP :out STD_LOGIC );
end test;

architecture beh of test is
signal sel: unsigned(2 downto 0) := "000";
	--signal SEG_CA: std_logic;  	
begin
process(CLK_50MHz)
 begin
   if rising_edge(CLK_50MHz) then
  SEG_COM_ANODE1<='0';
  SEG_COM_ANODE2<='1';
  SEG_COM_ANODE3<='1';
  SEG_COM_ANODE4<='1';
	if (BTN3 = '1') then
		
		LED1<= '1';
		
		--sel <= (sel+1);

	end if;
  end if;
 end process;
end Beh;

--	case sel is
--		when "001" => SEG_CA<='0';
--						SEG_CB<='1';
--						SEG_CC<='1';
--						SEG_CD<='0';
--						SEG_CE<='0';
--						SEG_CF<='0';
--						SEG_CG<='0';
						  
--		when "010" => SEG_CA<='1';
--						SEG_CB<='1';
--						SEG_CC<='0';
--						SEG_CD<='1';
--						SEG_CE<='1';
--						SEG_CF<='0';
--						SEG_CG<='1';
						  					  
--		when "011" => SEG_CA<='1';
--						SEG_CB<='1';
--						SEG_CC<='1';
--						SEG_CD<='1';
--						SEG_CE<='0';
--						SEG_CF<='0';
--						SEG_CG<='1';
--		
--		when "100" => SEG_CA<='0';
--						SEG_CB<='1';
--						SEG_CC<='1';
--						SEG_CD<='0';
--						SEG_CE<='0';
--						SEG_CF<='1';
--						SEG_CG<='1';
--		
--		when "101" => SEG_CA<='1';
--						SEG_CB<='0';
--						SEG_CC<='1';
--						SEG_CD<='1';
--						SEG_CE<='0';
--						SEG_CF<='1';
--						SEG_CG<='1';
--		
--		when "110" => SEG_CA<='1';
--						SEG_CB<='0';
--						SEG_CC<='1';
--						SEG_CD<='1';
--						SEG_CE<='1';
--						SEG_CF<='1';
--						SEG_CG<='1';
--		
--		when "111" => SEG_CA<='1';
--						SEG_CB<='1';
--						SEG_CC<='1';
--						SEG_CD<='0';
--						SEG_CE<='0';
--						SEG_CF<='0';
--						SEG_CG<='0';
		
--		when others => 
--						LED1<='0';
--						SEG_CA<='0';
						--SEG_CB<='0';
--						SEG_CC<='0';
--						SEG_CD<='0';
--						SEG_CE<='0';
--						SEG_CF<='0';
--						SEG_CG<='0';
--	end case;	


