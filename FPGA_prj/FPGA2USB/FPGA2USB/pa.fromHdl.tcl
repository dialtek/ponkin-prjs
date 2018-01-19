
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name FPGA2USB -dir "C:/work/Projects/FPGA_prj/FPGA2USB/FPGA2USB/planAhead_run_1" -part xc3s500efg320-4
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "FPGA2USB_imp.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {ipcore_dir/fx2lp_clk_div.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../main.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top fx2lp_slaveFIFO2b_streamIN_fpga_top $srcset
add_files [list {FPGA2USB_imp.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc3s500efg320-4
