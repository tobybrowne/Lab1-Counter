#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char ** argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    int flag = 0;

    // run simulation for many clock cycles
    for (i=0; i<300; i++){
        // toggles clock and traces variables
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }

        // turn on rst before the second clock cycle and on the 15th.
        top->rst = (i < 2) | (i == 100);

        // turn on en after the 4th clock cycle
        top->en = (i > 4);

        // pause counting for 3 clock cycles starting at 0x9
        // required use of a new flag variable
        if(top->count > 9){
            if(flag == 0){
                flag = i;
            }
            
            if(i >= flag+3){
                top->en = 1;
            }
            else{
                top->en = 0;
            }
        }
        
        if(Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);

}