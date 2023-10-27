module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk,
    input logic rst,
    input logic en,
    output logic [WIDTH-1:0] count
);

// posedge rst - makes reset asynchronous
// it can be hard to tell if rst is asynchronous since we only evaluate twice a cycle (in testbench)
always_ff @(posedge clk, posedge rst)
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + {{WIDTH-1{1'b0}}, en};

endmodule
