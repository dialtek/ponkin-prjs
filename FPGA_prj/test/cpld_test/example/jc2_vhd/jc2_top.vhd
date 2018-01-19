library IEEE;
use IEEE.std_logic_1164.all;  -- defines std_logic types

entity jc2_top is
    port (
	  LEFT : in STD_LOGIC;   -- Active-low switch #3 (left)
	  RIGHT : in STD_LOGIC;  -- Active-low switch #0 (right)
	  STOP : in STD_LOGIC;   -- Active-low switch #2
     CLK : in STD_LOGIC;
     Q : out STD_LOGIC_VECTOR (3 downto 0) -- Active-low LEDs
         );
--To pass pin location constraints from this HDL source file rather than 
--through a User Constraints Format (UCF) file, uncomment the six attribute 
--declarations below and remove jc2_top.ucf from the project.
--    attribute pin_assign : string;
--    attribute pin_assign of clk : signal is "A7";
--    attribute pin_assign of left : signal is "G7";
--    attribute pin_assign of right : signal is "B2";
--    attribute pin_assign of stop : signal is "F2";
--    attribute pin_assign of q : signal is "G5 F6 C6 B4";
end jc2_top;

architecture jc2_top_arch of jc2_top is
   signal DIR : STD_LOGIC := '0';	 -- Left=1, Right=0
	signal RUN : STD_LOGIC := '0';
	signal Q_int : STD_LOGIC_VECTOR (3 downto 0) := "0000";  -- Internal signal driving Q output; Active-low LEDs
begin

process (CLK, RIGHT, LEFT, STOP, RUN, DIR, Q_int)
begin
   if (CLK'event and CLK='1') then       -- CLK rising edge
   -- DIR register:
     if (RIGHT='0') then
        DIR <= '0';
     elsif (LEFT='0') then
        DIR <= '1';
     end if;
     
   -- RUN register:
     if (STOP='0') then
        RUN <= '0';
     elsif (LEFT='0' or RIGHT='0') then
        RUN <= '1';
     end if;
     
   -- Counter section:
     if (RUN='1') then
        if (DIR='1') then
           Q_int(3 downto 1) <= Q_int(2 downto 0);    -- Shift lower bits (Left Shift)
           Q_int(0) <= not Q_int(3);                  -- Circulate inverted MSB to LSB
        else
           Q_int(2 downto 0) <= Q_int(3 downto 1);    -- Shift upper bits (Right Shift)
           Q_int(3) <= not Q_int(0);                  -- Circulate inverted LSB to MSB
        end if;
     end if;
     
   end if;
	Q <= Q_int;
end process;

end jc2_top_arch;
