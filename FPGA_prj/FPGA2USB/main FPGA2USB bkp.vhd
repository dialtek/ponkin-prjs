library IEEE;
use IEEE.STD_LOGIC_1164.ALL;      
use IEEE.STD_LOGIC_ARITH.ALL;     
use IEEE.STD_LOGIC_UNSIGNED.ALL;
library UNISIM;
use UNISIM.vcomponents.all;

entity FPGA2USB is 
	Port (                     
	 fdata     			: inout STD_LOGIC_VECTOR(7 downto 0);  --  FIFO data lines.
	 faddr    		   : out 	 STD_LOGIC_VECTOR(1 downto 0);     --  FIFO select lines
	 slrd      			: out   STD_LOGIC;                        -- Read control line
	 slwr      			: out   STD_LOGIC;                        -- Write control line
    
	 FIFO_full_fl     : in  STD_LOGIC;                        --EP6 full flag
--	 flaga     : in  STD_LOGIC;                        --EP2 empty flag
	 input_buf_empty_fl: inout  STD_LOGIC;
	 
--	 Sw7_led : out STD_LOGIC;
--	 Sw7     : in STD_LOGIC;
	 
	 
	 sloe      : out STD_LOGIC;                        --Slave Output Enable control
--	 pkt_end   : out STD_LOGIC;
--        done      : out STD_LOGIC;
--         sync      : in std_logic;
			
	 CLKIN_IBUFG_OUT : out   std_logic; 
    CLK0_OUT        : out   std_logic;
	 CLKIN_IN       : in  STD_LOGIC;                        --Interface Clock
	 CLKFX_OUT   : inout STD_LOGIC;
	 LOCKED_OUT      : out   std_logic;
	 RST_IN          : in    std_logic);
	 --BTN3				  : in    std_logic;
	 --LED0				  : out   std_logic);
	
end FPGA2USB;

architecture behav of FPGA2USB is

component fx2lp_clk_div is
   port ( CLKIN_IN        : in    std_logic; 
          RST_IN          : in    std_logic; 
          CLKFX_OUT       : inout   std_logic; 
          CLKIN_IBUFG_OUT : out   std_logic; 
          CLK0_OUT        : out   std_logic; 
          LOCKED_OUT      : out   std_logic);
			 --CLKIN_IN - 50MEG
			 --CLKFX_OUT - 48MEG
end component;

--streamIN fsm signal
--type stream_in_state is (stram_in_idle, stream_in_write);
--signal current_stream_in_state, next_stream_in_state : stream_in_state;
----
signal slrd_n, slwr_n,sloe_n: std_logic;
--sloe_n,slrd_d_n
----
--signal fl_d_signal: std_logic;
--signal lock : std_logic;
----
signal data_out : std_logic_vector(7 downto 0);
signal fifo_addr: std_logic_vector(1 downto 0);


--signal done_d   : std_logic;
--signal wait_s   : std_logic_vector(3 downto 0);

begin --architecture begining
input_buf_empty_fl <= FIFO_full_fl;
--btn_on_signal <= BTN3;
faddr <= fifo_addr;
fifo_addr <= "10"; -- 0x10 работает, не изменять!!
slwr <= slwr_n;
sloe <= sloe_n;
--slwr_n <= '0';
slrd <= slrd_n;


--CLKFX_OUT_48MEG <= CLKFX_OUT;

-----------------------------------------------------------
--clock divider 50M to 48M using Xilinx DCM 
clk_div: fx2lp_clk_div
		port map	(CLKIN_IN=>CLKIN_IN,CLKFX_OUT=>CLKFX_OUT,
	CLKIN_IBUFG_OUT=>CLKIN_IBUFG_OUT,CLK0_OUT=>CLK0_OUT,
	LOCKED_OUT=>LOCKED_OUT,RST_IN=>RST_IN);
-----------------------------------------------------------

process(CLKFX_OUT,FIFO_full_fl) begin
        if(CLKFX_OUT'event and CLKFX_OUT = '1')then		  
		  if(FIFO_full_fl = '1')then
			sloe_n <= '1';
			slwr_n <= '0';
			data_out <= "11110010";
			slrd_n <= '1';

		  if(FIFO_full_fl = '0') then
			data_out <= "00000000";
			sloe_n <= '0';
         slwr_n <= '1';
			slrd_n <= '1';
			
		  end if;
          end if;
			   end if;  			  

end process;

fdata <= data_out;
--LED0  <= btn_on_signal;

end architecture;

