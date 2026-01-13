
module DifftestClockGate(
	input     CK,
	input	    E,
	output    Q
);

`ifdef SYNTHESIS
	BUFGCE bufgce_1 (
		.O(Q),
		.I(CK),
		.CE(E)
	);
`else
  assign Q = CK & E;
`endif // SYNTHESIS
endmodule

