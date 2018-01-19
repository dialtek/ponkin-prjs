
-- Module Name:    StateMachine - Behavioral 

library IEEE;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity StateMachine is
    Port ( gclk 	 : in  STD_LOGIC;
			  spi_clk : in  STD_LOGIC;
           D 	    : in  STD_LOGIC;   -- spi in data
           Q 		 : out STD_LOGIC;   -- 20 bit out data
           CE 		 : in  STD_LOGIC;   -- spi clk enable signal
			  shout   :	out STD_LOGIC;
			  LED     :	out STD_LOGIC);
end StateMachine;

architecture Behavioral of StateMachine is


	TYPE STATE_TYPE IS ARRAY (3 DOWNTO 0) of std_logic;
--	
--	Gray Coding
--
	CONSTANT	spi_get_word :		STATE_TYPE := "0001";
	CONSTANT	concat_bytes :	   STATE_TYPE := "0011";
	CONSTANT	shift_out_d :	   STATE_TYPE := "0111";
--
signal state : STATE_TYPE; 								-- для хранения состояний
signal spi_in_word: std_logic_vector(15 downto 0); -- буфер для приема слова от SPI
signal out_word   : std_logic_vector(19 downto 0); -- буфер данных для отправки на АЦП

signal int_shout  : std_logic;
signal Q_out_s    : std_logic;

begin

process(gclk,spi_clk,CE,D)
 
 VARIABLE cnt     :	INTEGER RANGE 0 to 20;
 VARIABLE out_cnt :	INTEGER RANGE 0 to 21;
 
 begin
 
 state <= spi_get_word;
 
  IF (CE = '1') THEN -- 1 _/  CE rising edge 

	case state is

   when spi_get_word => -- считывание 2 байт данных SPI
		   
			if (spi_clk'event and spi_clk = '1') then 
			
				int_shout <= spi_in_word(15); 
				spi_in_word <= SHL(spi_in_word,"1");
				spi_in_word(0) <= D;
				cnt := cnt + 1;
			end if;				
			
			if (cnt > 15) then   
				   state <= concat_bytes;
					cnt := 0;
					
			else state <= spi_get_word;
			
			end if;
			--	 
    --
	 when concat_bytes => -- 
	 
				out_word(0)	<= '1';
				out_word(1)	<= '0';
				out_word(2)	<= '1';
				out_word(3)	<= '0';

				for i in 0 to 15 loop
              out_word(i+4) <= spi_in_word(15-i);
            end loop;
			
			state <= shift_out_d;
			
			 when shift_out_d =>
			 
			 if (gclk'event and gclk = '1') then 
			
				Q_out_s <= out_word(out_cnt);			
				out_cnt := out_cnt+1;
				
			end if;

			if (out_cnt > 20) then   
				   state <= spi_get_word;
					out_cnt := 0;
					Q_out_s <= '0';					
			else state <= shift_out_d;
			
			end if;
	 	 --   
    --
	 when others =>
	 
		   state <= spi_get_word;
	--
	
	end case;
	-------------------------
 end IF; 
	
end process; 

	Q    	<= Q_out_s;
	shout	<= int_shout;
   LED   <= '1';
	
end Behavioral;

