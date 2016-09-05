extern "C" {

#define CPP_CHAR1 char
#define CPP_INT8  isvd::index_t
#define CPP_REAL4 float
#define CPP_REAL8 double
#define CPP_COMP4 std::complex<float>
#define CPP_COMP8 std::complex<double>

#define FORTRAN_CHAR1 CPP_CHAR1*
#define FORTRAN_INT8  CPP_INT8*
#define FORTRAN_REAL4 CPP_REAL4*
#define FORTRAN_REAL8 CPP_REAL8*
#define FORTRAN_COMP4 CPP_COMP4*
#define FORTRAN_COMP8 CPP_COMP8*

#define REAL4_SELECT2(name) CPP_INT8 (*arg)( const FORTRAN_REAL4, const FORTRAN_REAL4 )
#define REAL8_SELECT2(name) CPP_INT8 (*arg)( const FORTRAN_REAL8, const FORTRAN_REAL8 )
#define COMP4_SELECT1(name) CPP_INT8 (*arg)( const FORTRAN_COMP4 )
#define COMP8_SELECT1(name) CPP_INT8 (*arg)( const FORTRAN_COMP8 )
