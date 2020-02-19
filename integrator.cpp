#include "cantera/IdealGasMix.h"
#include "cantera/transport.h"
#include "cantera/zerodim.h"
#include <cstdio>

using namespace Cantera;
using std::cout;
using std::endl;

void integrator()
{
    IdealGasMix gas("gri30.cti","gri30_mix");
    double temp = 1201.0;
    double pres = OneAtm;
    gas.setState_TPX(temp, pres, "CH4:1, O2:2, N2:7.52");
    std::unique_ptr<Transport> tr(newTransportMgr("Mix", &gas, 0));
    
    writelog("#######################################################################\n");
    writelog("Initial state:\n");
    writelog("#######################################################################\n");
    
    std::cout << gas.report() << std::endl;

    IdealGasConstPressureReactor r;

    r.insert(gas);

    double dt = 1.e-2;
    int nsteps = 8;

    ReactorNet sim;
    sim.addReactor(r);
    writelog("#######################################################################\n");
    writelog("Integration:\n");
    writelog("#######################################################################\n\n");

    for (int i = 1; i <= nsteps; i++) {
        double tm = i*dt;
        sim.advance(tm);
        cout << "time =        " << tm << " s" << endl;
        cout << "pressure =    " << gas.pressure() << " Pa" << endl;
        cout << "temperature = " << gas.temperature() << " K" << endl;
        cout << "density =     " << gas.density() << " kg/m^3" << endl;
        cout << endl;
    }

    writelog("#######################################################################\n");
    writelog("Final state:\n");
    writelog("#######################################################################\n");
    std::cout << gas.report() << std::endl;
}

int main()
{
    try {
        integrator();
    } catch (CanteraError& err) {
        std::cout << err.what() << std::endl;
    }
}