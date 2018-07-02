
using namespace std;

class Idx {


    ifstream _label;
    ifstream _image;

    string _labelName = "trainlabels";
    string _imageName = "trainimages";

    public:
    Idx() {
        _label.open( _labelName );
        _image.open( _imageName );
        if( !_label.is_open() ) throw "CANNOT OPEN " + _labelName;
        if( !_image.is_open() ) throw "CANNOT OPEN " + _imageName;
    }


    Matrix <float> getImage(int n) {

        Matrix <float> image( 28, 28 );
        char value[1];
        float res;

        for (int i = 0; i < 28; ++i ) {     //Cols
            for (int j = 0; j < 28; ++j ) { //Rows
            // Move indexer to pixel in i column in j row
            _image.seekg( 784 * n + 16 + 28 * i + j );
            _image.read( value, sizeof( value ) );   

            float res = int( *value );

            image[i][j] = res;
            }
        }
        return image;
    }

    Matrix <float> getLabel( int n ) {
        char value[1];
        
        _label.seekg( n + 8 );
        _label.read( value, sizeof( value ) );   

        // Multistep conversion from char to float
        float res = int( *value );
        
        return Matrix <float> {{ res }};
    }

    int convert( char *buffer, int size ) {
        // Convert multiple bytes to one int
        int value{};
        for( uint i = 0; i < size; ++i ) {
            value += buffer[i] << ( 8 * ( size - i - 1 ));
        }
        return value;
    }
};