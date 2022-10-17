#include <visualization/visualization.h>

void LotkaVolterra(){

  /**
   *  Setting global variables, the time we are integrating over
   *  and the number of integration steps we take in this time.
   * 
   *  We also define the function f representing our ODE
   *  and the initial conditiond y0.
   */

  unsigned int steps = 1000;
  unsigned int t0 = 0;
  unsigned int tend = 10;


  auto f = [] (Eigen::VectorXd y) {
    Eigen::VectorXd df(2);
    df << y(0)*(4-4.0/3*y(1)) , -y(1)*(0.8-0.4*y(0));

    return df;
  };

  Eigen::VectorXd y0(2);
  y0 << 6,3;

  /**
   * Solve using built in solver:
   */

  std::vector<Eigen::VectorXd> result = ExplicitRKSolvers::Explicit4thOrderRK(f, y0, steps, t0, tend);

  std::vector<double> t(steps);
  std::vector<double> prey(steps);
  std::vector<double> predator(steps);

    for(size_t i = 0; i < t.size(); i++) {
        t[i] = i*(tend-t0 / (double) steps);
        prey[i] = result[i](0);
        predator[i] = result[i](1);
    }
    plt::title("Lotka-Volterra Integration Example");
    plt::named_plot("Prey Population",t, prey);
    plt::named_plot("Predator Population",t,predator);
    plt::xlabel("Time");
    plt::ylabel("Population");
    plt::legend();
    plt::save("lotkaVolterraSolved.png");

    plt::figure();
    plt::title("Lotka-Volterra Phase Space");
    plt::named_plot("Predator Prey",prey,predator);
    plt::xlabel("Prey");
    plt::ylabel("Predator");
    plt::save("lotkaVolterraPhaseSpace.png");

  
}

void LorenzAttractor(){

  /**
   *  Setting global variables, the time we are integrating over
   *  and the number of integration steps we take in this time.
   * 
   *  We also define the function f representing our ODE
   *  and the initial conditiond y0.
   */

  unsigned int steps = 10000;
  double sigma = 10;
  double rho = 28;
  double beta = 8.0/3;

  auto f = [beta,sigma,rho] (Eigen::VectorXd y) {
    Eigen::VectorXd df(3);
    df << sigma*(y(1) - y(0)), 
          y(0)*(rho-y(2)) - y(1),
          y(0)*y(1) - beta*y(2);

    return df;
  };



  Eigen::VectorXd y0(3);
  y0 << 1,1,1;

  /**
   * Solve using built in solver:
   */

  std::vector<Eigen::VectorXd> result = ExplicitRKSolvers::Explicit4thOrderRK(f,y0, steps, 0, 10);

  std::vector<double> x(steps);
  std::vector<double> y(steps);
  std::vector<double> z(steps);

    for(size_t i = 0; i < x.size(); i++) {
        x[i] = result[i](0);
        y[i] = result[i](1);
        z[i] = result[i](2);
    }
    plt::plot3(x, y, z);

    plt::xlabel("x");
    plt::ylabel("y");
    plt::set_zlabel("z"); // set_zlabel rather than just zlabel, in accordance with the Axes3D method
    
    // plt::title needs to be called after plot3(), otherwise title won't show up
    plt::title("Lorenz Attractor Integration Example");
    plt::save("lorenzAttractorSolved.png");
  
}




// int main(void) {
//   lotkaVolterra();
//   plt::show();
// }