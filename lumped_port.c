const char help[] = "test for sparse linear system!";

#include <petscksp.h>
#include <stdlib.h>

// struct definition
/*
 * csr matrix
 * size of matrix: m_size x n_size
 * count of non-zero elements
 * matrix row index
 * sum count of non-zero in every row, size: n_nz x 1
 * column indicies, size: n_nz x 1
 * non-zero elements, size: n_nz x 1
 * */
typedef struct csr_mat{
    int m_size;
    int n_size;
    int n_nz;
    int * row_index;
    int * pointer_row;
    int * pointer_column;
    double * nz_value;
}CSR_MAT;

/*
 * vector strucr
 * size of vector: n_size x 1
 * elements in vector: n_size x 1
 * */
typedef struct csr_vec{
    int n_size;
    double * nz_value;
}CSR_VEC;

int main( int argc, char * * args )
{
    puts( help );

    // read matrix file, vector file
    FILE * fp_mat = NULL, * fp_vec = NULL;
    CSR_MAT * lumped_port_mat = NULL;
    CSR_VEC * lumped_port_vec = NULL;

    if( ( fp_mat = fopen( "LinearSystem/matrix.txt", "r" ) ) == NULL 
	    || ( fp_vec = fopen( "LinearSystem/vector.txt", "r" ) ) == NULL )
    {
	fprintf( stderr, "Cannot open file!\n" );
	exit( EXIT_FAILURE );
    }

    if( ( lumped_port_mat = ( CSR_MAT * ) malloc( sizeof( CSR_MAT ) ) ) == NULL 
	    || ( lumped_port_vec = ( CSR_VEC * ) malloc( sizeof( CSR_VEC ) ) ) == NULL )
    {
	fprintf( stderr, "Memory allocation failed!\n" );
	exit( EXIT_FAILURE );
    }

    fscanf( fp_mat, "%d%d", &lumped_port_mat->m_size, &lumped_port_mat->n_size );
    fscanf( fp_vec, "%d", &lumped_port_vec->n_size );

    // memory allocation
    /*
     * mat->row_index, size: m_size x 1
     * mat->pointer_row, size: m_size + 1 x 1
     * mat->pointer_column, size: n_nz x 1
     * mat->nz_value, size: n_nz x 1
     * */
    if( ( lumped_port_mat->row_index = ( int * ) malloc( lumped_port_mat->m_size * sizeof( int ) ) ) == NULL 
	    || ( lumped_port_mat->pointer_row = ( int * ) malloc( ( lumped_port_mat->m_size + 1 ) * sizeof( int ) ) ) == NULL 
	    || ( lumped_port_mat->pointer_column = ( int * ) malloc( lumped_port_mat->n_nz * sizeof( int ) ) ) == NULL
	    || ( lumped_port_mat->nz_value = ( double * ) malloc( lumped_port_mat->n_nz * sizeof( double ) ) ) == NULL )
    {
	fprintf( stderr, "Memory allocation failed!\n" );
	exit( EXIT_FAILURE );
    }

    /*
     * vec->nz_value, size: n_size x 1
     * */
    if( ( lumped_port_vec->nz_value = ( double * ) malloc( lumped_port_vec->n_size * sizeof( double ) ) ) 
	    == NULL )
    {
	fprintf( stderr, "Memory allocation failed!\n" );
	exit( EXIT_FAILURE );
    }

    // matrix
    for( int index = 0; index < lumped_port_mat->m_size; index++ )
    {
	fscanf( fp_mat, "%d", lumped_port_mat->row_index + index );
    }
    for( int index = 0; index < lumped_port_mat->m_size + 1; index++ )
    {
	fscanf( fp_mat, "%d", lumped_port_mat->pointer_row + index );
    }
    for( int index = 0; index < lumped_port_mat->n_nz; index++ )
    {
	fscanf( fp_mat, "%d", lumped_port_mat->pointer_column + index );
    }
    for( int index = 0; index < lumped_port_mat->n_nz; index++ )
    {
	fscanf( fp_mat, "%lf", lumped_port_mat->nz_value + index );
    }

    // vector
    for( int index = 0; index < lumped_port_vec->n_size; index++ )
    {
	fscanf( fp_vec, "%lf", lumped_port_vec->nz_value + index );
    }

    fclose( fp_mat ); fclose( fp_vec );
    free( lumped_port_mat->row_index ); free( lumped_port_mat->pointer_row );
    free( lumped_port_mat->pointer_column ); free( lumped_port_mat->nz_value );
    free( lumped_port_vec->nz_value );
    free(lumped_port_mat); free( lumped_port_vec );

    return 0;
}
