library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity segm_disp is	port (
	BTN3,BTN2,BTN1,BTN0: in std_logic;
	LED7,LED1: out std_logic;
	CLK_50MHz: in std_logic;
	SEG_COM_ANODE1,SEG_COM_ANODE2,
	SEG_COM_ANODE3,SEG_COM_ANODE4: out std_logic;
	SEG_CA,SEG_CB,SEG_CC,
	SEG_CG,SEG_CE,SEG_CD,SEG_CF: out std_logic
	);
end segm_disp;

architecture Beh of segm_disp is
component test
Port (CLK_50MHz: in std_logic;
	      LED7: out std_logic
	        );
end component;

 begin
 
two_in_one: test
port map(LED7 => LED7, CLK_50MHz => CLK_50MHz);
 
  	process (CLK_50MHz)
		begin
			if rising_edge(CLK_50MHz) then 
				if (BTN3 = '1') then
				   SEG_COM_ANODE1<='0';
					SEG_COM_ANODE2<='1';
					SEG_COM_ANODE3<='1';
					SEG_COM_ANODE4<='1';					
					LED1<='1';
					SEG_CA<='1';
					SEG_CB<='0';
					SEG_CC<='0';
					SEG_CD<='1';
					SEG_CE<='1';
					SEG_CF<='1';
				   SEG_CG<='1';
					
				elsif (BTN2 = '1') then
				   SEG_COM_ANODE1<='1';
					SEG_COM_ANODE2<='0';
					SEG_COM_ANODE3<='1';
					SEG_COM_ANODE4<='1';
					LED1<='1';
					SEG_CA<='0';
					SEG_CB<='0';
					SEG_CC<='1';
					SEG_CD<='0';
					SEG_CE<='0';
					SEG_CF<='1';
					SEG_CG<='0';
		 
				elsif (BTN1 = '1') then
				   SEG_COM_ANODE1<='1';
					SEG_COM_ANODE2<='1';
					SEG_COM_ANODE3<='0';
					SEG_COM_ANODE4<='1';					
					LED1<='1';
					SEG_CA<='0';
					SEG_CB<='0';
					SEG_CC<='0';
					SEG_CD<='0';
					SEG_CE<='1';
					SEG_CF<='1';
					SEG_CG<='0';
	 
				elsif (BTN0 = '1') then
				   SEG_COM_ANODE1<='1';
					SEG_COM_ANODE2<='1';
					SEG_COM_ANODE3<='1';
					SEG_COM_ANODE4<='0';					
					LED1<='1';
					SEG_CA<='1';
					SEG_CB<='0';
					SEG_CC<='0';
					SEG_CD<='1';
					SEG_CE<='1';
					SEG_CF<='0';
					SEG_CG<='0';					
				
				else
				   SEG_COM_ANODE1<='1';
					SEG_COM_ANODE2<='1';
					SEG_COM_ANODE3<='1';
					SEG_COM_ANODE4<='1';					
					LED1<='0';
					SEG_CA<='1';
					SEG_CB<='1';
					SEG_CC<='1';
					SEG_CD<='1';
					SEG_CE<='1';
					SEG_CF<='1';
					SEG_CG<='1';
				
		 end if;		 	 
		end if;
	end process;
end Beh;

