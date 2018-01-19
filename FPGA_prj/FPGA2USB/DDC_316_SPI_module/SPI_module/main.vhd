-- FPGA SPI MODULE 
-- last change: 19.05.14 15:11
----------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;

entity FPGA_SPI_module is
    Port ( --DIN          : in  STD_LOGIC;					 -- SPI data in
           DOUT         : buffer  STD_LOGIC;  			    -- SPI data out 
           DCLK         : buffer  STD_LOGIC; 			 -- SPI clock
			  input_data	: in STD_LOGIC_VECTOR(0 TO 7); -- transmit data buffer
           CLK_IN_40MEG : in  STD_LOGIC; 				 	 -- 40 MEG clock in
			  clock_pol    : IN	STD_LOGIC);              -- spi clock polarity
end FPGA_SPI_module;

architecture Behave of FPGA_SPI_module is
  --TYPE machine IS(init, execute);                         --state machine data type
  --SIGNAL state       	  : machine;                      --current state
  SIGNAL tx_buffer   	  : STD_LOGIC_VECTOR(0 TO 7); 	 --transmit data buffer
  SIGNAL CLK_IN_signal 	  : STD_LOGIC; 				 	 	 -- 40 MEG clock in signal
  
begin
   
	CLK_IN_signal <= CLK_IN_40MEG;
	
	process(CLK_IN_40MEG, input_data, DCLK)
	
	variable i: integer range 0 to 8 := 0;				 -- Переменная цикла	

	begin 
	
	tx_buffer(0 TO 7) <= input_data(0 TO 7);			 -- зашружаем буфер SPI для дальнейше передачи
															
if falling_edge (CLK_IN_40MEG) then

	if (i = 8) then CLK_IN_signal <= '0';
	else 		
	i := i+1;				 
	end if;
											-- инкремент переменной цикла
	--if (i = 1) then CLK_IN_signal <= '0';
	--else				 CLK_IN_signal <= not CLK_IN_signal;
	--end if;
	
	--CASE state IS
	--	when init =>
	--		i := i+1;
	--		DOUT	<= '0';												 -- обнуляем линию DOUT SPI	- начальное состояние
	--		state <= execute;
		
	--	when execute =>
			--DCLK <= not DCLK;								-- инверсия тактового сигнала при на каждой итерации цикла
			--CLK_IN_signal <= not CLK_IN_signal;			
			
--M1:	case i is
--		when 0 => DCLK <= '1';
--		when 1 => DCLK <= '0';
--		when 2 => DCLK <= '1';
--		when 3 => DCLK <= '0';
--		when 4 => DCLK <= '1';
--		when 5 => DCLK <= '0';
--		when 6 => DCLK <= '1';
--		when 7 => DCLK <= '0';
--		when 8 => DCLK <= '1';
	
	 --if (i = 8) then 				
				--CLK_IN_signal <= '0'; 	-- обнуление сигнала CLK SPI после 8-ми тактов	
				--DOUT <= '0';									-- обнуление сигнала DOUT SPI после 8-ми тактов
				--DCLK <= '0';
			--else 											
			--	if (tx_buffer(i) = '1') then			-- проверка на высокий лог. уровень	
			--			DOUT <= '1';							 
			--	else  DOUT <= '0';		
			--	end if;
				
	 --end if;
					
--	end case;
	
--	i := i+1;
	
		end if;
	end process;
	
	DCLK <= CLK_IN_signal;

end Behave;