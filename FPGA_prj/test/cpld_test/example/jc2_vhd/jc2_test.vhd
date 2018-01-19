-- VHDL Test Bench for jc2_top design functional and timing simulation

LIBRARY  IEEE;
USE IEEE.std_logic_1164.all;

ENTITY testbench IS
END testbench;

ARCHITECTURE testbench_arch OF testbench IS
	COMPONENT jc2_top
		PORT (
			CLK : in  STD_LOGIC;
			LEFT : in  STD_LOGIC;
			RIGHT : in  STD_LOGIC;
			STOP : in  STD_LOGIC;
         		Q: inout STD_LOGIC_VECTOR (3 DOWNTO 0)
		);
	END COMPONENT;

	SIGNAL CLK : STD_LOGIC;
	SIGNAL LEFT : STD_LOGIC;
	SIGNAL RIGHT : STD_LOGIC;
	SIGNAL STOP : STD_LOGIC;
	SIGNAL Q : STD_LOGIC_VECTOR (3 DOWNTO 0);

BEGIN
	UUT : jc2_top
	PORT MAP (
		LEFT => LEFT,
		RIGHT => RIGHT,
		STOP => STOP,
		CLK => CLK,
		Q => Q
	);

	PROCESS
		BEGIN
		-- --------------------
		CLK <= transport '0';
		LEFT <= transport '1';
		RIGHT <= transport '1';
		STOP <= transport '1';
		-- --------------------
		WAIT FOR 110 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		LEFT <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		LEFT <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		STOP <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		STOP <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		RIGHT <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		RIGHT <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		LEFT <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		LEFT <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '1';
		-- --------------------
		WAIT FOR 10 ns;
		CLK <= transport '0';
		-- --------------------
		WAIT;
	END PROCESS;
END testbench_arch;

CONFIGURATION jc2_top_cfg OF testbench IS
	FOR testbench_arch
	END FOR;
END jc2_top_cfg;
