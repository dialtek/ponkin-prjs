library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity simul is
    Port ( btn : in  STD_LOGIC;
			  --clock_ : in  STD_LOGIC;
           led : out  STD_LOGIC);
end simul_;

architecture Beh of simul is

begin
led <= NOT btn;
end Beh;

