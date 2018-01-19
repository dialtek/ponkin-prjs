
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library UNISIM;
use UNISIM.VComponents.all;

entity FPGA2USB_new is
port(
		faddr: out STD_LOGIC_VECTOR(1 downto 0));     --  FIFO select lines);
end FPGA2USB_new;

architecture Behavioral of FPGA2USB_new is

begin
faddr <= "01";


end Behavioral;

