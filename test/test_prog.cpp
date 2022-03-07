#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include "tools.h"
#include "transducer.h"
#include "signal.h"
#include "stl_driver.h"

using namespace std;
using namespace RobonTL;

int main(int argc, char** argv) {


    // Read formula
    string phi_st = "alw_[0, 2.4] (x[t]>0)";
    cout << "Enter formula (default: alw_[0, 5] (x[t]>0))\n"  << endl;
    string req_st = string("signal x,y,z\n") + string("phi:=") + phi_st;
	
    STLDriver stl_driver = STLDriver();	
    bool parse_success = stl_driver.parse_string(req_st);
    if (parse_success) 
        cout << "Formula parsed successfully." << endl;
    else {
        cout << "Something went wrong." <<endl;
        return 1; 
    }  

    
    // Read data
    vector<double> sample;    

    double t = 0;
    double dt = 0.1; 

    if (parse_success) 
        cout << "Formula parsed successfully." << endl;
    else {
        cout << "Something went wrong." <<endl;
        return 1; 
    }  

    
    while (1) {
        // push time 
        sample.push_back(t);
        t += dt;

        // push value(s)
        cout << "Enter new value (666 to quit)" << endl;
        double value;
        cin >> value; 
        sample.push_back(value);

        // push new sample
        stl_driver.data.push_back(sample);
        sample.clear(); 
        if (value==666)
            break;

        // Computes upper and lower robustness

        /** compute robustness **/ 
        transducer* phi;
        double rob, rob_up, rob_low;
        rob = rob_up = rob_low = 0;
     
        Signal z, z_up, z_low;
	
        phi = stl_driver.formula_map["phi"]->clone();
        phi->set_horizon(0.,0.);
        phi->set_trace_data_ptr(stl_driver.data);                           
        rob    = phi->compute_robustness();
        rob_up = phi->compute_upper_rob();
        rob_low= phi->compute_lower_rob();
        z =  phi->z;
        z_low = phi->z_low;
        z_up = phi->z_up;
        z.addLastSample();
        z_low.addLastSample();
        z_up.addLastSample();
    

        cout << "Size of data:" << (phi->trace_data_ptr)->size() << endl;
        cout << "rob:" << rob << endl;
        cout << "rob_low:" << rob_low << endl;
        cout << "rob_up:" << rob_up << endl;
        delete phi;
    
    }
   

    return 0;

}

