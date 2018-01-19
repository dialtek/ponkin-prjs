//-----------------------------------------------------------------------------
//  
//  Copyright (c) 2009 Xilinx Inc.
//
//  Project  : Programmable Wave Generator
//  Module   : out_ddr_flop.v
//  Parent   : Various
//  Children : None
//
//  Description: 
//    This is a wrapper around a basic DDR output flop.
//    A version of this module with identical ports exists for all target
//    technologies for this design
//    
//
//  Parameters:
//    None
//
//  Notes       : 
//
//  Multicycle and False Paths, Timing Exceptions
//     None
//

`timescale 1ns/1ps


module out_ddr_flop (
  input            clk,          // Destination clock
  input            rst,          // Reset - synchronous to destination clock
  input            d_rise,       // Data for the rising edge of clock
  input            d_fall,       // Data for the falling edge of clock
  output           q             // Double data rate output
);


//***************************************************************************
// Register declarations
//***************************************************************************

//***************************************************************************
// Code
//***************************************************************************

   // ODDR2: Output Double Data Rate Output Register with Set, Reset
   //        and Clock Enable.
   //        Spartan-6
   // Xilinx HDL Language Template, version ???

   ODDR2 #(
      .DDR_ALIGNMENT("NONE"), // Sets output alignment to "NONE", "C0" or "C1" 
      .INIT(1'b0),    // Sets initial state of the Q output to 1'b0 or 1'b1
      .SRTYPE("SYNC") // Specifies "SYNC" or "ASYNC" set/reset
   ) ODDR2_inst (
      .Q   (q),      // 1-bit DDR output data
      .C0  (clk),    // 1-bit clock input
      .C1  (!clk),   // 1-bit clock input
      .CE  (1'b1),   // 1-bit clock enable input
      .D0  (d_rise), // 1-bit data input (associated with C0)
      .D1  (d_fall), // 1-bit data input (associated with C1)
      .R   (rst),    // 1-bit reset input
      .S   (1'b0)    // 1-bit set input
   );

   // End of ODDR2_inst instantiation

endmodule

