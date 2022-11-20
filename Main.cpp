#include "Hline.hpp"
#include "Vline.hpp"
#include "Point.hpp"
#include "Domain.hpp"

int main(int argc, char **argv)
{
    // Point origin = Point(0,0);
    Hline border1 = Hline(0,1,true,0,0,1);
    Vline border2 = Vline(0,1,true,1,0,1);
    Hline border3 = Hline(0,1,true,0,0,1);
    Vline border4 = Vline(0,1,true,0,1,1);
    Domain domain = Domain(border1,border2,border3,border4);
    domain.generate_grid(5,5);
    domain.print_grid();
}