--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.28xd
--  \   \         Application: netgen
--  /   /         Filename: rs232_test_synthesis.vhd
-- /___/   /\     Timestamp: Tue Aug 06 16:50:04 2013
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -ar Structure -tm rs232_test -w -dir netgen/synthesis -ofmt vhdl -sim rs232_test.ngc rs232_test_synthesis.vhd 
-- Device	: xc3s500e-4-fg320
-- Input file	: rs232_test.ngc
-- Output file	: C:\Xilinx\test\RS232_test\rs232_test\netgen\synthesis\rs232_test_synthesis.vhd
-- # of Entities	: 1
-- Design Name	: rs232_test
-- Xilinx	: C:\Xilinx\14.2\ISE_DS\ISE\
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Command Line Tools User Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
use UNISIM.VPKG.ALL;

entity rs232_test is
  port (
    pin_rx : in STD_LOGIC := 'X'; 
    LED0 : out STD_LOGIC; 
    pin_tx : out STD_LOGIC; 
    clk_50M : in STD_LOGIC := 'X' 
  );
end rs232_test;

architecture Structure of rs232_test is
  signal Mcompar_count_cmp_lt0000_cy_0_rt_2 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_cy_4_rt_8 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_cy_7_rt_12 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_cy_9_rt_15 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_10_Q_16 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_1_Q_17 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_2_Q_18 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_3_Q : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_5_Q : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_6_Q_21 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_lut_8_Q : STD_LOGIC; 
  signal Mcount_count_cy_10_rt_25 : STD_LOGIC; 
  signal Mcount_count_cy_11_rt_27 : STD_LOGIC; 
  signal Mcount_count_cy_12_rt_29 : STD_LOGIC; 
  signal Mcount_count_cy_13_rt_31 : STD_LOGIC; 
  signal Mcount_count_cy_14_rt_33 : STD_LOGIC; 
  signal Mcount_count_cy_15_rt_35 : STD_LOGIC; 
  signal Mcount_count_cy_16_rt_37 : STD_LOGIC; 
  signal Mcount_count_cy_17_rt_39 : STD_LOGIC; 
  signal Mcount_count_cy_18_rt_41 : STD_LOGIC; 
  signal Mcount_count_cy_19_rt_43 : STD_LOGIC; 
  signal Mcount_count_cy_1_rt_45 : STD_LOGIC; 
  signal Mcount_count_cy_20_rt_47 : STD_LOGIC; 
  signal Mcount_count_cy_21_rt_49 : STD_LOGIC; 
  signal Mcount_count_cy_22_rt_51 : STD_LOGIC; 
  signal Mcount_count_cy_23_rt_53 : STD_LOGIC; 
  signal Mcount_count_cy_24_rt_55 : STD_LOGIC; 
  signal Mcount_count_cy_25_rt_57 : STD_LOGIC; 
  signal Mcount_count_cy_26_rt_59 : STD_LOGIC; 
  signal Mcount_count_cy_2_rt_61 : STD_LOGIC; 
  signal Mcount_count_cy_3_rt_63 : STD_LOGIC; 
  signal Mcount_count_cy_4_rt_65 : STD_LOGIC; 
  signal Mcount_count_cy_5_rt_67 : STD_LOGIC; 
  signal Mcount_count_cy_6_rt_69 : STD_LOGIC; 
  signal Mcount_count_cy_7_rt_71 : STD_LOGIC; 
  signal Mcount_count_cy_8_rt_73 : STD_LOGIC; 
  signal Mcount_count_cy_9_rt_75 : STD_LOGIC; 
  signal Mcount_count_xor_27_rt_77 : STD_LOGIC; 
  signal N0 : STD_LOGIC; 
  signal N1 : STD_LOGIC; 
  signal clk_50M_BUFGP_109 : STD_LOGIC; 
  signal count_and0000 : STD_LOGIC; 
  signal count_cmp_lt0000 : STD_LOGIC; 
  signal led_on_153 : STD_LOGIC; 
  signal led_on_not0002 : STD_LOGIC; 
  signal Mcompar_count_cmp_lt0000_cy : STD_LOGIC_VECTOR ( 10 downto 0 ); 
  signal Mcount_count_cy : STD_LOGIC_VECTOR ( 26 downto 0 ); 
  signal Mcount_count_lut : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal Result : STD_LOGIC_VECTOR ( 27 downto 0 ); 
  signal count : STD_LOGIC_VECTOR ( 27 downto 0 ); 
  signal count_and0000_wg_cy : STD_LOGIC_VECTOR ( 5 downto 0 ); 
  signal count_and0000_wg_lut : STD_LOGIC_VECTOR ( 6 downto 0 ); 
begin
  XST_GND : GND
    port map (
      G => N0
    );
  XST_VCC : VCC
    port map (
      P => N1
    );
  led_on : FDE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_and0000,
      D => led_on_not0002,
      Q => led_on_153
    );
  count_0 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(0),
      R => count_and0000,
      Q => count(0)
    );
  count_1 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(1),
      R => count_and0000,
      Q => count(1)
    );
  count_2 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(2),
      R => count_and0000,
      Q => count(2)
    );
  count_3 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(3),
      R => count_and0000,
      Q => count(3)
    );
  count_4 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(4),
      R => count_and0000,
      Q => count(4)
    );
  count_5 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(5),
      R => count_and0000,
      Q => count(5)
    );
  count_6 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(6),
      R => count_and0000,
      Q => count(6)
    );
  count_7 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(7),
      R => count_and0000,
      Q => count(7)
    );
  count_8 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(8),
      R => count_and0000,
      Q => count(8)
    );
  count_9 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(9),
      R => count_and0000,
      Q => count(9)
    );
  count_10 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(10),
      R => count_and0000,
      Q => count(10)
    );
  count_11 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(11),
      R => count_and0000,
      Q => count(11)
    );
  count_12 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(12),
      R => count_and0000,
      Q => count(12)
    );
  count_13 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(13),
      R => count_and0000,
      Q => count(13)
    );
  count_14 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(14),
      R => count_and0000,
      Q => count(14)
    );
  count_15 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(15),
      R => count_and0000,
      Q => count(15)
    );
  count_16 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(16),
      R => count_and0000,
      Q => count(16)
    );
  count_17 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(17),
      R => count_and0000,
      Q => count(17)
    );
  count_18 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(18),
      R => count_and0000,
      Q => count(18)
    );
  count_19 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(19),
      R => count_and0000,
      Q => count(19)
    );
  count_20 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(20),
      R => count_and0000,
      Q => count(20)
    );
  count_21 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(21),
      R => count_and0000,
      Q => count(21)
    );
  count_22 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(22),
      R => count_and0000,
      Q => count(22)
    );
  count_23 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(23),
      R => count_and0000,
      Q => count(23)
    );
  count_24 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(24),
      R => count_and0000,
      Q => count(24)
    );
  count_25 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(25),
      R => count_and0000,
      Q => count(25)
    );
  count_26 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(26),
      R => count_and0000,
      Q => count(26)
    );
  count_27 : FDRE
    generic map(
      INIT => '0'
    )
    port map (
      C => clk_50M_BUFGP_109,
      CE => count_cmp_lt0000,
      D => Result(27),
      R => count_and0000,
      Q => count(27)
    );
  Mcompar_count_cmp_lt0000_cy_0_Q : MUXCY
    port map (
      CI => N1,
      DI => N0,
      S => Mcompar_count_cmp_lt0000_cy_0_rt_2,
      O => Mcompar_count_cmp_lt0000_cy(0)
    );
  Mcompar_count_cmp_lt0000_lut_1_Q : LUT4
    generic map(
      INIT => X"0001"
    )
    port map (
      I0 => count(8),
      I1 => count(9),
      I2 => count(10),
      I3 => count(11),
      O => Mcompar_count_cmp_lt0000_lut_1_Q_17
    );
  Mcompar_count_cmp_lt0000_cy_1_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(0),
      DI => N1,
      S => Mcompar_count_cmp_lt0000_lut_1_Q_17,
      O => Mcompar_count_cmp_lt0000_cy(1)
    );
  Mcompar_count_cmp_lt0000_lut_2_Q : LUT4
    generic map(
      INIT => X"8000"
    )
    port map (
      I0 => count(12),
      I1 => count(13),
      I2 => count(14),
      I3 => count(15),
      O => Mcompar_count_cmp_lt0000_lut_2_Q_18
    );
  Mcompar_count_cmp_lt0000_cy_2_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(1),
      DI => N0,
      S => Mcompar_count_cmp_lt0000_lut_2_Q_18,
      O => Mcompar_count_cmp_lt0000_cy(2)
    );
  Mcompar_count_cmp_lt0000_cy_3_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(2),
      DI => N1,
      S => Mcompar_count_cmp_lt0000_lut_3_Q,
      O => Mcompar_count_cmp_lt0000_cy(3)
    );
  Mcompar_count_cmp_lt0000_cy_4_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(3),
      DI => N0,
      S => Mcompar_count_cmp_lt0000_cy_4_rt_8,
      O => Mcompar_count_cmp_lt0000_cy(4)
    );
  Mcompar_count_cmp_lt0000_cy_5_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(4),
      DI => N1,
      S => Mcompar_count_cmp_lt0000_lut_5_Q,
      O => Mcompar_count_cmp_lt0000_cy(5)
    );
  Mcompar_count_cmp_lt0000_lut_6_Q : LUT4
    generic map(
      INIT => X"8000"
    )
    port map (
      I0 => count(19),
      I1 => count(20),
      I2 => count(21),
      I3 => count(22),
      O => Mcompar_count_cmp_lt0000_lut_6_Q_21
    );
  Mcompar_count_cmp_lt0000_cy_6_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(5),
      DI => N0,
      S => Mcompar_count_cmp_lt0000_lut_6_Q_21,
      O => Mcompar_count_cmp_lt0000_cy(6)
    );
  Mcompar_count_cmp_lt0000_cy_7_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(6),
      DI => N0,
      S => Mcompar_count_cmp_lt0000_cy_7_rt_12,
      O => Mcompar_count_cmp_lt0000_cy(7)
    );
  Mcompar_count_cmp_lt0000_cy_8_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(7),
      DI => N1,
      S => Mcompar_count_cmp_lt0000_lut_8_Q,
      O => Mcompar_count_cmp_lt0000_cy(8)
    );
  Mcompar_count_cmp_lt0000_cy_9_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(8),
      DI => N0,
      S => Mcompar_count_cmp_lt0000_cy_9_rt_15,
      O => Mcompar_count_cmp_lt0000_cy(9)
    );
  Mcompar_count_cmp_lt0000_lut_10_Q : LUT2
    generic map(
      INIT => X"1"
    )
    port map (
      I0 => count(26),
      I1 => count(27),
      O => Mcompar_count_cmp_lt0000_lut_10_Q_16
    );
  Mcompar_count_cmp_lt0000_cy_10_Q : MUXCY
    port map (
      CI => Mcompar_count_cmp_lt0000_cy(9),
      DI => N1,
      S => Mcompar_count_cmp_lt0000_lut_10_Q_16,
      O => Mcompar_count_cmp_lt0000_cy(10)
    );
  Mcount_count_cy_0_Q : MUXCY
    port map (
      CI => N0,
      DI => N1,
      S => Mcount_count_lut(0),
      O => Mcount_count_cy(0)
    );
  Mcount_count_xor_0_Q : XORCY
    port map (
      CI => N0,
      LI => Mcount_count_lut(0),
      O => Result(0)
    );
  Mcount_count_cy_1_Q : MUXCY
    port map (
      CI => Mcount_count_cy(0),
      DI => N0,
      S => Mcount_count_cy_1_rt_45,
      O => Mcount_count_cy(1)
    );
  Mcount_count_xor_1_Q : XORCY
    port map (
      CI => Mcount_count_cy(0),
      LI => Mcount_count_cy_1_rt_45,
      O => Result(1)
    );
  Mcount_count_cy_2_Q : MUXCY
    port map (
      CI => Mcount_count_cy(1),
      DI => N0,
      S => Mcount_count_cy_2_rt_61,
      O => Mcount_count_cy(2)
    );
  Mcount_count_xor_2_Q : XORCY
    port map (
      CI => Mcount_count_cy(1),
      LI => Mcount_count_cy_2_rt_61,
      O => Result(2)
    );
  Mcount_count_cy_3_Q : MUXCY
    port map (
      CI => Mcount_count_cy(2),
      DI => N0,
      S => Mcount_count_cy_3_rt_63,
      O => Mcount_count_cy(3)
    );
  Mcount_count_xor_3_Q : XORCY
    port map (
      CI => Mcount_count_cy(2),
      LI => Mcount_count_cy_3_rt_63,
      O => Result(3)
    );
  Mcount_count_cy_4_Q : MUXCY
    port map (
      CI => Mcount_count_cy(3),
      DI => N0,
      S => Mcount_count_cy_4_rt_65,
      O => Mcount_count_cy(4)
    );
  Mcount_count_xor_4_Q : XORCY
    port map (
      CI => Mcount_count_cy(3),
      LI => Mcount_count_cy_4_rt_65,
      O => Result(4)
    );
  Mcount_count_cy_5_Q : MUXCY
    port map (
      CI => Mcount_count_cy(4),
      DI => N0,
      S => Mcount_count_cy_5_rt_67,
      O => Mcount_count_cy(5)
    );
  Mcount_count_xor_5_Q : XORCY
    port map (
      CI => Mcount_count_cy(4),
      LI => Mcount_count_cy_5_rt_67,
      O => Result(5)
    );
  Mcount_count_cy_6_Q : MUXCY
    port map (
      CI => Mcount_count_cy(5),
      DI => N0,
      S => Mcount_count_cy_6_rt_69,
      O => Mcount_count_cy(6)
    );
  Mcount_count_xor_6_Q : XORCY
    port map (
      CI => Mcount_count_cy(5),
      LI => Mcount_count_cy_6_rt_69,
      O => Result(6)
    );
  Mcount_count_cy_7_Q : MUXCY
    port map (
      CI => Mcount_count_cy(6),
      DI => N0,
      S => Mcount_count_cy_7_rt_71,
      O => Mcount_count_cy(7)
    );
  Mcount_count_xor_7_Q : XORCY
    port map (
      CI => Mcount_count_cy(6),
      LI => Mcount_count_cy_7_rt_71,
      O => Result(7)
    );
  Mcount_count_cy_8_Q : MUXCY
    port map (
      CI => Mcount_count_cy(7),
      DI => N0,
      S => Mcount_count_cy_8_rt_73,
      O => Mcount_count_cy(8)
    );
  Mcount_count_xor_8_Q : XORCY
    port map (
      CI => Mcount_count_cy(7),
      LI => Mcount_count_cy_8_rt_73,
      O => Result(8)
    );
  Mcount_count_cy_9_Q : MUXCY
    port map (
      CI => Mcount_count_cy(8),
      DI => N0,
      S => Mcount_count_cy_9_rt_75,
      O => Mcount_count_cy(9)
    );
  Mcount_count_xor_9_Q : XORCY
    port map (
      CI => Mcount_count_cy(8),
      LI => Mcount_count_cy_9_rt_75,
      O => Result(9)
    );
  Mcount_count_cy_10_Q : MUXCY
    port map (
      CI => Mcount_count_cy(9),
      DI => N0,
      S => Mcount_count_cy_10_rt_25,
      O => Mcount_count_cy(10)
    );
  Mcount_count_xor_10_Q : XORCY
    port map (
      CI => Mcount_count_cy(9),
      LI => Mcount_count_cy_10_rt_25,
      O => Result(10)
    );
  Mcount_count_cy_11_Q : MUXCY
    port map (
      CI => Mcount_count_cy(10),
      DI => N0,
      S => Mcount_count_cy_11_rt_27,
      O => Mcount_count_cy(11)
    );
  Mcount_count_xor_11_Q : XORCY
    port map (
      CI => Mcount_count_cy(10),
      LI => Mcount_count_cy_11_rt_27,
      O => Result(11)
    );
  Mcount_count_cy_12_Q : MUXCY
    port map (
      CI => Mcount_count_cy(11),
      DI => N0,
      S => Mcount_count_cy_12_rt_29,
      O => Mcount_count_cy(12)
    );
  Mcount_count_xor_12_Q : XORCY
    port map (
      CI => Mcount_count_cy(11),
      LI => Mcount_count_cy_12_rt_29,
      O => Result(12)
    );
  Mcount_count_cy_13_Q : MUXCY
    port map (
      CI => Mcount_count_cy(12),
      DI => N0,
      S => Mcount_count_cy_13_rt_31,
      O => Mcount_count_cy(13)
    );
  Mcount_count_xor_13_Q : XORCY
    port map (
      CI => Mcount_count_cy(12),
      LI => Mcount_count_cy_13_rt_31,
      O => Result(13)
    );
  Mcount_count_cy_14_Q : MUXCY
    port map (
      CI => Mcount_count_cy(13),
      DI => N0,
      S => Mcount_count_cy_14_rt_33,
      O => Mcount_count_cy(14)
    );
  Mcount_count_xor_14_Q : XORCY
    port map (
      CI => Mcount_count_cy(13),
      LI => Mcount_count_cy_14_rt_33,
      O => Result(14)
    );
  Mcount_count_cy_15_Q : MUXCY
    port map (
      CI => Mcount_count_cy(14),
      DI => N0,
      S => Mcount_count_cy_15_rt_35,
      O => Mcount_count_cy(15)
    );
  Mcount_count_xor_15_Q : XORCY
    port map (
      CI => Mcount_count_cy(14),
      LI => Mcount_count_cy_15_rt_35,
      O => Result(15)
    );
  Mcount_count_cy_16_Q : MUXCY
    port map (
      CI => Mcount_count_cy(15),
      DI => N0,
      S => Mcount_count_cy_16_rt_37,
      O => Mcount_count_cy(16)
    );
  Mcount_count_xor_16_Q : XORCY
    port map (
      CI => Mcount_count_cy(15),
      LI => Mcount_count_cy_16_rt_37,
      O => Result(16)
    );
  Mcount_count_cy_17_Q : MUXCY
    port map (
      CI => Mcount_count_cy(16),
      DI => N0,
      S => Mcount_count_cy_17_rt_39,
      O => Mcount_count_cy(17)
    );
  Mcount_count_xor_17_Q : XORCY
    port map (
      CI => Mcount_count_cy(16),
      LI => Mcount_count_cy_17_rt_39,
      O => Result(17)
    );
  Mcount_count_cy_18_Q : MUXCY
    port map (
      CI => Mcount_count_cy(17),
      DI => N0,
      S => Mcount_count_cy_18_rt_41,
      O => Mcount_count_cy(18)
    );
  Mcount_count_xor_18_Q : XORCY
    port map (
      CI => Mcount_count_cy(17),
      LI => Mcount_count_cy_18_rt_41,
      O => Result(18)
    );
  Mcount_count_cy_19_Q : MUXCY
    port map (
      CI => Mcount_count_cy(18),
      DI => N0,
      S => Mcount_count_cy_19_rt_43,
      O => Mcount_count_cy(19)
    );
  Mcount_count_xor_19_Q : XORCY
    port map (
      CI => Mcount_count_cy(18),
      LI => Mcount_count_cy_19_rt_43,
      O => Result(19)
    );
  Mcount_count_cy_20_Q : MUXCY
    port map (
      CI => Mcount_count_cy(19),
      DI => N0,
      S => Mcount_count_cy_20_rt_47,
      O => Mcount_count_cy(20)
    );
  Mcount_count_xor_20_Q : XORCY
    port map (
      CI => Mcount_count_cy(19),
      LI => Mcount_count_cy_20_rt_47,
      O => Result(20)
    );
  Mcount_count_cy_21_Q : MUXCY
    port map (
      CI => Mcount_count_cy(20),
      DI => N0,
      S => Mcount_count_cy_21_rt_49,
      O => Mcount_count_cy(21)
    );
  Mcount_count_xor_21_Q : XORCY
    port map (
      CI => Mcount_count_cy(20),
      LI => Mcount_count_cy_21_rt_49,
      O => Result(21)
    );
  Mcount_count_cy_22_Q : MUXCY
    port map (
      CI => Mcount_count_cy(21),
      DI => N0,
      S => Mcount_count_cy_22_rt_51,
      O => Mcount_count_cy(22)
    );
  Mcount_count_xor_22_Q : XORCY
    port map (
      CI => Mcount_count_cy(21),
      LI => Mcount_count_cy_22_rt_51,
      O => Result(22)
    );
  Mcount_count_cy_23_Q : MUXCY
    port map (
      CI => Mcount_count_cy(22),
      DI => N0,
      S => Mcount_count_cy_23_rt_53,
      O => Mcount_count_cy(23)
    );
  Mcount_count_xor_23_Q : XORCY
    port map (
      CI => Mcount_count_cy(22),
      LI => Mcount_count_cy_23_rt_53,
      O => Result(23)
    );
  Mcount_count_cy_24_Q : MUXCY
    port map (
      CI => Mcount_count_cy(23),
      DI => N0,
      S => Mcount_count_cy_24_rt_55,
      O => Mcount_count_cy(24)
    );
  Mcount_count_xor_24_Q : XORCY
    port map (
      CI => Mcount_count_cy(23),
      LI => Mcount_count_cy_24_rt_55,
      O => Result(24)
    );
  Mcount_count_cy_25_Q : MUXCY
    port map (
      CI => Mcount_count_cy(24),
      DI => N0,
      S => Mcount_count_cy_25_rt_57,
      O => Mcount_count_cy(25)
    );
  Mcount_count_xor_25_Q : XORCY
    port map (
      CI => Mcount_count_cy(24),
      LI => Mcount_count_cy_25_rt_57,
      O => Result(25)
    );
  Mcount_count_cy_26_Q : MUXCY
    port map (
      CI => Mcount_count_cy(25),
      DI => N0,
      S => Mcount_count_cy_26_rt_59,
      O => Mcount_count_cy(26)
    );
  Mcount_count_xor_26_Q : XORCY
    port map (
      CI => Mcount_count_cy(25),
      LI => Mcount_count_cy_26_rt_59,
      O => Result(26)
    );
  Mcount_count_xor_27_Q : XORCY
    port map (
      CI => Mcount_count_cy(26),
      LI => Mcount_count_xor_27_rt_77,
      O => Result(27)
    );
  count_and0000_wg_lut_0_Q : LUT4
    generic map(
      INIT => X"0100"
    )
    port map (
      I0 => count(5),
      I1 => count(9),
      I2 => count(8),
      I3 => count(7),
      O => count_and0000_wg_lut(0)
    );
  count_and0000_wg_cy_0_Q : MUXCY
    port map (
      CI => N1,
      DI => N0,
      S => count_and0000_wg_lut(0),
      O => count_and0000_wg_cy(0)
    );
  count_and0000_wg_lut_1_Q : LUT4
    generic map(
      INIT => X"0002"
    )
    port map (
      I0 => count(13),
      I1 => count(10),
      I2 => count(4),
      I3 => count(11),
      O => count_and0000_wg_lut(1)
    );
  count_and0000_wg_cy_1_Q : MUXCY
    port map (
      CI => count_and0000_wg_cy(0),
      DI => N0,
      S => count_and0000_wg_lut(1),
      O => count_and0000_wg_cy(1)
    );
  count_and0000_wg_lut_2_Q : LUT4
    generic map(
      INIT => X"0800"
    )
    port map (
      I0 => count(12),
      I1 => count(14),
      I2 => count(6),
      I3 => count(15),
      O => count_and0000_wg_lut(2)
    );
  count_and0000_wg_cy_2_Q : MUXCY
    port map (
      CI => count_and0000_wg_cy(1),
      DI => N0,
      S => count_and0000_wg_lut(2),
      O => count_and0000_wg_cy(2)
    );
  count_and0000_wg_lut_3_Q : LUT4
    generic map(
      INIT => X"0400"
    )
    port map (
      I0 => count(16),
      I1 => count(17),
      I2 => count(3),
      I3 => count(20),
      O => count_and0000_wg_lut(3)
    );
  count_and0000_wg_cy_3_Q : MUXCY
    port map (
      CI => count_and0000_wg_cy(2),
      DI => N0,
      S => count_and0000_wg_lut(3),
      O => count_and0000_wg_cy(3)
    );
  count_and0000_wg_lut_4_Q : LUT4
    generic map(
      INIT => X"0400"
    )
    port map (
      I0 => count(18),
      I1 => count(19),
      I2 => count(2),
      I3 => count(21),
      O => count_and0000_wg_lut(4)
    );
  count_and0000_wg_cy_4_Q : MUXCY
    port map (
      CI => count_and0000_wg_cy(3),
      DI => N0,
      S => count_and0000_wg_lut(4),
      O => count_and0000_wg_cy(4)
    );
  count_and0000_wg_lut_5_Q : LUT4
    generic map(
      INIT => X"0400"
    )
    port map (
      I0 => count(1),
      I1 => count(22),
      I2 => count(24),
      I3 => count(23),
      O => count_and0000_wg_lut(5)
    );
  count_and0000_wg_cy_5_Q : MUXCY
    port map (
      CI => count_and0000_wg_cy(4),
      DI => N0,
      S => count_and0000_wg_lut(5),
      O => count_and0000_wg_cy(5)
    );
  count_and0000_wg_lut_6_Q : LUT4
    generic map(
      INIT => X"0002"
    )
    port map (
      I0 => count(25),
      I1 => count(27),
      I2 => count(0),
      I3 => count(26),
      O => count_and0000_wg_lut(6)
    );
  count_and0000_wg_cy_6_Q : MUXCY
    port map (
      CI => count_and0000_wg_cy(5),
      DI => N0,
      S => count_and0000_wg_lut(6),
      O => count_and0000
    );
  LED0_OBUF : OBUF
    port map (
      I => led_on_153,
      O => LED0
    );
  pin_tx_OBUF : OBUF
    port map (
      I => led_on_153,
      O => pin_tx
    );
  Mcompar_count_cmp_lt0000_cy_0_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(7),
      O => Mcompar_count_cmp_lt0000_cy_0_rt_2
    );
  Mcompar_count_cmp_lt0000_cy_4_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(17),
      O => Mcompar_count_cmp_lt0000_cy_4_rt_8
    );
  Mcompar_count_cmp_lt0000_cy_7_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(23),
      O => Mcompar_count_cmp_lt0000_cy_7_rt_12
    );
  Mcompar_count_cmp_lt0000_cy_9_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(25),
      O => Mcompar_count_cmp_lt0000_cy_9_rt_15
    );
  Mcount_count_cy_1_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(1),
      O => Mcount_count_cy_1_rt_45
    );
  Mcount_count_cy_2_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(2),
      O => Mcount_count_cy_2_rt_61
    );
  Mcount_count_cy_3_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(3),
      O => Mcount_count_cy_3_rt_63
    );
  Mcount_count_cy_4_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(4),
      O => Mcount_count_cy_4_rt_65
    );
  Mcount_count_cy_5_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(5),
      O => Mcount_count_cy_5_rt_67
    );
  Mcount_count_cy_6_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(6),
      O => Mcount_count_cy_6_rt_69
    );
  Mcount_count_cy_7_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(7),
      O => Mcount_count_cy_7_rt_71
    );
  Mcount_count_cy_8_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(8),
      O => Mcount_count_cy_8_rt_73
    );
  Mcount_count_cy_9_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(9),
      O => Mcount_count_cy_9_rt_75
    );
  Mcount_count_cy_10_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(10),
      O => Mcount_count_cy_10_rt_25
    );
  Mcount_count_cy_11_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(11),
      O => Mcount_count_cy_11_rt_27
    );
  Mcount_count_cy_12_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(12),
      O => Mcount_count_cy_12_rt_29
    );
  Mcount_count_cy_13_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(13),
      O => Mcount_count_cy_13_rt_31
    );
  Mcount_count_cy_14_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(14),
      O => Mcount_count_cy_14_rt_33
    );
  Mcount_count_cy_15_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(15),
      O => Mcount_count_cy_15_rt_35
    );
  Mcount_count_cy_16_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(16),
      O => Mcount_count_cy_16_rt_37
    );
  Mcount_count_cy_17_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(17),
      O => Mcount_count_cy_17_rt_39
    );
  Mcount_count_cy_18_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(18),
      O => Mcount_count_cy_18_rt_41
    );
  Mcount_count_cy_19_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(19),
      O => Mcount_count_cy_19_rt_43
    );
  Mcount_count_cy_20_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(20),
      O => Mcount_count_cy_20_rt_47
    );
  Mcount_count_cy_21_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(21),
      O => Mcount_count_cy_21_rt_49
    );
  Mcount_count_cy_22_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(22),
      O => Mcount_count_cy_22_rt_51
    );
  Mcount_count_cy_23_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(23),
      O => Mcount_count_cy_23_rt_53
    );
  Mcount_count_cy_24_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(24),
      O => Mcount_count_cy_24_rt_55
    );
  Mcount_count_cy_25_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(25),
      O => Mcount_count_cy_25_rt_57
    );
  Mcount_count_cy_26_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(26),
      O => Mcount_count_cy_26_rt_59
    );
  Mcount_count_xor_27_rt : LUT1
    generic map(
      INIT => X"2"
    )
    port map (
      I0 => count(27),
      O => Mcount_count_xor_27_rt_77
    );
  clk_50M_BUFGP : BUFGP
    port map (
      I => clk_50M,
      O => clk_50M_BUFGP_109
    );
  Mcompar_count_cmp_lt0000_lut_3_INV_0 : INV
    port map (
      I => count(16),
      O => Mcompar_count_cmp_lt0000_lut_3_Q
    );
  Mcompar_count_cmp_lt0000_lut_5_INV_0 : INV
    port map (
      I => count(18),
      O => Mcompar_count_cmp_lt0000_lut_5_Q
    );
  Mcompar_count_cmp_lt0000_lut_8_INV_0 : INV
    port map (
      I => count(24),
      O => Mcompar_count_cmp_lt0000_lut_8_Q
    );
  Mcompar_count_cmp_lt0000_cy_10_inv_INV_0 : INV
    port map (
      I => Mcompar_count_cmp_lt0000_cy(10),
      O => count_cmp_lt0000
    );
  Mcount_count_lut_0_INV_0 : INV
    port map (
      I => count(0),
      O => Mcount_count_lut(0)
    );
  led_on_not00021_INV_0 : INV
    port map (
      I => led_on_153,
      O => led_on_not0002
    );

end Structure;

