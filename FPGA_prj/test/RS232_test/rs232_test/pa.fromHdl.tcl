
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name rs232_test -dir "C:/Xilinx/test/RS232_test/rs232_test/planAhead_run_1" -part xc3s500efg320-4
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "rs232_test_imp.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {rs232_test.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top rs232_test $srcset
add_files [list {rs232_test_imp.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc3s500efg320-4
