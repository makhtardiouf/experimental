
#include "comb/stringsubst.h"

#include "matrix/vector.h"  // class vector
#include "matrix/matrix.h"  // class matrix

#include "fxtio.h"
#include "fxttypes.h"
#include "array-len.h"
#include "jjassert.h"

#include "nextarg.h"

//% 3-dimensional Hilbert curve generated by an L-system.


typedef vector<int> V3;
V3 Pos(3);

typedef matrix<int> M3;
M3 Dir(3);
M3 Rxp(3);  M3 Rxm(3);
M3 Ryp(3);  M3 Rym(3);
M3 Rzp(3);  M3 Rzm(3);


void
make_axis_rotation(ulong n, int phi, M3 &M)
// Create matrix that rotates by phi*90 degree (phi == +1 or -1)
// around axis n (== 0, 1, or 2).
{
    int c = 0;    // cos(phi) == 0
    int ps = +phi;  // +sin(phi) == +-1
    int ms = -phi;  // -sin(phi)

    M[0][0] = M[1][1] = M[2][2] = c;
    M[1][0] = M[0][2] = M[2][1] = ms;
    M[0][1] = M[2][0] = M[1][2] = ps;

    M[0][n] = M[1][n] = M[2][n] = 0;
    M[n][0] = M[n][1] = M[n][2] = 0;

    M[n][n] = 1;
}
// -------------------------


void
setup_rot_mat()
{
    Dir.unit();  // unit matrix

    // Fix initial direction so that
    // all coordinates remain positive:
    Dir[1][1] = -1;  Dir[2][2] = -1;

    make_axis_rotation(0, +1, Rxp);   //  '<'
    make_axis_rotation(0, -1, Rxm);   //  '>'
    make_axis_rotation(1, +1, Ryp);   //  'v'
    make_axis_rotation(1, -1, Rym);   //  '^'
    make_axis_rotation(2, +1, Rzp);   //  '+'
    make_axis_rotation(2, -1, Rzm);   //  '-'
}
// -------------------------

//void
//print_spmat(const M3 &M)
//{
//    cout << " [ ";
//    for (ulong r=0; r<3; ++r)
//    {
//        for (ulong c=0; c<3; ++c)
//        {
//            int t = M[r][c];
//            if ( t != 0 )  cout << (t>0?'+':'-') << c << " ";
//        }
//    }
//    cout << "]";
//}
//// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 2;
    NXARG(ldn, "Number of recursions, will create 8**ldn points");

    ulong cmax = (1UL<<(ldn*3)) + 4096;
    NXARG(cmax, "Max length of string");
    if ( cmax==0 )  cmax = -1UL;

    const char * h3d_rules[] = {
        // recursion:
        "a", "^<aF^<aFa-F^>>aFavF+>>aFa-F>a->",
        // "draw":
        "F", "F",
        // rotations:
        "+", "+",  // +z
        "-", "-",  // -z
        "^", "^",  // +y
        "v", "v",  // -y
        "<", "<",  // +x
        ">", ">"   // -x

//        "a", "yx a F yx a F a Z F yXX a F a Y F zXX a F a Z F X a ZX",
//        "F", "F",
//        "z", "z",  // +z
//        "Z", "Z",  // -z
//        "y", "y",  // +y
//        "Y", "Y",  // -y
//        "x", "x",  // +x
//        "X", "X"   // -x
    };
    //  axiom is "a"

    string_subst S(ldn);
    S.set_axiom("a");
    S.set_rules( h3d_rules, ARRAY_LEN(h3d_rules) );
    jjassert( S.first() );


    M3 Ri(3);  Ri.unit();  // current orientation
    setup_rot_mat();
    int x=0, y=0, z=0;  // current coordinates
    int dx, dy, dz;  // increment

    ulong ct=0;  // count non-turn symbols
    do
    {
        if ( ct > cmax )  break;

        char c = S.current();

        switch ( c )
        {
        case 'a':
            break;

        case 'F':
            dx = Dir[0][0];  dy = Dir[1][0];  dz = Dir[2][0];
            x += dx;  y += dy;  z += dz;

            ++ct;
            if ( 0==(ct%8) )  cout << endl;
            cout << setw(6) << ct << ":";


            cout << "    dir=[";
            cout << setw(2) << dx << ", ";
            cout << setw(2) << dy << ", ";
            cout << setw(2) << dz << " ]  ";

            // move:
            if ( dx )  cout << (dx>0?'>':'<');
            if ( dy )  cout << (dy>0?'^':'v');
            if ( dz )  cout << (dz>0?'+':'-');

            cout << "    pos=[";
            cout << setw(2) << x << ", ";
            cout << setw(2) << y << ", ";
            cout << setw(2) << z << " ]";

            cout << endl;
            break;

#define  CASE(s, R)  case s : Ri*=R; Dir*=R;  break;
            CASE( '+', Rzp);
            CASE( '-', Rzm);
            CASE( '^', Rym);
            CASE( 'v', Ryp);
            CASE( '<', Rxp);
            CASE( '>', Rxm);
        }
    }
    while ( S.next() );

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/stringsubst-hilbert3d-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/stringsubst-hilbert3d-demo.cc DEMOFLAGS=-DTIMING"
/// End:

