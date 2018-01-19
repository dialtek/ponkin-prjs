
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY ShiftReg IS
  PORT (
    d : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    clk : IN STD_LOGIC;
    sclr : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(0 DOWNTO 0)
  );
END ShiftReg;

ARCHITECTURE ShiftReg_a OF ShiftReg IS
-- synthesis translate_off
COMPONENT wrapped_ShiftReg
  PORT (
    d : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    clk : IN STD_LOGIC;
    sclr : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(0 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_ShiftReg USE ENTITY XilinxCoreLib.c_shift_ram_v11_0(behavioral)
    GENERIC MAP (
      c_addr_width => 4,
      c_ainit_val => "0",
      c_default_data => "0",
      c_depth => 8,
      c_has_a => 0,
      c_has_ce => 0,
      c_has_sclr => 1,
      c_has_sinit => 0,
      c_has_sset => 0,
      c_mem_init_file => "no_coe_file_loaded",
      c_opt_goal => 0,
      c_parser_type => 0,
      c_read_mif => 0,
      c_reg_last_bit => 1,
      c_shift_type => 0,
      c_sinit_val => "0",
      c_sync_enable => 0,
      c_sync_priority => 1,
      c_verbosity => 0,
      c_width => 1,
      c_xdevicefamily => "spartan3e"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_ShiftReg
  PORT MAP (
    d => d,
    clk => clk,
    sclr => sclr,
    q => q
  );
-- synthesis translate_on

END ShiftReg_a;
