library IEEE;
use IEEE.STD_LOGIC_1164.ALL;      
use IEEE.STD_LOGIC_ARITH.ALL;     
use IEEE.STD_LOGIC_UNSIGNED.ALL;

library UNISIM;
use UNISIM.vcomponents.all;

entity FPGA2USB is 
	Port (                     
	 fdata     			:  inout   STD_LOGIC_VECTOR(7 downto 0);     -- ���� FIFO 
	 faddr    		   :  out 	  STD_LOGIC_VECTOR(1 downto 0);     -- ����� ������ FIFO
	 slrd      			:  out     STD_LOGIC;                        -- ����� ���������� ������ FIFO
	 slwr      			:  out     STD_LOGIC;                        -- ����� ���������� ������ � FIFO
    
	 RX_FIFO_full_fl     :  in      STD_LOGIC;                        -- EP6 full flag
--	 flaga     : in  STD_LOGIC;                                    -- EP2 empty flag
	 input_buf_empty_fl: inout   STD_LOGIC;
	 
--	 Sw7_led : out STD_LOGIC;
--	 Sw7     : in STD_LOGIC;
	 
	 
	 sloe      : out STD_LOGIC;                        --Slave Output Enable control
--	 pkt_end   : out STD_LOGIC;
--  done      : out STD_LOGIC;
--  sync      : in std_logic;
			
	 CLKIN_IBUFG_OUT  : out   std_logic; 
    CLK0_OUT         : out   std_logic;
	 CLKIN_IN         : in  STD_LOGIC;     --������� ����������� ������
	 CLK_48M   			: inout STD_LOGIC;   --�������� ����������� ������
	 LOCKED_OUT       : out   std_logic;
	 RST_IN           : in    std_logic);
	 --BTN3				  : in    std_logic;
	 --LED0				  : out   std_logic);
	
end FPGA2USB;

architecture behav of FPGA2USB is

	TYPE STATE_TYPE IS ARRAY (1 DOWNTO 0) of std_logic; -- ������� ������. �����
	CONSTANT	FIFO_inc :	STATE_TYPE := "01";
	CONSTANT	FIFO_full:	STATE_TYPE := "10";

component fx2lp_clk_div is -- 50Mhz -> 48Mhz
   port ( CLKIN_IN        : in    std_logic;   --CLKIN_IN - 50MEG
          RST_IN          : in    std_logic; 
          CLKFX_OUT       : inout   std_logic; --CLKFX_OUT - 48MEG
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic; 
          LOCKED_OUT      : out   std_logic); 
end component;

signal state : STATE_TYPE; -- ���������� ������. ����
signal slrd_n, slwr_n,sloe_n: std_logic;
signal data_out : std_logic_vector(7 downto 0);
signal fifo_addr: std_logic_vector(1 downto 0);
		
begin --architecture begining

input_buf_empty_fl <= RX_FIFO_full_fl;
--btn_on_signal <= BTN3;
faddr <= fifo_addr;
fifo_addr <= "10"; -- 0x10 ��������, �� ��������!!
slwr <= slwr_n;
sloe <= sloe_n;
--slwr_n <= '0';
slrd <= slrd_n;

--CLKFX_OUT_48MEG <= CLKFX_OUT;

-----------------------------------------------------------
--clock divider 50M to 48M using Xilinx DCM 
clk_div: fx2lp_clk_div
		port map	(CLKIN_IN        =>	CLKIN_IN,
					 CLKFX_OUT       =>	CLK_48M,
					 CLKIN_IBUFG_OUT =>	CLKIN_IBUFG_OUT,
					 CLK0_OUT        =>	CLK0_OUT,
	             LOCKED_OUT		  =>	LOCKED_OUT,
					 RST_IN          =>	RST_IN);
-----------------------------------------------------------

state_proc: process(CLK_48M,RX_FIFO_full_fl) 

--VARIABLE i   : INTEGER RANGE 0 to 127;
BEGIN 
        if(CLK_48M'event and CLK_48M = '1')then	
		  
		  state <= FIFO_inc;
		  
			CASE state IS

			WHEN FIFO_inc =>
			
			 if(input_buf_empty_fl = '1')then
				for i in 0 to 255 loop
				sloe_n <= '1';     -- ����� ���. ������ FIFO
				slwr_n <= '0';     -- ����� ���������� ������ � FIFO
				slrd_n <= '1';     -- ����� ���������� ������ FIFO	
			   data_out <= data_out + "00000001"; -- ������ ������ � FIFO
					if(input_buf_empty_fl = '0') then state <= FIFO_full; end if;
			  end loop;
          end if;

			 WHEN FIFO_full => 
			 
				slwr_n <= '0'; -- ���������� ������ � FIFO
				slrd_n <= '0'; -- ���������� ������ FIFO
				
			 WHEN OTHERS =>
			 state <= FIFO_full;
			 
			END CASE;
		end if;  			    	
end process;

fdata <= data_out;

end architecture;

